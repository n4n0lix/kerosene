#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "transform.h"
#include "renderer.h"
#include "matrix4f.h"
#include "shader.h"
#include "material.h"
#include "texture.h"
#include "simplevertexarray.h"
#include "attribvertexarray.h"
#include "tileset.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct CharMapping {
    uint32 index;
    uint32 width;
};

class TextRenderer : public Renderer
{
public:
  TextRenderer( weak<Tileset> pTileset );
  TextRenderer( weak<Tileset> pTileset, Entity pEntity );

  void set_text( string text );
  void set_font_size( float );

  // Inhereted by Renderer
  virtual float render_layer_priority() const override;

protected:
  // Inhereted by Renderer
  virtual void on_init( RenderEngine& ) override;
  virtual void on_render( RenderEngine&, Camera&, Matrix4f& pProjViewMat, float pInterpolation ) override;
  virtual void on_cleanup( RenderEngine& ) override;

private:
  void                on_dirty();
  void                init_char_mapping();

  bool                            _textChanged;
  Material                        _material;
  string                          _text;
  std::map<char32, CharMapping>   _charMapping;
  weak<Tileset>                   _tileset;
  bool                            _tilesetInit;

  SimpleVertexArray<Vertex_pt> _svao;
  AttribVertexArray<Vertex_pt> _avao;

  static Logger LOGGER;
};

ENGINE_NAMESPACE_END
