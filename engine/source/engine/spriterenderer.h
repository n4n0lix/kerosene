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
#include "stopwatch.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef uint32 TextureI;

#define MAX_ANIMS 16
#define MAX_ANIM_KEYS 16
#define MAX_SUBSPRITES 64

class SpriteRenderer : public Renderer
{
public:
    struct Config {
        Vector2f anchor;
        Vector2f size;
        weak<Texture> texture;
        Entity  entity;
    };

    struct AnimKey {
      uint32 time = 0;
      uint32 subSprite = 0;
    };

    struct Animation {
      AnimKey keys[MAX_ANIM_KEYS];
    };

    struct SubSprite {
      float left   = 0;
      float top    = 0;
      float right  = 1;
      float bottom = 1;
    };


public:
    SpriteRenderer();
    SpriteRenderer( Config config );

    bool      dirty;

    uint32    CurAnim;
    uint32    CurAnimKey;
    Animation Anims[MAX_ANIMS];
    SubSprite SubSprites[MAX_SUBSPRITES];
    StopWatch StopWatch;

    void    set_texture( weak<Texture> );
    void    set_origin( Vector2f );
    void    set_size( Vector2f );

    // Inhereted by Renderer
    virtual float render_layer_priority() const override;

protected:
    // Inhereted by Renderer
    virtual void on_init( RenderEngine& ) override;
    virtual void on_render( RenderEngine&, Camera&, Matrix4f& pProjViewMat, float pInterpolation ) override;
    virtual void on_cleanup( RenderEngine& ) override;

private:
    void on_dirty();

    Vector2f                    _size;
    Vector2f                    _anchor;
    Material                    _material;

    SimpleVertexArray<Vertex_pt> _svao;

    static Logger LOGGER;
};

ENGINE_NAMESPACE_END
