#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include "_gl.h"
#include "_global.h"

#include <cstdio>

int main(int argc, char* argv[])
{
    // global setup...

    int result = Catch::Session().run(argc, argv);

    // global clean-up...

    std::cout << "Press anykey to exit the program ...";
    std::getchar();

    return (result < 0xff ? result : 0xff);
}