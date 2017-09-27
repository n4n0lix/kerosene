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
    _clockStart = std::chrono::high_resolution_clock::now();
}

void PerfStats::check_if_second_is_over() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> timeSpan = now - _clockStart;

    if ( timeSpan.count() > 1000 ) {
        _clockStart = now;

        //_numTPS = _counterTPS;
        _numFPS = _counterFPS;
        _avgFrameTime = _counterAvgFrameTime / _numFPS;

        //_counterTPS = 0;
        _counterFPS = 0;
        _counterPolygons = 0;
        _counterDrawCalls = 0;
        _counterAvgFrameTime = std::chrono::milliseconds{ 0 };

        cout << "RenderStats\n"
             << "------------------------------\n"
             << "Frames per sec.:   " << _numFPS << "\n"
             << "Avg. Frame Time:   " << _avgFrameTime.count() << "ms\n"
             << "Polygons in scene: " << _numPolygons << "\n"
             << "Draw calls:        " << _numDrawCalls << "\n"
             << "Loaded Textures:  " << _numLoadedTextures << "\n"
             << "Loaded  Shaders:  " << _numLoadedShaders << "\n"
             << "==============================\n\n";
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


ENGINE_NAMESPACE_END