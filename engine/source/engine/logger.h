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
        using std::ostringstream;

// Other Includes
#include "glew.h"

// Internal Includes
#include "_global.h"
#include "vectorutils.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

#define GL_ERR(level, prettyfunc, line) LOGGER.glerr(level) << prettyfunc << "::" << line << endl;

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

    ostream& log(Level level) {
        return get_stream(level, _className) << get_log_level_name(level) << " - " << _className << " - ";
    }

    ostream& log(Level level, uint32_t instanceId) {
        return log(level) << "[" << instanceId << "] - ";
    }

    ostream& log_(Level level) {
        return get_stream(level, _className);
    }

    static void glerr(string function, int line, string glFunc) {
        GLenum err = glGetError();

        if (err != GL_NO_ERROR) {
            std::cerr << function << ":" << line << "@" << glFunc << ":" <<endl;
            while (err != GL_NO_ERROR) {
                std::cerr << "    GL ERROR: " << gl_err_to_string(err) << endl;
                err = glGetError();
            }
        }
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
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                     Private Static                     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    static string get_log_level_name(Level level) {
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

    static ostream& get_stream(Level level, string className) {
        if (is_logging_enabled(level, className)) {
            return cout;
        }

        SILENT_STREAM.clear();
        return SILENT_STREAM;
    }

    static bool is_logging_enabled(Level level, string className) {
        if (VectorUtils<string>::contains(DISABLED_CLASS_NAMES, className)) {
            return false;
        }

        if (!VectorUtils<Level>::contains(ENABLED_LOG_LEVELS, level)) {
            return false;
        }

        return true;
    }

    static string gl_err_to_string(GLenum error) {
        switch (error) {
            case GL_NO_ERROR: return "No error";
            case GL_INVALID_ENUM: return "Invalid Enum";
            case GL_INVALID_VALUE: return "Invalid Value";
            case GL_INVALID_OPERATION: return "Invalid Operation";
            case GL_STACK_OVERFLOW: return "Stack overflow";
            case GL_STACK_UNDERFLOW: return "Stack underflow";
            case GL_OUT_OF_MEMORY: return "Out of memory";
            case GL_TABLE_TOO_LARGE: return "Table too large";
        }

        return "Invalid GLenum given!";
    }

    static vector<Level>  ENABLED_LOG_LEVELS;
    static vector<string> DISABLED_CLASS_NAMES;
    static ostringstream  SILENT_STREAM;
    static bool           INITIALIZED;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Public                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END
