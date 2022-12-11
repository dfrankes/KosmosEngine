#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <format>
#include <string>
#include <cmath>
#include <vector>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Kosmos.hpp"
class DevUI
{
public:
    bool debugOverlay = true;
    bool sceneExplorer = false;
    std::vector<float> frames;

    DevUI()
    {
    }

    void DrawUI()
    {

        if (ImGui::BeginMainMenuBar())
        {
            ImGui::Text(std::format("[Kosmos Engine]").c_str());
            ImGui::Separator();

            // Enable overlay
            if (ImGui::MenuItem("Overlay"))
                debugOverlay = !debugOverlay;

            // Debuggers
            if (ImGui::BeginMenu("Debuggers"))
            {
                if (ImGui::MenuItem("Scene Browser"))
                {
                    sceneExplorer = !sceneExplorer;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Scene Explorer window
        if (sceneExplorer)
        {
            ImGui::SetNextWindowSize(ImVec2(300.0f, 300.0f));
            // ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));

            ImGui::Begin("Kosmos Engine", 0, ImGuiWindowFlags_NoResize);
            ImGui::Text("Scene Objects");
            ImGui::Button("Reload objects!");
            ImGui::End();
        }

        if (debugOverlay)
        {
            ImGui::SetNextWindowSize(ImVec2(300.0f, 100.0f));
            ImGui::Begin("Debug Overlay", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

            glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
            float test[] = {0.0f, 0.0f, 0.0f};

            ImGui::PlotLines("FPS History", &frames[0], frames.size(), 0, NULL, 0.0f, 144.0f);
            ImGui::InputFloat3("Camera XYZ", test);

            const char *items[] = {"_DEFAULT_", "_PLANET_RENDERER_"};
            static const char *current_item = "_DEFAULT_";
            if (ImGui::BeginCombo("Active Scene", current_item))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (current_item == items[n]);
                    if (ImGui::Selectable(items[n], is_selected))
                    {
                        current_item = items[n];
                    }

                    if (is_selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            ImGui::End();
        }
    }

    void render()
    {
        if (frames.size() > 200)
        {
            for (size_t i = 1; i < frames.size(); i++)
            {
                frames[i - 1] = frames[i];
            }
            frames[frames.size() - 1] = round(1 / Kosmos::engine->deltaTime);
        }
        else
        {
            frames.push_back(round(1 / Kosmos::engine->deltaTime));
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        DrawUI();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
};