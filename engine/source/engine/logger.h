#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <sstream>

// Other Includes

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

enum class Level {
    OFF,
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger
{
public:

    static bool SUPPRESS_OUTPUT;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    Logger(string className, Level level) : _className(className), _level(level), _silentOutput(std::ostringstream()) { }

    std::ostream& log(Level level) {
        return get_stream(level) << get_log_level_name(level) << " - " << _className << " - ";
    }

    std::ostream& log(Level level, uint32_t instanceId) {
        return log(level) << "[" << instanceId << "] - ";
    }

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    string          _className;
    Level           _level;

    std::ostringstream   _silentOutput;
    
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

    std::ostream& get_stream(Level level) {
        if (_level == Level::ERROR && (level == Level::ERROR)) {
            return cout;
        }

        if (_level == Level::WARN && (level == Level::ERROR || level == Level::WARN)) {
            return cout;
        }

        if (_level == Level::INFO && (level == Level::ERROR || level == Level::WARN || level == Level::INFO)) {
            return cout;
        }

        if (_level == Level::DEBUG) {
            return cout;
        }

        _silentOutput.clear();
        return _silentOutput;
    }

};

ENGINE_NAMESPACE_END
