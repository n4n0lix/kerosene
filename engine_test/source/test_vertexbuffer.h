#pragma once

#include "test.h"

#include "_global.h"
#include "vertexbuffer.h"
#include "_renderdefs.h"
#include "vertex_pc.h"

ENGINE_NAMESPACE_BEGIN

//
// BEHAVIOUR
//

BEHAVIOUR(VertexBuffer, if_constructed_allocate_opengl_vbo)

    // 1# Setup test
    shared_ptr<VertexLayout> validLayout = make_shared<VertexLayout>(Vertex_pc().layout());

    // 2# Test
    VertexBuffer<Vertex_pc> vbo(validLayout, 4);

    // 3# Evaluate
    IS_EQUALS(1, GLMock::invocations("glGenBuffers"));

END

//
// PERFORMANCE
//
ENGINE_NAMESPACE_END