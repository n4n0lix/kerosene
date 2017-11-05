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

    inline void frame_draw_call(size_t numPolygons) {
        _counterDrawCalls++;
        _counterPolygons += numPolygons;
    }

    inline void frame_load_texture( size_t imgDataBytes) {
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

            size_t _numLoadedShaders;
    size_t _numLoadedTextures;
    size_t _numLoadedTexturesBytes;

    size_t _numFPS;
    size_t _counterFPS;

    size_t _numPolygons;
    size_t _counterPolygons;

    size_t _numDrawCalls;
    size_t _counterDrawCalls;

    size_t _numTPS;
    size_t _counterTPS;

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
