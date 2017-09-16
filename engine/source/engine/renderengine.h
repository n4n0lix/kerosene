#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <iostream>

// Other Includes

// Internal Includes
#include "_gl.h"
#include "_global.h"
#include "engineexception.h"
#include "glwindow.h"
#include "gameobject.h"

// Testing Includes (temporary)
#include "primitivetype.h"
#include "camera.h"

#include "texture.h"
#include "shader.h"
#include "material.h"
#include "batch.h"

#include "vertex_pc.h"
#include "vertex_pt.h"
#include "shaderbuilder.h"
#include "textureslot.h"

#include "imageutils.h"
#include "stringutils.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class Camera;
class GameObject;

class RenderEngine
{
public:

    const int32_t GL_VERSION_MAJOR = 3;
    const int32_t GL_VERSION_MINOR = 3;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            RenderEngine() = default;
            virtual ~RenderEngine() = default;

    // GENERAL
    void on_start();
	void on_render(list<GameObject*> gameObjects);
    void on_shutdown();
	bool is_exit_requested();

    // UTILITY
    void            set_interpolation(float interpol);
	weak<GLWindow>  get_window();
    owner<Texture>  load_texture(string filename, TextureOptions options = TextureOptions());

	// RESOURCES
	weak<Texture>       add_texture(string filename, owner<Texture> texture);
    weak<Texture>       get_texture(string name);
    bool                has_texture(string name);

    weak<Shader>        add_shader(string name, owner<Shader> shader);
	weak<Shader>        get_shader(string name);
    bool                has_shader(string name);

    weak<Material>      add_material(string name, owner<Material> material);
    weak<Material>      get_material(string name);
    bool                has_material(string name);


	// RENDERING
	template<class VERTEX>
	owner<VertexToken>  add_vertices(weak<Material> material, list<VERTEX> vertices);
	void                remove_vertices(owner<VertexToken> token);

	void                add_render(weak<VertexToken> token);
	void                remove_render(weak<VertexToken> token);

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    void init_context_and_window();
    void setup_builtin_shaders();

    owner<GLWindow>    _mainWindow;

    // Test
    owner<Camera> _camera;

	map< string, owner<Texture> >	                            _textures;
	map< string, owner<Shader> >	                            _shaders;
    map< string, owner<Material> >                              _materials;

    map< weak<Material>,    owner<IBatch>, weak_less<Material>>     _batches;
	map< weak<VertexToken>, weak<IBatch>,  weak_less<VertexToken>>	_batchTokenLookup;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	static Logger LOGGER;

};

template<class VERTEX>
owner<VertexToken> RenderEngine::add_vertices(weak<Material> material, list<VERTEX> vertices)
{
	// #1 Check if batch exists for material, otherwise instanciate one
	if (_batches.count(material) == 0) {
        owner<Batch<VERTEX>> batch = make_owner<Batch<VERTEX>>(material);
        _batches.emplace(material, move(batch));
	}

    // #2 Get batch and add vertices
    weak<IBatch> ibatch = _batches[material].get_non_owner();

    weak<Batch<VERTEX>> batch = static_weak_cast<Batch<VERTEX>>( ibatch );
	owner<VertexToken> token  = batch->add_vertices(vertices);
	_batchTokenLookup.emplace(token.get_non_owner(), ibatch);

    return std::move(token);
}

ENGINE_NAMESPACE_END
