#pragma once

#ifndef ENGINE_DEBUG_H
#define ENGINE_DEBUG_H

#include <iostream>
#include <format>

class Logger
{
public:
    Logger(){};
    static void Log(std::string message);
    static void Error(std::string message, bool throwMessageBox = false, bool killProcess = false);
    static void Warning(std::string message);
};

#endif