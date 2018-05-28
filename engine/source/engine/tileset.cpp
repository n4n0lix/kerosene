#include "stdafx.h"
#include "tileset.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Tileset::Tileset( uint32 pTileWidth, uint32 pTileHeight, weak<Texture> pTexture )
    : _tileWidth(pTileWidth), _tileHeight(pTileHeight), _texture( pTexture )
{

}

Rect4f Tileset::get_uvs_by_index( uint32 index )
{
    float uvPerX = ( 1.0f * _texture->get_width() ) / _tileWidth;
    float uvPerY = ( 1.0f * _texture->get_height()) / _tileHeight;

    uint32 x = index % _tileWidth;
    uint32 y = index / _tileHeight;

    return Rect4f( x * uvPerX, y * uvPerY, uvPerX, uvPerY );
}

weak<Texture> Tileset::get_texture()
{
    return _texture;
}

ENGINE_NAMESPACE_END


