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
### 2.1 Design by contract
Make visible what the function requires and can ensure after its execution.

    Requires( objects.empty() );    // Required by the function to work properly
    Assert( objects.size() == 1);   // Some in-function check of sanity 
    Ensures( objects.size() > 0 );  // What the function can ensure after its execution

