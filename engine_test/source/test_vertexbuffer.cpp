#include "catch.h"

#include "_global.h"
#include "vertexbuffer.h"
#include "vertex_pc.h"

ENGINE_NAMESPACE_BEGIN

vector<Vertex_pc> new_vertices(int num) {
    vector<Vertex_pc> vertices = vector<kerosene::Vertex_pc>();
    for (int i = 0; i < num; i++) {
        vertices.push_back(Vertex_pc());
    }
    return vertices;
}

SCENARIO("vertexbuffer are automatically resizing if needed", "[vertexbuffer]") {
    GIVEN("A vertexbuffer with 5 vertices") {
        VertexBuffer<Vertex_pc>   v      = VertexBuffer<Vertex_pc>(Vertex_pc().layout(), 5);
        weak<VertexBufferToken>   token;

        token = v.add_vertices( new_vertices(5) );
        v.commit_write();

        REQUIRE(v.num_vertices() == 5);
        REQUIRE(v.object_capacity() == 5);

        WHEN("vertices are added") {
            token = v.add_vertices( new_vertices(5) );
            v.commit_write();

            THEN("the size and capacity increased") {
                REQUIRE(v.object_capacity() > 5);
                REQUIRE(v.num_vertices() > 5);
            }
        }
        WHEN("vertices are removed") {
            v.remove_vertices(token);
            v.commit_remove();

            THEN("the size changes but not capacity") {
                REQUIRE(v.num_vertices() == 0);
                REQUIRE(v.object_capacity() == 5);
            }
        }
    }
}

SCENARIO("vertexbuffer only writes necessery data during a commit", "[vertexbuffer]") {
    GIVEN("A vertexbuffer ") {
        auto v = VertexBuffer<Vertex_pc>(Vertex_pc().layout(), 5);

        REQUIRE(v.object_capacity() == 5);
        REQUIRE(v.num_vertices() == 0);

        WHEN("the same vertices are added and removed before commiting") {
            auto token = v.add_vertices(new_vertices(10));
            v.remove_vertices(token);
            v.commit_write();

            THEN("size and capacity won't change") {
                REQUIRE(v.object_capacity() == 5);
                REQUIRE(v.num_vertices() == 0);
            }
        }
    }
}

ENGINE_NAMESPACE_END