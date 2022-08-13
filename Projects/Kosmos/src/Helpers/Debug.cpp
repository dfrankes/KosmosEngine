#include "debug.h"
#include <iostream>

#include <chrono>
#include <ctime>

#include <string.h>

#include <windows.h>

#define LOGGER_PRETTY_TIME_FORMAT "%y-%m-%d %H:%M:%S"
#define LOGGER_PRETTY_MS_FORMAT ".%03d"
#pragma region time

// strftime format


// convert current time to milliseconds since unix epoch
template <typename T>
static int to_ms(const std::chrono::time_point<T>& tp)
{
    using namespace std::chrono;

    auto dur = tp.time_since_epoch();
    return static_cast<int>(duration_cast<milliseconds>(dur).count());
}

// format it in two parts: main part with date and time and part with milliseconds
static std::string pretty_time()
{
    auto tp = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(tp);

    // this function use static global pointer. so it is not thread safe solution
    std::tm* time_info = std::localtime(&current_time);

    char buffer[128];

    int string_size = strftime(
        buffer, sizeof(buffer),
        LOGGER_PRETTY_TIME_FORMAT,
        time_info
    );

    int ms = to_ms(tp) % 1000;

    string_size += std::snprintf(
        buffer + string_size, sizeof(buffer) - string_size,
        LOGGER_PRETTY_MS_FORMAT, ms
    );

    return std::string(buffer, buffer + string_size);
}
#pragma endregion time


void Debug::Log(std::string message)
{
    std::cout << "[" << pretty_time() << "]" << "[Engine][LOG] " << message.c_str() << std::endl;
}

void Debug::Error(char message[], bool throwMessageBox, bool killProcess)
{
    std::cout << "[" << pretty_time() << "]" << "[Engine][ERROR] " << "\033[1;31m" << message << "\033[0m" << std::endl;

    if(throwMessageBox)
    {
        MessageBox(0, message, MB_OK, MB_ICONEXCLAMATION);
    }
    if(killProcess)
    {
        exit(-1);
    }
}

void Debug::Warning(char message[])
{
    std::cout << "[" << pretty_time() << "]" << "[Engine][WARNING] " << "\033[1;36m" << message << "\033[0m" << std::endl;
}