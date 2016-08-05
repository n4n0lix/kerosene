# kerosene
- gameengine
- c++
- cross-platform (linux/windows)(x86/x64)
- opengl 3.3

## 1. introduction
#### building
##### windows
* microsoft visual studio 2015
use the provided solution `engine.sln`.

##### linux
* todo

## 2. code
### 2.1 contract
make visible what the function requires and ensures after its execution.

    Requires( <bool> ); // Required by the function to work properly
    Assert( <bool> );   // Some in-function check of sanity 
    Ensures( <bool> );  // What the function can ensure after its execution

### 2.2 guard
make guard-checks visible.

    Guard( <bool> ) return;

## 3. design
### 3.1 render-engine
#### vertex
it's common to use different vertex types for different shaders. for example in one shader we only need the position (**vec3**) and the color (**vec4**), but for another shader we might add texture coordiantes (**vec2**). we can easiely declare new vertex types in the render-engine by creating a new class that derives from *Vertex*. all we have to do now is to implement the three virtual methods like for example we did for *Vertex_pc* that contains a position (**vec3**) and a color (**vec4**).

first we declare the layout of the vertex in the shader. this enables us to access the attributes of the vertex class later via this attribute names in the shader. the order of this layout is important for the next method to implement *Vertex::data()*.

    VertexLayout Vertex_pc::layout() const
    {
        return{ { {"vec3", "position", 1}, 
                  {"vec4", "color",    2} } };
    }

next we write the vertexs data into a vector so that the renderengine can submit it to the gpu. it is important that the order of attributes are corresponding to the vertex layout we defined above.

    vector<float> Vertex_pc::data() const
    {
        vector<float> data;
        data.reserve(7);
        data.push_back(position.x);
        data.push_back(position.y);
        data.push_back(position.z);
        data.push_back(color.x);
        data.push_back(color.y);
        data.push_back(color.z);
        data.push_back(color.w);
        return std::move(data);
    }

this method has to simply returns the size of the vertex in bytes.

    uint32 Vertex_pc::bytesize() const 
    { 
        return 3 * FLOAT_BYTES + 4 * FLOAT_BYTES; 
    }
