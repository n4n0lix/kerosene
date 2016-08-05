#include "imageutils.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void ImageUtils::load_png(string filepath)
{
    LOGGER.log(Level::DEBUG) << "Load png file '" << filepath.c_str() << "'" << endl;

    // 1# Open file
    FILE* ptrFile;
    errno_t error = fopen_s(&ptrFile, filepath.c_str(), "rb");
    unique_ptr<FILE> file = unique_ptr<FILE>(ptrFile);

    std::cout << filepath << endl;

    if (error) {
        LOGGER.log(Level::ERROR) << "Couldn't load png file: error (errno:" << error << ") during open file '" << filepath.c_str() << "'!" << endl;
        return;
    }

    // 2# Verify png file
    unsigned char fileSignature[8];
    if (fread(fileSignature, 1, sizeof(fileSignature), file.get()) < 8) {
        fclose(file.get());
        LOGGER.log(Level::ERROR) << "Couldn't load png file: file '" << filepath << "' couldn't be read!" << endl;
        return;
    }

    if (!png_check_sig(fileSignature, 8)) {
        fclose( file.get() );
        LOGGER.log(Level::ERROR) << "Couldn't load png file: file '" << filepath << "' is no png file!" << endl;
        return;
    }

    // 3# Prepare PNG decoding
    png_structp pngHandle = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (pngHandle == nullptr) {
        fclose( file.get() );
        LOGGER.log(Level::ERROR) << "Couldn't load png file: couldn't create png-handle!" << endl;
        return;
    }

    png_infop pngMetadata = png_create_info_struct(pngHandle);
    if (pngMetadata == nullptr) {
        png_destroy_read_struct(&pngHandle, nullptr, nullptr);
        fclose( file.get() );
        LOGGER.log(Level::ERROR) << "Couldn't load png file: couldn't create png-metadata!" << endl;
        return;
    }

    // 4# PNG Decoding
    // set libpng error handling mechanism
    if (setjmp(png_jmpbuf(pngHandle))) {
        png_destroy_read_struct(&pngHandle, &pngMetadata, nullptr);
        fclose(file.get());

        if (pixels != nullptr) {
            delete[] pixels;
            pixels = nullptr;
        }
        return false;
    }

    // TODO: continue http://devcry.heiho.net/html/2015/20150517-libpng.html

    // X# clean up
    fclose(file.get());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Logger ImageUtils::LOGGER = Logger("ImageUtils", Level::DEBUG);

ENGINE_NAMESPACE_END