#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <iostream>
        using std::cout;

#include <vector>
        using std::vector;

#include <algorithm>
        using std::transform;

#include <string>
        using std::string;

#include <sstream>
        using std::stringstream;
        using std::ostream;
        using std::ostringstream;

// Other Includes

// Internal Includes
#include "vectorutils.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

enum class Level {
    OFF,
    DEBUG,
    INFO,
    ERROR
};

class Logger
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    Logger(string className, Level level) : _className(className), _level(level) {  }

    ostream& log(Level level) {
        return get_stream(level, _className) << get_log_level_name(level) << " - " << _className << " - ";
    }

    ostream& log(Level level, uint32_t instanceId) {
        return log(level) << "[" << instanceId << "] - ";
    }

    ostream& log_(Level level) {
        return get_stream(level, _className);
    }

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    string _className;
    Level  _level;
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static string get_log_level_name(Level level) {
        switch (level) {
            case Level::DEBUG:       return "DEBUG";
            case Level::INFO:        return "INFO";
            case Level::ERROR:       return "ERROR";
        }

        return "--";
    }

    ostream& get_stream(Level level, string className) {
        if (level >= _level) {
            return cout;
        }

        SILENT_STREAM.clear();
        return SILENT_STREAM;
    }

    static ostringstream  SILENT_STREAM;
};