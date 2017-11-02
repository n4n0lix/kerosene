#include "stdafx.h"
#include "texture.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Texture::Texture(Image* image, TextureOptions options)
{
    // 0# Contract Pre
    Requires( image != nullptr );

    // 1# 
    _width = image->width;
    _height = image->height;
    _bpp = image->bpp;

    // 2# Configure texture object
    glGenTextures(1, &_id);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, _id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (options.filtering() == TextureFiltering::LINEAR) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    // 3# Load image data       
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data.data());

    glGenerateMipmap( GL_TEXTURE_2D );

    LOGGER.log(Level::DEBUG, _id) << "CREATE\n";
    PerfStats::instance().frame_load_texture( _width * _height * _bpp);
}

Texture::~Texture()
{
    LOGGER.log(Level::DEBUG, _id) << "DELETE\n";
    glDeleteTextures( 1, &_id );
    PerfStats::instance().frame_unload_texture( _width * _height * _bpp );
}

GLuint Texture::id() {
    return _id;
}

uint32 Texture::get_width()
{
    return _width;
}

uint32 Texture::get_height()
{
    return _height;
}

uint32 Texture::get_bpp()
{
    return _bpp;
}

bool Texture::operator==(const Texture & o) const
{
    return _id == o._id;
}

bool Texture::operator!=(const Texture & o) const
{
    return !(*this == o);
}

bool Texture::operator<(const Texture & o1) const
{
    return _id < o1._id;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Logger Texture::LOGGER = Logger("Texture", Level::DEBUG);

ENGINE_NAMESPACE_END

