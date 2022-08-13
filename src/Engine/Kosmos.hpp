#include "Core/Window.hpp"

// This class is exported from the dll
class Kosmos
{
public:
    Kosmos();
    virtual ~Kosmos(){};
    void run();

private:
    Window m_window;
    bool m_isRunning;
};