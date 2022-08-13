#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Helpers/Debug.h"
#include "Core/Window.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Engine::Engine()
{
    return;
}

bool Engine::drawWindow()
{
    Debug::Log("Loading the Kosmos...");
    Window window;
    window.create(600, 800, "Hello World");
    return 0;
}