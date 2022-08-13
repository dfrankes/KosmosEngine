#ifndef ENGINE_DEBUG_H
#define ENGINE_DEBUG_H

#include <iostream>

class Debug
{
public:
    static void Log(std::string message);
    static void Error(std::string message, bool throwMessageBox = false, bool killProcess = false);
    static void Warning(std::string message);

private:
    Debug() {}
};

#endif