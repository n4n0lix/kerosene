#pragma once

// Std-Includes

// Other Includes
#include "png.h"

// Internal Includes
#include "_global.h"
#include "logger.h"

ENGINE_NAMESPACE_BEGIN

enum class ImageFormat {
    UNKOWN, GREY, GREYA, RGB, RGBA
};


class Image {
public:
            Image() = default;
            ~Image() = default;

    uint32              width;
    uint32              height;
    uint32              bpp; // Bytes per pixels
    ImageFormat         format;
    std::vector<uint8>  data;
    uint32              sizeBytes;

    string          dbg_str() {
        std::ostringstream oss;
        string formatStr;

        switch ( format ) {
            case ImageFormat::UNKOWN: formatStr = "UNKOWN"; break;
            case ImageFormat::GREY: formatStr = "GREY"; break;
            case ImageFormat::GREYA: formatStr = "GREYA"; break;
            case ImageFormat::RGB: formatStr = "RGB"; break;
            case ImageFormat::RGBA: formatStr = "RGBA"; break;
        }

        oss << width << "x" << height << "x" << bpp * 8 << "@" << formatStr;
        return oss.str();
    }
};

class ImageUtils {
public:

    static owner<Image>		 load_png( string file );
    static void              flip_y( Image* image );

private:
    ImageUtils() = default;
    ~ImageUtils() = default;

    static Logger LOGGER;
};

ENGINE_NAMESPACE_END
