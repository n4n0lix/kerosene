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

## 2. coding conventions
### 2.1 contract
make visible what the function requires and can ensure after its execution.

    Requires( <bool> ); // Required by the function to work properly
    Assert( <bool> );   // Some in-function check of sanity 
    Ensures( <bool> );  // What the function can ensure after its execution

### 2.2 guards
make guard-checks visible.

    Guard( <bool> ) return;
