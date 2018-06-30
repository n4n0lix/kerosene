#include "stdafx.h"
#include "textrenderer.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

TextRenderer::TextRenderer(weak<Tileset> pTileset) : TextRenderer(pTileset, Entity::None)
{

}

TextRenderer::TextRenderer(weak<Tileset> pTileset, Entity pEntity ) :
    _material( Material() ), _tileset( pTileset )
{
    set_entity( pEntity );
    init_char_mapping();
}

void TextRenderer::set_text( string text )
{
    _textChanged = _text != text;
    _text = text;
}

void TextRenderer::on_init( RenderEngine& pRenderEngine )
{   
    _material.set_shader( pRenderEngine.get_shader( "builtin_texture" ) );
    
    on_dirty();
}

void TextRenderer::on_render( RenderEngine& pRenderEngine, Camera& pCamera, Matrix4f& pProjViewMat, float pInterpolation )
{
    auto entity = get_entity();

    if ( _textChanged) {
        _textChanged = false;
        on_dirty();
    }

    if ( _tilesetInit != _tileset->is_init() ) {
        _tilesetInit = _tileset->is_init();
        on_dirty();
    }

    Vector3f position;
    Vector3f scale;
    Quaternion4f rotation;

    if ( entity.has<CTransform>() ) {
        CTransform& transform = entity.get<CTransform>();

        // Interpolate transform, as we are between a calculated tick and a future tick
        position = Vector3f::lerp( transform.lastPosition, transform.position, pInterpolation );
        scale = Vector3f::lerp( transform.lastScale, transform.scale, pInterpolation );
        rotation = Quaternion4f::slerp( transform.lastRotation, transform.rotation, pInterpolation );
    }
    else {
        position = Vector3f( 0, 0, 0 );
        scale = Vector3f( 1, 1, 1 );
        rotation = Quaternion4f();
    }

    Matrix4f matPos = Matrix4f::translation( position );
    Matrix4f matScale = Matrix4f::scaling( scale );
    Matrix4f matRot = Quaternion4f::to_rotation_mat4f( rotation );

#ifdef MAT4_ROW_MAJOR
    Matrix4f world  = (matScale * matRot) * matPos;
    Matrix4f wvp    = pProjViewMat * world;
#else
    Matrix4f world = (matPos * matRot) * matScale;
    Matrix4f wvp    = world * pProjViewMat;
#endif

    _material.set_texture_diffuse( _tileset->get_texture() );
    _material.set_wvp( wvp );
    _material.bind();
    _svao.render_all();
}

void TextRenderer::on_cleanup( RenderEngine& pRenderEngine )
{
}

void TextRenderer::on_dirty()
{
    uint32 pointer = 0;
    std::vector<Vertex_pt> vertices = {};

    for ( size_t i = 0; i < _text.length(); i++ ) {
        char32 chr = _text.at( i );
        CharMapping map = _charMapping[chr];

        float x0 = pointer + 0.0f;
        float x1 = pointer + 4.f;
        float y0 = 0.f;
        float y1 = 4.f;

        auto uvs = _tileset->get_uvs_by_index( map.index );

        auto v0 = Vertex_pt( Vector3f( x1, y0, 0 ), Vector2f( uvs.max_x(), uvs.max_y() ) );
        auto v1 = Vertex_pt( Vector3f( x0, y0, 0 ), Vector2f( uvs.min_x(), uvs.max_y() ) );
        auto v2 = Vertex_pt( Vector3f( x1, y1, 0 ), Vector2f( uvs.max_x(), uvs.min_y() ) );
        auto v3 = Vertex_pt( Vector3f( x0, y1, 0 ), Vector2f( uvs.min_x(), uvs.min_y() ) );

        //auto v0 = Vertex_pt( Vector3f( x1, y0, 0 ), Vector2f( 1, 1 ) );
        //auto v1 = Vertex_pt( Vector3f( x0, y0, 0 ), Vector2f( 0, 1 ) );
        //auto v2 = Vertex_pt( Vector3f( x1, y1, 0 ), Vector2f( 1, 0 ) );
        //auto v3 = Vertex_pt( Vector3f( x0, y1, 0 ), Vector2f( 0, 0 ) );

        auto vrts = std::vector<Vertex_pt>{
            v0, v1, v2,
            v1, v2, v3
        };

        vertices.insert( vertices.end(), vrts.begin(), vrts.end() );
        pointer += (map.width-1);
    }

    _svao.get_vertex_buffer()->clear();
    _svao.get_vertex_buffer()->add_vertices( vertices );
}

