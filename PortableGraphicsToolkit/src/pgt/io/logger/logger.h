#pragma once
#include <pgt/target_settings/system_settings.h>
#include <pgt/target_settings/target_settings.h>
#include <pgt/utils/string/string_utils.h>
#include <string>
#include <assert.h>
#define PGT_LOG_LEVEL_INFO 0
#define PGT_LOG_LEVEL_WARN 1
#define PGT_LOG_LEVEL_ERROR 2
#define PGT_LOG_LEVEL_FATAL 3
#define PGT_LOG_LEVEL_DEBUG 4
namespace pgt {
    void log(char log_level, const std::string& text);
    // void redirectLogToFile(const char* filename); TODO
    const char* getTimeChr();
}
#if PGT_OS_WINDOWS
#define PGT_PAUSE system("pause");
#else
#define PGT_PAUSE std::getchar();
#endif

#if PGT_DEBUG
#define PGT_DEBUG_ONLY(command) command
#define PGT_DEBUG_ASSERT(assertion, ...) PGT_ASSERT(assertion, __VA_ARGS__)
#define PGT_LOG_DEBUG(...) PGT_LOG(PGT_LOG_LEVEL_DEBUG, __VA_ARGS__)
#define PGT_ERROR_BREAK __debugbreak();
#else
#define PGT_DEBUG_ONLY(command)
#define PGT_DEBUG_ASSERT(assertion, ...)
#define PGT_LOG_DEBUG(...)
#define PGT_ERROR_BREAK                                                         \
    {                                                                          \
        PGT_PAUSE exit(-1);                                                     \
    }
#endif
#if PGT_COMPILER_GNUCPP
    #define PGT_LOG(log_level, msg, ...)  pgt::log(log_level, pgt::makeStr(msg, ##__VA_ARGS__))
#else
    #define PGT_LOG(log_level, msg, ...)  pgt::log(log_level, pgt::makeStr(msg, __VA_ARGS__))
#endif


#define PGT_LOG_INFO(...) PGT_LOG(PGT_LOG_LEVEL_INFO, __VA_ARGS__)
#define PGT_LOG_WARN(...) PGT_LOG(PGT_LOG_LEVEL_WARN, __VA_ARGS__)
#define PGT_LOG_ERROR(...) PGT_LOG(PGT_LOG_LEVEL_ERROR, __VA_ARGS__)
#define PGT_LOG_FATAL(...) PGT_LOG(PGT_LOG_LEVEL_FATAL, __VA_ARGS__)
#define PGT_ASSERT(assertion, ...)                                              \
    if (!(assertion)) {                                                        \
        PGT_LOG_FATAL("ASSERTION FAILED in %s: Line %i:\n    %s",               \
                     pgt::getFileNameFromPath(__FILE__), __LINE__,              \
                     pgt::makeStr(__VA_ARGS__).c_str());                        \
        PGT_ERROR_BREAK                                                         \
    }
#define PGT_OUT_OF_RANGE_EXIT(ret_val)                                          \
    {                                                                          \
        PGT_ASSERT(false, "The Argument is out of Range!") return ret_val;      \
    }
