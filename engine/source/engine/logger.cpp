#include "logger.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
vector<Level>  Logger::ENABLED_LOG_LEVELS = { DEBUG_RENDERING, DEBUG_LOGIC, INFO_RENDERING, INFO_LOGIC, ERROR_RENDERING, ERROR_LOGIC };
vector<string> Logger::DISABLED_CLASS_NAMES = vector<string>();
ostringstream  Logger::SILENT_STREAM = ostringstream();
bool           Logger::INITIALIZED = false;

ENGINE_NAMESPACE_END
