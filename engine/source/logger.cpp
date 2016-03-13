#include "logger.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Private Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
vector<Level>  Logger::ENABLED_LOG_LEVELS = vector<Level>();
vector<string> Logger::DISABLED_CLASS_NAMES = vector<string>();

ENGINE_NAMESPACE_END
