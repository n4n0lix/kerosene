# kerosene
- gameengine
- c++
- cross-platform (linux/windows)(x86/x64)
- opengl 3.3

Based on OrangeStar-Engine and what we've learned from the mistakes we've made building it ;)

## Windows
##### Requirements
* Microsoft Visual Studio 2015

Use the provided solution `engine.sln` that includes the projects`engine`, `engine_test` and `engine_sandbox`.
## Linux
##### Requirements
* cmake
* glew-1.13
* gcc

Use one of the provided compile scripts
 * `compile-linux-gcc-linux32-debug.sh`
 * `compile-linux-gcc-linux32-release.sh`
 * `compile-linux-gcc-linux64-debug.sh`
 * `compile-linux-gcc-linux64-release.sh`