void TextRenderer::init_char_mapping()
{
    _charMapping['A'] = { 0, 4 };
    _charMapping['B'] = { 1, 4 };
    _charMapping['C'] = { 2, 4 };
    _charMapping['D'] = { 3, 4 };
    _charMapping['E'] = { 4, 4 };
    _charMapping['F'] = { 5, 4 };
    _charMapping['G'] = { 6, 4 };
    _charMapping['H'] = { 7, 4 };
    _charMapping['I'] = { 8, 1 };
    _charMapping['J'] = { 9, 4 };
    _charMapping['K'] = { 10, 4 };
    _charMapping['L'] = { 11, 4 };
    _charMapping['M'] = { 12, 5 };
    _charMapping['N'] = { 13, 4 };
    _charMapping['O'] = { 14, 4 };
    _charMapping['P'] = { 15, 4 };
    _charMapping['Q'] = { 16, 4 };
    _charMapping['R'] = { 17, 4 };
    _charMapping['S'] = { 18, 4 };
    _charMapping['T'] = { 19, 5 };
    _charMapping['U'] = { 20, 4 };
    _charMapping['V'] = { 21, 5 };
    _charMapping['W'] = { 22, 5 };
    _charMapping['X'] = { 23, 4 };
    _charMapping['Y'] = { 24, 4 };
    _charMapping['Z'] = { 25, 5 };

    _charMapping['a'] = { 32, 4 };
    _charMapping['b'] = { 33, 4 };
    _charMapping['c'] = { 34, 3 };
    _charMapping['d'] = { 35, 4 };
    _charMapping['e'] = { 36, 4 };
    _charMapping['f'] = { 37, 3 };
    _charMapping['g'] = { 38, 4 };
    _charMapping['h'] = { 39, 3 };
    _charMapping['i'] = { 40, 1 };
    _charMapping['j'] = { 41, 2 };
    _charMapping['k'] = { 42, 3 };
    _charMapping['l'] = { 43, 2 };
    _charMapping['m'] = { 44, 5 };
    _charMapping['n'] = { 45, 3 };
    _charMapping['o'] = { 46, 4 };
    _charMapping['p'] = { 47, 4 };
    _charMapping['q'] = { 48, 4 };
    _charMapping['r'] = { 49, 3 };
    _charMapping['s'] = { 50, 4 };
    _charMapping['t'] = { 51, 2 };
    _charMapping['u'] = { 52, 4 };
    _charMapping['v'] = { 53, 3 };
    _charMapping['w'] = { 54, 5 };
    _charMapping['x'] = { 55, 4 };
    _charMapping['y'] = { 56, 4 };
    _charMapping['z'] = { 57, 4 };

    _charMapping['0'] = { 64, 2 };
    _charMapping['1'] = { 65, 2 };
    _charMapping['2'] = { 66, 2 };
    _charMapping['3'] = { 67, 2 };
    _charMapping['4'] = { 68, 2 };
    _charMapping['5'] = { 69, 2 };
    _charMapping['6'] = { 70, 2 };
    _charMapping['7'] = { 71, 2 };
    _charMapping['8'] = { 72, 2 };
    _charMapping['9'] = { 73, 2 };
    _charMapping['+'] = { 74, 2 };
    _charMapping['-'] = { 75, 2 };
    //_charMapping[' '] = { 76, 2 };
    _charMapping['*'] = { 77, 2 };
    _charMapping['#'] = { 78, 2 };
    _charMapping['~'] = { 79, 2 };

    _charMapping['^'] = { 80, 2 };
    _charMapping['°'] = { 81, 2 };
    _charMapping['!'] = { 82, 2 };
    _charMapping['"'] = { 83, 2 };
    _charMapping['§'] = { 84, 2 };
    _charMapping['$'] = { 85, 2 };
    _charMapping['%'] = { 86, 2 };
    _charMapping['&'] = { 87, 2 };
    _charMapping['/'] = { 88, 2 };
    _charMapping['('] = { 89, 2 };
    _charMapping[')'] = { 90, 2 };
    _charMapping['='] = { 91, 2 };
    _charMapping['?'] = { 92, 2 };
    _charMapping['\\'] = { 93, 2 };
    _charMapping['`'] = { 94, 2 };
    _charMapping['´'] = { 95, 2 };

    _charMapping[' '] = { 96, 2 };
    _charMapping['.'] = { 97, 2 };
    _charMapping[':'] = { 98, 2 };
    _charMapping[','] = { 99, 2 };
    _charMapping[';'] = { 100, 2 };
    _charMapping['_'] = { 101, 2 };
    _charMapping['['] = { 102, 2 };
    _charMapping[']'] = { 103, 2 };
    _charMapping['{'] = { 104, 2 };
    _charMapping['}'] = { 105, 2 };
    _charMapping['²'] = { 106, 2 };
    _charMapping['³'] = { 107, 2 };
    _charMapping['<'] = { 108, 2 };
    _charMapping['>'] = { 109, 2 };
    _charMapping['|'] = { 110, 2 };
    _charMapping['\''] = { 111, 2 };
}

float TextRenderer::render_layer_priority() const
{
    if ( get_entity().has<CTransform>() )
        return get_entity().get<CTransform>().position.z;
    else
        return FLT_MAX;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
