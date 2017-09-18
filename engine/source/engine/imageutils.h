#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes
#include "png.h"

// Internal Includes
#include "_global.h"
#include "logger.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

enum class ImageFormat {
    UNKOWN, GREY, GREYA, RGB, RGBA
};

class Image {
public:
            Image() = default;
            ~Image() = default;

    uint32          width;
    uint32          height;
    uint32          bpp; // Bytes per pixels
    ImageFormat     format;
    vector<uint8>   data;
    uint32          sizeBytes;

    string          dbg_str() {
        std::ostringstream oss;
        oss << width << "x" << height << "x" << bpp * 8;
        return oss.str();
    }
};

class ImageUtils {
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                      Public Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static owner<Image>		 load_png( string file );
    static void              flip_y( Image* image );

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                      Private Static                    */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    ImageUtils() = default;
    ~ImageUtils() = default;

    static Logger LOGGER;
};

ENGINE_NAMESPACE_END
