#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <chrono>
#include <ctime>

// Other Includes

// Internal Includes
#include "_global.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class PerfStats
{

    typedef std::chrono::high_resolution_clock            clock_t;
    typedef std::chrono::duration<double, milliseconds>   duration_t;

public:

    static PerfStats& instance() {
        static PerfStats INSTANCE;
        return INSTANCE;
    }

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            ~PerfStats() = default;

    // TICK
    inline void tick_start() {
        _tickClockStart = clock_t::now();
    }

    inline void tick_end() {
        check_if_second_is_over();

        _counterTPS++;

        milliseconds timeSpan = std::chrono::duration_cast<milliseconds>(clock_t::now() - _frameClockStart);
        _counterAvgTickTime += timeSpan;
    }

    // FRAME
    inline void frame_start() {
        _frameClockStart = clock_t::now();
        _numPolygons = _counterPolygons;
        _numDrawCalls = _counterDrawCalls;
        _counterPolygons = 0;
        _counterDrawCalls = 0;
    }

    inline void frame_gpu_call() {

    }

    inline void frame_draw_call(uint32 numPolygons) {
        _counterDrawCalls++;
        _counterPolygons += numPolygons;
    }

    inline void frame_load_texture(uint32 imgDataBytes) {
        _numLoadedTextures++;
        _numLoadedTexturesBytes += imgDataBytes;
    }

    inline void frame_load_shader() {
        _numLoadedShaders++;
    }

    inline void frame_unload_texture( uint32 imgDataBytes ) {
        _numLoadedTextures--;
        _numLoadedTexturesBytes -= imgDataBytes;
    }

    inline void frame_unload_shader() {
        _numLoadedShaders--;
    }

    inline void frame_end() {
        check_if_second_is_over();

        _counterFPS++;

        milliseconds timeSpan = std::chrono::duration_cast<milliseconds>(clock_t::now() - _frameClockStart);
        _counterAvgFrameTime += timeSpan;
    }

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            PerfStats();

            void   check_if_second_is_over();

    uint32 _numLoadedShaders;
    uint32 _numLoadedTextures;
    uint32 _numLoadedTexturesBytes;

    uint32 _numFPS;
    uint32 _counterFPS;

    uint32 _numPolygons;
    uint32 _counterPolygons;

    uint32 _numDrawCalls;
    uint32 _counterDrawCalls;

    uint32 _numTPS;
    uint32 _counterTPS;

    milliseconds _avgFrameTime;
    milliseconds _counterAvgFrameTime;
    milliseconds _avgTickTime;
    milliseconds _counterAvgTickTime;

    std::chrono::high_resolution_clock::time_point _clockStart;
    std::chrono::high_resolution_clock::time_point _frameClockStart;
    std::chrono::high_resolution_clock::time_point _tickClockStart;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
