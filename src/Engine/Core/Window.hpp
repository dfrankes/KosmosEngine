#pragma once

#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Window
{
public:
    Window() {}
    ~Window() {}

    void create(int width, int height, const char *windowTitle);

    static GLFWwindow *getWindow();
    static int getWidth();
    static int getHeight();
    static void update();
    static void render();
    static void clear();

private:
    const char *m_windowTitle;
    static GLFWwindow *m_window;
    static int m_width;
    static int m_height;
};