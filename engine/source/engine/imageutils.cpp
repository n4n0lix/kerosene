#include "imageutils.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// http://devcry.heiho.net/html/2015/20150517-libpng.html
owner<Image> ImageUtils::load_png(string filepath)
{
    LOGGER.log(Level::DEBUG) << "Load png file '" << filepath.c_str() << "' ..." << endl;

    uint32          imgWidth;
    uint32          imgHeight;
    uint32          imgBpp;
    ImageFormat     imgFormat;
    uint32          imgBytes;
    list<uint8>     imgData;

    // 1# Open file
    FILE* ptrFile;
    errno_t error = fopen_s(&ptrFile, filepath.c_str(), "rb");
    //owner<FILE> file = owner<FILE>(ptrFile);

    std::cout << filepath << endl;

    if (error) {
        LOGGER.log(Level::ERROR) << "Couldn't load png file: error (errno:" << error << ") during open file '" << filepath.c_str() << "'!" << endl;
        return nullptr;
    }

    // 2# Verify png file
    unsigned char fileSignature[8];
    if (fread(fileSignature, 1, sizeof(fileSignature), ptrFile) < 8) {
        fclose( ptrFile );
        LOGGER.log(Level::ERROR) << "Couldn't load png file: file '" << filepath << "' couldn't be read!" << endl;
        return nullptr;
    }

    if (!png_check_sig(fileSignature, 8)) {
        fclose( ptrFile );
        LOGGER.log(Level::ERROR) << "Couldn't load png file: file '" << filepath << "' is no png file!" << endl;
        return nullptr;
    }

    // 3# Prepare PNG decoding
    png_structp pngDecoder = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (pngDecoder == nullptr) {
        fclose( ptrFile );
        LOGGER.log(Level::ERROR) << "Couldn't load png file: couldn't create png-handle!" << endl;
        return nullptr;
    }

    png_infop pngMetadata = png_create_info_struct(pngDecoder);
    if (pngMetadata == nullptr) {
        png_destroy_read_struct(&pngDecoder, nullptr, nullptr);
        fclose( ptrFile );
        LOGGER.log(Level::ERROR) << "Couldn't load png file: couldn't create png-metadata!" << endl;
        return nullptr;
    }

    // 4# PNG Decoding
    // set libpng error handling mechanism
    if (setjmp(png_jmpbuf(pngDecoder))) {
        png_destroy_read_struct(&pngDecoder, &pngMetadata, nullptr);
        fclose( ptrFile );
        return nullptr;
    }

    png_init_io( pngDecoder, ptrFile );

    // skip signature bytes (we already read those)
    png_set_sig_bytes( pngDecoder, sizeof(fileSignature) );

    // get image information
    png_read_info( pngDecoder, pngMetadata );

    imgWidth = png_get_image_width( pngDecoder, pngMetadata );
    imgHeight = png_get_image_height( pngDecoder, pngMetadata );

    // set least one byte per channel
    if (png_get_bit_depth( pngDecoder, pngMetadata ) < 8) {
        png_set_packing( pngDecoder );
    }

    // #X Convert transparency to alpha channel
    if (png_get_valid( pngDecoder, pngMetadata, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha( pngDecoder );
    }

    // #X Determine color format
    switch (png_get_color_type( pngDecoder, pngMetadata )) {
        case PNG_COLOR_TYPE_GRAY:
            png_set_gray_to_rgb( pngDecoder );
            imgFormat = ImageFormat::RGB;
            break;

        case PNG_COLOR_TYPE_GRAY_ALPHA:
            png_set_gray_to_rgb( pngDecoder );
            imgFormat = ImageFormat::RGBA;
            break;

        case PNG_COLOR_TYPE_PALETTE:
            png_set_expand( pngDecoder );
            imgFormat = ImageFormat::RGB;
            break;

        case PNG_COLOR_TYPE_RGB:
            imgFormat = ImageFormat::RGB;
            break;

        case PNG_COLOR_TYPE_RGBA:
            imgFormat = ImageFormat::RGBA;
            break;

        default:
            imgFormat = ImageFormat::UNKOWN;
    }

    if (imgFormat == ImageFormat::UNKOWN) {
        png_destroy_read_struct( &pngDecoder, &pngMetadata, nullptr );
        fclose( ptrFile );
        return nullptr;
    }

    // #X Read bytes per pixels
    imgBpp = (uint32)png_get_rowbytes( pngDecoder, pngMetadata ) / imgWidth;

    // #X ??? TODO: Investigate this step
    png_set_interlace_handling( pngDecoder );
    png_read_update_info( pngDecoder, pngMetadata );

    // #X Read out image data
    imgData.resize(imgWidth * imgHeight * imgBpp);

    vector<png_bytep> rows;
    rows.resize( imgHeight, 0 );
    uint8* row_address = &imgData[0];
    for (int32 i = 0; i < imgHeight; i++) {
        rows[i] = row_address;
        row_address += imgWidth * imgBpp;
    }
    png_read_image(pngDecoder, &rows[0]);

    // #X Clean up png reading
    png_read_end( pngDecoder , nullptr );
    png_destroy_read_struct( &pngDecoder, &pngMetadata, nullptr );
    fclose( ptrFile );
    
    // X# Return Image
    owner<Image> result = make_unique<Image>();
    result->width       = imgWidth;
    result->height      = imgHeight;
    result->format      = imgFormat;
    result->bpp         = imgBpp;
    result->data        = move( imgData );
    result->sizeBytes   = imgBytes;
    
    LOGGER.log(Level::DEBUG) << "Png file '" << filepath.c_str() << "' sucessful loaded (" << result->dbg_str() << ")" << endl;

    return move( result );
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Logger ImageUtils::LOGGER = Logger("ImageUtils", Level::DEBUG);

ENGINE_NAMESPACE_END