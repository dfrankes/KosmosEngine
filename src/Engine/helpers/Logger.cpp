#include "Logger.hpp"
#include <iostream>

#include <chrono>
#include <ctime>

#include <string.h>

#include <windows.h>

#define LOGGER_PRETTY_TIME_FORMAT "%y-%m-%d %H:%M:%S"
#define LOGGER_PRETTY_MS_FORMAT ".%03d"

#pragma region time

// strftime format

template <typename T>
static int to_ms(const std::chrono::time_point<T> &tp)
{
    using namespace std::chrono;

    auto dur = tp.time_since_epoch();
    return static_cast<int>(duration_cast<milliseconds>(dur).count());
}

static std::string pretty_time()
{
    auto tp = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(tp);
    std::tm *time_info = std::localtime(&current_time);
    char buffer[128];
    int string_size = strftime(
        buffer, sizeof(buffer),
        LOGGER_PRETTY_TIME_FORMAT,
        time_info);
    int ms = to_ms(tp) % 1000;
    string_size += std::snprintf(
        buffer + string_size, sizeof(buffer) - string_size,
        LOGGER_PRETTY_MS_FORMAT, ms);
    return std::string(buffer, buffer + string_size);
}
#pragma endregion time

void Logger::Log(std::string message)
{
    std::cout << "[" << pretty_time() << "]"
              << "[Engine][LOG] " << message.c_str() << std::endl;
}

void Logger::Error(std::string message, bool throwMessageBox, bool killProcess)
{
    std::cout << "[" << pretty_time() << "]"
              << "[Engine][ERROR] "
              << "\033[1;31m" << message << "\033[0m" << std::endl;

    if (throwMessageBox)
    {
        MessageBox(0, message.c_str(), MB_OK, MB_ICONEXCLAMATION);
    }
    if (killProcess)
    {
        exit(-1);
    }
}

void Logger::Warning(std::string message)
{
    std::cout << "[" << pretty_time() << "]"
              << "[Engine][WARNING] "
              << "\033[1;36m" << message.c_str() << "\033[0m" << std::endl;
}