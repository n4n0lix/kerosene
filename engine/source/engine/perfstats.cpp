#include "stdafx.h"
#include "perfstats.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Private                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

PerfStats::PerfStats() {
    _clockStart = clock_t::now();
}

void PerfStats::check_if_second_is_over() {
    auto now = clock_t::now();
    auto timeSpan = now - _clockStart;

    if ( timeSpan > 1000ms ) {
        _clockStart = now;

        _numTPS = _counterTPS;
        _avgTickTime = (_numTPS > 0) ? (_counterAvgTickTime / _numTPS) : (-1ms);

        _numFPS = _counterFPS;
        _avgFrameTime = (_numFPS > 0) ? (_counterAvgFrameTime / _numFPS) : (-1ms);

        _counterFPS = 0;
        _counterPolygons = 0;
        _counterDrawCalls = 0;
        _counterAvgFrameTime = 0ms;

        _counterTPS = 0;
        _counterAvgTickTime = 0ms;

        cout << "FPS " << _numFPS << "\n";
        return;
        cout << "Perf Stats\n"
             << "------------------------------\n"
             << "RENDER"
             << "\tFrames per sec.:   " << _numFPS << "\n"
             << "\tAvg. Frame Time:   " << _avgFrameTime.count() << "ms\n"
             << "\tPolygons in scene: " << _numPolygons << "\n"
             << "\tDraw calls:        " << _numDrawCalls << "\n"
             << "\tLoaded  Shaders:   " << _numLoadedShaders << "\n"
             << "\tLoaded Textures:   " << _numLoadedTextures << " (" << (_numLoadedTexturesBytes / 1024) << " kb)\n"
             << "------------------------------\n"
             << "LOGIC"
             << "\tTicks per sec.:    " << _numTPS << "\n"
             << "\tAvg. Tick Time:    " << _avgTickTime.count() << "ms\n"
             << "==============================\n\n";
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


ENGINE_NAMESPACE_END