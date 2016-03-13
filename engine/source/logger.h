#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <vector>
        using std::vector;

#include <algorithm>
        using std::transform;

#include <sstream>
        using std::stringstream;
        using std::ostream;

// Other Includes

// Internal Includes
#include "_global.h"
#include "vectorutils.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

enum DLL_PUBLIC Level {
    DEBUG_RENDERING,
    DEBUG_LOGIC,

    INFO_RENDERING,
    INFO_LOGIC,

    ERROR_RENDERING,
    ERROR_LOGIC
};

class DLL_PUBLIC Logger
{
public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Public Static                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    static void enable(Level level) {
        if (!VectorUtils<Level>::contains(ENABLED_LOG_LEVELS, level)) {
            VectorUtils<Level>::add(ENABLED_LOG_LEVELS, level);
        }
    }

    static void disable(Level level) {
        VectorUtils<Level>::remove(ENABLED_LOG_LEVELS, level);
    }

    static void enable(string className) {
        if (!VectorUtils<string>::contains(DISABLED_CLASS_NAMES, className)) {
            VectorUtils<string>::add(DISABLED_CLASS_NAMES, className);
        }
    }

    static void disable(string className) {
        VectorUtils<string>::remove(DISABLED_CLASS_NAMES, className);
    }

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    Logger(string className) : _className(className) { }

    void log(Level level, ostream& msg) {
        std::cout << getLogLevelName(level) << " - " << _className << " - " << static_cast<std::ostringstream&>(msg).str() << std::endl;
    }


protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    string getLogLevelName(Level level) const {
        switch (level) {
            case DEBUG_RENDERING:   return "DEBUG_RENDERING";
            case DEBUG_LOGIC:       return "DEBUG_LOGIC";
            case INFO_RENDERING:    return "INFO_RENDERING";
            case INFO_LOGIC:        return "INFO_LOGIC";
            case ERROR_RENDERING:   return "ERROR_RENDERING";
            case ERROR_LOGIC:       return "ERROR_LOGIC";
        }

        return "--";
    }

    string _className;
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static vector<Level>  ENABLED_LOG_LEVELS;
    static vector<string> DISABLED_CLASS_NAMES;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
