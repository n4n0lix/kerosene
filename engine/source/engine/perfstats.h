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

enum PerfType {
    TEXTURE_LOADED,
    SHADER_LOADED,
    VERTICES_LOADED,
    DRAW_CALL
};

struct FrameStats {
    // Meta
    uint64 time;

    // General
    uint32 numDrawCalls;
    uint32 numGPUCalls;
    uint64 duration;
    uint32 amountBytesSend;
};

struct TickStats {
    // Meta
    uint64 time;

    // General
    uint64 duration;
};

class PerfStats
{
public:

    typedef std::chrono::milliseconds                     milliseconds_t;
    typedef std::chrono::high_resolution_clock            clock_t;
    typedef std::chrono::duration<double, milliseconds_t> duration_t;

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

    }

    inline void tick_end() {

    }

    // FRAME
    inline void frame_start() {
        _frameClockStart = std::chrono::high_resolution_clock::now();
        _numPolygons = _counterPolygons;
        _numDrawCalls = _counterDrawCalls;
        _counterPolygons = 0;
        _counterDrawCalls = 0;
    }

    inline void frame_gpu_call() {
        _curFrameStat.numGPUCalls += 1;
    }

    inline void frame_draw_call(uint32 numPolygons) {
        _counterDrawCalls++;
        _counterPolygons += numPolygons;
    }

    inline void frame_load_texture() {
        _numLoadedTextures++;
    }

    inline void frame_load_shader() {
        _numLoadedShaders++;
    }

    inline void frame_unload_texture() {
        _numLoadedTextures--;
    }

    inline void frame_unload_shader() {
        _numLoadedShaders--;
    }

    inline void frame_end() {
        check_if_second_is_over();

        _lastFrameStat = _curFrameStat;
        _counterFPS++;

        milliseconds_t timeSpan = std::chrono::duration_cast<milliseconds_t>(clock_t::now() - _frameClockStart);
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

    FrameStats          _curFrameStat;
    FrameStats          _lastFrameStat;

    uint32              _numLoadedShaders;
    uint32              _numLoadedTextures;

    uint32 _numFPS;
    uint32 _counterFPS;

    uint32 _numPolygons;
    uint32 _counterPolygons;

    uint32 _numDrawCalls;
    uint32 _counterDrawCalls;

    std::chrono::milliseconds _avgFrameTime;
    std::chrono::milliseconds _counterAvgFrameTime;

    std::chrono::high_resolution_clock::time_point _clockStart;
    std::chrono::high_resolution_clock::time_point _frameClockStart;

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
