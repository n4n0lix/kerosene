#pragma once

// Std-Includes
#include <ostream>

// Other Includes

// Internal Includes
#include "_gl.h"

#include "_global.h"
#include "stackbuffer.h"

ENGINE_NAMESPACE_BEGIN

class IndexBuffer : public StackBuffer<uint32>
{
public:
            explicit IndexBuffer( uint32 initCapacity );
            virtual ~IndexBuffer() = default;

    GLuint                      get_id();

    weak<StackBufferToken>      add_indices( std::vector<uint32> indices );
    void                        remove_indices( weak<StackBufferToken> token );

protected:
    virtual void                        native_write( uint32 index, std::vector<uint32> vertices );
    virtual void                        native_resize( uint32 oldCapacity, uint32 newCapacity );
    virtual void                        native_copy( uint32 srcIndex, uint32 destIndex, uint32 length );

private:
    GLuint                          _iboId;
    GLuint                          createIBO( uint32 capacityBytes );

    static Logger LOGGER;
};

ENGINE_NAMESPACE_END