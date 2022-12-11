#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../Kosmos.hpp"
#include "Engine.hpp"

#include "core/Shader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <format>
#include <cassert>

#include "DevUI.hpp"

static GLFWwindow *m_window;
DevUI devUI;

bool mouseEnabled = false;

void resizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

Engine::Engine()
{
    Kosmos::logger.Log("Engine::Engine()");
    lastFrame = 0.0f;
    deltaTime = 0.0f;
}
void Engine::init()
{

    // Setup GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create the window
    m_window = glfwCreateWindow(1280, 720, std::string("Kosmos::Engine").c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        Kosmos::logger.Error("Failed to create GLFW Window!");
        glfwTerminate();
    }

    // Set OpenGL Window Context
    glfwMakeContextCurrent(m_window);
    glfwSetWindowSizeCallback(m_window, resizeCallback);
    glfwSetWindowUserPointer(m_window, this);

    // tell GLFW to capture our mouse
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Kosmos::logger.Error("Failed to initialize GLAD");
    }

    // More window stuff
    glEnable(GL_DEPTH_TEST);

    // callbacks
    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetScrollCallback(window, scroll_callback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    Kosmos::logger.Log("Preloading shaders");
    Shader defaultShader("resources/shaders/1.2.pbr.vs", "resources/shaders/1.2.pbr.fs");
    Shader lightingShader("resources/shaders/lightingShader.vs.glsl", "resources/shaders/lightingShader.fs.glsl");

    while (!glfwWindowShouldClose(m_window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clear
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Process input
        processInput(m_window);

        // Draw DevUI (ImGUI) stuff
        devUI.render();

        // Render scene

        // Swap Buffers and poll events
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}