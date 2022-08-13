#include "Kosmos.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Helpers/Debug.h"
#include "Core/Window.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Kosmos::Kosmos()
{
    Debug::Log("Constructing Kosmos Engine...");

    Debug::Log("Creating default Engine Window");
    Window window;
    window.create(SCR_WIDTH, SCR_HEIGHT, "Kosmos");

    m_window = window;
    return;
}

void Kosmos::run()
{
    Debug::Log("Loading the Kosmos...");
}