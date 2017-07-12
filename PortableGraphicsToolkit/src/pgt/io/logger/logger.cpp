#include "logger.h"
#include <iostream>
#include <ctime>


namespace pgt {

#if PGT_OS_WINDOWS
#include <windows.h>
    // 0 Black|1 BLUE|2 GREEN|3 AQUA|4 RED|5 PURPLE|6 YELLOW|7 WHITE|8 GRAY|9
    // LIGHTBLUE|A LIGHT GREEN|BRIGHT AQUA|C LIGHT RED|D LIGHT PURPLE|E LIGHT
    // YELLOW|F BRIGHT WHITE  0x[background][foreground]
    const WORD COLORS[] = {0x0A, 0x0E, 0x0C, 0xC0, 0x0D};
    HANDLE inputHld = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE outputHdl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif
    const char* LOG_LEVEL_NAMES[]{" [INFO]", " [WARN]", "[ERROR]", "[FATAL]",
                                  "[DEBUG]"};

    void log(char log_level, const std::string& text)
    {
        const char* time = getTimeChr();
#if PGT_OS_WINDOWS
        GetConsoleScreenBufferInfo(outputHdl, &csbi);
        SetConsoleTextAttribute(outputHdl, COLORS[log_level]);
#endif
        printf("%s %s: %s\n", time, LOG_LEVEL_NAMES[log_level], text.c_str());
#if PGT_OS_WINDOWS
        SetConsoleTextAttribute(outputHdl, csbi.wAttributes);
#endif
        delete time;
    }
    const char* getTimeChr()
    {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        char* buffer = new char[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", now);
        return buffer;
    }
}