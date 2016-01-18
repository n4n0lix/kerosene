// Header
#include "batch.h"
ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Batch::Batch(shared_ptr<Material> material) {
    _material = material;
    _shader = material->getShader();

    _vboByteSize = 0;
    _vboNumVertices = 0;

    // VAO
    glGenVertexArrays(1, &_vaoId);
    glBindVertexArray(_vaoId);

        // VBO
        glGenBuffers(1, &_vboId);
        glBindBuffer(GL_ARRAY_BUFFER, _vboId);
        glBufferData(GL_ARRAY_BUFFER, _vboByteSize, NULL, GL_STATIC_DRAW);

        VertexLayout layout = _shader->getVertexLayout();

        GLuint offset = 0;
        for (VertexComponent component : layout.comps) {
            glEnableVertexAttribArray(component.position);
            glVertexAttribPointer(component.position, component.components(), component.gltype(), false, layout.bytesize(), BUFFER_OFFSET(offset));
            cout << "glVertexAttribPointer( " << component.position << ", " << component.components() << ", " << component.gltype() << ", " << false << ", " << layout.bytesize() << ", " << offset << " )" << endl;
            offset += component.bytesize();
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Batch::render(PrimitiveType type) const
{
    _material->getShader()->bind();

    glBindVertexArray(_vaoId);
    glDrawArrays(type, 0, _vboNumVertices);
    glBindVertexArray(0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
