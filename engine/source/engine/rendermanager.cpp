#include "rendermanager.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

RenderManager::RenderManager()
{
    setup_builtin_shaders();
}

void RenderManager::remove_vertices(s_ptr<VertexToken> token)
{
    s_ptr<IBatch> batch = _tokenToBatches[ token ]; 

    if (batch != nullptr) {
        batch->remove_vertices(token);
    }
}

void RenderManager::add_render(s_ptr<VertexToken> token)
{
    s_ptr<IBatch> batch = _tokenToBatches[ token ];

    if (batch != nullptr) {
        batch->add_render(token);
    }
}

void RenderManager::remove_render(s_ptr<VertexToken> token)
{
    s_ptr<IBatch> batch = _tokenToBatches[token];

    if (batch != nullptr) {
        batch->remove_render(token);
    }
}

void RenderManager::render()
{
    // 1# get all batches
    Vector<s_ptr<IBatch>> batches = Vector<s_ptr<IBatch>>();

    for (pair<w_ptr<Material>, s_ptr<IBatch>> entry : _materialToBatches) {
        if (!batches.contains(entry.second)) {
            batches.add(entry.second);
        }
    }

    // 2# render all batches
    for each (s_ptr<IBatch> batch in batches)
    {
        batch->render();
    }
}

s_ptr<Texture> RenderManager::load_texture(string filename, TextureOptions options)
{

    // 1# Check if texture is already loaded. TODO: This currently ignores texture options
    w_ptr<Texture> weak = _fileToTextures.get(filename);
    if (!weak.expired()) {
        return weak.lock();
    }

    // 2# Load Texture
    s_ptr<Texture> texture;
    s_ptr<Image> image;

    // PNG
    if (StringUtils::ends_with(filename, ".png")) {
        image = ImageUtils::load_png(filename);
    }

    texture = make_shared<Texture>(image, options);
    _fileToTextures.put(filename, texture);
    return texture;
}

s_ptr<Texture> RenderManager::overwrite_texture(string filename, s_ptr<Texture> texture)
{
    _fileToTextures.put(filename, texture);
    return texture;
}

s_ptr<Shader> RenderManager::load_shader(string filename)
{
    s_ptr<Shader> shader;

    // 1# Check if shader is already loaded. TODO: This currently ignores texture options
    w_ptr<Shader> weak = _fileToShader.get(filename);
    if (!weak.expired()) {
        return weak.lock();
    }

    if (shader != nullptr) {
        return shader;
    }

    // 2# Try to load from built-in-shaders
    s_ptr<Shader> builtIn = _builtinShaders.get(filename);
    if (builtIn != nullptr) {
        return builtIn;
    }

    // 3# Load Shader from file
    // TODO:

    LOGGER.log(Level::WARN) << "Shader '" << filename << "' not found!";

    return nullptr;
}

s_ptr<Material> RenderManager::load_material(s_ptr<Shader> shader, s_ptr<Texture> texture)
{
    return s_ptr<Material>();
}

s_ptr<Shader> RenderManager::built_in_shader(string filename, s_ptr<Shader> shader)
{
    _builtinShaders.put(filename, shader);
    return shader;
}

void RenderManager::setup_builtin_shaders()
{
    // VERTEX LAYOUTS
    s_ptr<VertexLayout> pcLayout = make_shared<VertexLayout>(Vertex_pc().layout());
    s_ptr<VertexLayout> ptLayout = make_shared<VertexLayout>(Vertex_pt().layout());

    // SETUP BUILT-IN SHADER
    // COLOR SHADER
    ///////////
    ostringstream csVertexShader;
    csVertexShader
        << "out vec4 fs_color;\n"
        << "\n"
        << "void main() {\n"
        << "    gl_Position = vec4(position, 1.0);\n"
        << "    fs_color = color;\n"
        << "}\n";

    ostringstream csFragmentShader;
    csFragmentShader
        << "in vec4 fs_color;\n"
        << "\n"
        << "out vec4 out_color;\n"
        << "\n"
        << "void main() {\n"
        << "    out_color = fs_color;\n"
        << "}\n";

    s_ptr<Shader> colorShader = ShaderBuilder()
        .vertex_uniform("mat4", "uni_wvp")
        .vertexlayout(pcLayout)
        .vertex_source(csVertexShader.str())
        .frag_source(csFragmentShader.str())
        .build();

    built_in_shader("builtin_diffuse", colorShader);

    // TEXTURE SHADER
    ///////////
    ostringstream tsVertexShader;
    tsVertexShader
        << "out vec2 fs_texcoords;\n"
        << "\n"
        << "void main() {\n"
        << "    gl_Position = vec4(position, 1.0);\n"
        << "    fs_texcoords = texcoords;\n"
        << "}\n";

    ostringstream tsFragmentShader;
    tsFragmentShader
        << "in vec2 fs_texcoords;\n"
        << "\n"
        << "out vec4 out_color;\n"
        << "\n"
        << "void main() {\n"
        << "    out_color = texture(" << TextureSlotTemplate::TEXTURE_DIFFUSE.name << ", fs_texcoords);\n"
        << "}\n";

    s_ptr<Shader> texShader = ShaderBuilder()
        .vertex_uniform("mat4", "uni_wvp")
        .frag_texture_slot(TextureSlotTemplate::TEXTURE_DIFFUSE)
        .vertexlayout(ptLayout)
        .vertex_source(tsVertexShader.str())
        .frag_source(tsFragmentShader.str())
        .build();

    built_in_shader("builtin_texture", texShader);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Logger RenderManager::LOGGER = Logger("RenderManager", Level::DEBUG);

ENGINE_NAMESPACE_END