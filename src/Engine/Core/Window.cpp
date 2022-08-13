#include "Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Helpers/Debug.h"
#include <string>
#include <format>
#include <cassert>

void resizeCallback(GLFWwindow *window, int width, int height);

int Window::m_height = 0;
int Window::m_width = 0;
GLFWwindow *Window::m_window = NULL;

void Window::create(int width, int height, const char *windowTitle)
{
    Debug::Log(std::format("Window::create({},{},{})", width, height, windowTitle));

    m_windowTitle = windowTitle;
    m_width = width;
    m_height = height;

    // Setup GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create the window
    m_window = glfwCreateWindow(m_width, m_height, windowTitle, NULL, NULL);
    if (m_window == NULL)
    {
        Debug::Error("Failed to create GLFW window");
        glfwTerminate();
    }

    // Set OpenGL Window Context
    glfwMakeContextCurrent(m_window);
    glfwSetWindowSizeCallback(m_window, resizeCallback);
    glfwSetWindowUserPointer(m_window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Debug::Error("Failed to initialize GLAD");
    }

    // Test render roop
    while (!glfwWindowShouldClose(m_window))
    {
        // input
        // -----
        // processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        // ourShader.use();
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

// Return the GLFW Window
GLFWwindow *Window::getWindow()
{
    return m_window;
}

// Return the current window width
int Window::getWidth()
{
    return m_width;
}

// Return the current window height
int Window::getHeight()
{
    return m_height;
}

void Window::update()
{
    glfwPollEvents();
}

void Window::render()
{
    glfwSwapBuffers(m_window);
}

void Window::clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void resizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}