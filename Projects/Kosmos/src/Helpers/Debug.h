#ifndef ENGINE_DEBUG_H
#define ENGINE_DEBUG_H

#include <iostream>

class Debug
{
    public:
        static void Log(std::string message);
        static void Error(char* message, bool throwMessageBox = false, bool killProcess = false);
        static void Warning(char* message);
    private:
        Debug(){}
};

#endif