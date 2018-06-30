#pragma once

// Std-Includes
#include <sstream>
#include <chrono>
#include <iomanip>

// Other Includes

// Internal Includes
#include "_global.h"

ENGINE_NAMESPACE_BEGIN

typedef std::chrono::high_resolution_clock            clock_t;

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
    static clock_t::time_point  APP_START;
    static bool                 SUPPRESS_OUTPUT;

            Logger( string className, Level level ) : _className( className ), _level( level ), _silentOutput( std::ostringstream() ) { }

    std::ostream& log( Level level ) {
        auto msTotal = (clock_t::now() - APP_START).count() / 1000000;
        auto ms = msTotal % 1000;
        auto s = (msTotal / 1000) % 60;
        auto m = (msTotal / 1000 / 60) % 60;

        return get_stream( level ) << "[" 
            << std::setfill( '0' ) << std::setw( 2 ) << m << ":"
            << std::setfill( '0' ) << std::setw( 2 ) << s << ":"
            << std::setfill( '0' ) << std::setw( 3 ) << ms
            << "] " << get_log_level_name( level ) << " - " << _className << " - ";
    }

    std::ostream& log( Level level, uint32_t instanceId ) {
        return log( level ) << "[" << instanceId << "] - ";
    }

private:

            string               _className;
            Level                _level;
            std::ostringstream   _silentOutput;


    static string get_log_level_name( Level level ) {
        switch ( level ) {
            case Level::DEBUG:       return "DEBUG";
            case Level::INFO:        return "INFO";
            case Level::ERROR:       return "ERROR";
        }

        return "--";
    }

    std::ostream& get_stream( Level level ) {
        if ( _level == Level::ERROR && (level == Level::ERROR) ) {
            return cout;
        }

        if ( _level == Level::WARN && (level == Level::ERROR || level == Level::WARN) ) {
            return cout;
        }

        if ( _level == Level::INFO && (level == Level::ERROR || level == Level::WARN || level == Level::INFO) ) {
            return cout;
        }

        if ( _level == Level::DEBUG ) {
            return cout;
        }

        _silentOutput.clear();
        return _silentOutput;
    }

};

ENGINE_NAMESPACE_END
