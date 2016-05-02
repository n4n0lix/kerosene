#include "logger.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

vector<Level>  Logger::ENABLED_LOG_LEVELS = vector<Level>();
vector<string> Logger::ENABLED_CLASS_NAMES = vector<string>();
ostringstream  Logger::SILENT_STREAM = ostringstream();
bool           Logger::INITIALIZED = false;