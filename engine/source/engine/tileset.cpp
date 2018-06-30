#include "stdafx.h"
#include "tileset.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Tileset::Tileset( string pTexture, uint32 pTileWidth, uint32 pTileHeight )
    : _tileWidth(pTileWidth), _tileHeight(pTileHeight), _texturePath( pTexture ), _texture(nullptr)
{

}

Rect4f Tileset::get_uvs_by_index( uint32 index )
{
    if ( _texture == nullptr )
        return Rect4f( 0, 0, 1, 1 );


    float uvPerX = ( 1.0f * _tileWidth) / _texture->get_width();
    float uvPerY = ( 1.0f * _tileHeight) / _texture->get_height();

    uint32 x = index % tiles_per_row();
    uint32 y = index / tiles_per_row();

    return Rect4f( x * uvPerX, y * uvPerY, uvPerX, uvPerY );
}

weak<Texture> Tileset::get_texture()
{
    return _texture;
}

uint32 Tileset::get_tile_width()
{
    return _tileWidth;
}

uint32 Tileset::get_tile_height()
{
    return _tileHeight;
}

uint32 Tileset::tiles_per_row()
{
    if ( _texture == nullptr )
        return 0;

    return _texture->get_width() / _tileWidth;
}

uint32 Tileset::tiles_per_col()
{
    if ( _texture == nullptr )
        return 0;

    return _texture->get_height() / _tileHeight;
}

void Tileset::on_init( RenderEngine& pRenderEngine)
{
    _texture = pRenderEngine.get_texture( _texturePath );
    cout << "Init Tileset\n";
}

void Tileset::on_cleanup( RenderEngine& pRenderEngine )
{
}

ENGINE_NAMESPACE_END


