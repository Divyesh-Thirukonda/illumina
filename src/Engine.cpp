#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "ImGuiFileDialog.h"
#include <iostream>

Engine::Engine() {}
Engine::~Engine() { Shutdown(); }

bool Engine::CreateProject(const std::string& name, const std::filesystem::path& rootDir) {
    auto proj = rootDir / name;
    if (std::filesystem::exists(proj)) return false;
    std::filesystem::create_directories(proj / "Scenes");
    std::filesystem::create_directories(proj / "Assets");
    Scene::SaveDefault((proj / "Scenes" / "Main.scene").string());
    return true;
}

bool Engine::OpenProject(const std::filesystem::path& projectDir) {
    if (!std::filesystem::exists(projectDir)) return false;
    m_ProjectPath = projectDir;
    m_CurrentScene = std::make_shared<Scene>((projectDir / "Scenes" / "Main.scene").string());
    return true;
}

bool Engine::Init(const std::string& title) {
    if (!glfwInit()) return false;
    m_Window = glfwCreateWindow(1280, 720, title.c_str(), nullptr, nullptr);
    if (!m_Window) { glfwTerminate(); return false; }
    glfwMakeContextCurrent(m_Window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Docking removed for compatibility
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    return true;
}

void Engine::Run() {
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(m_Window)) {
        double now = glfwGetTime();
        float dt = static_cast<float>(now - lastTime);
        lastTime = now;

        ProcessInput();
        if (m_Mode == Mode::PLAY && m_CurrentScene)
            m_CurrentScene->Update(dt);
        Render();
    }
}

void Engine::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (m_Window) glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Engine::ProcessInput() {
    glfwPollEvents();
    if (m_CurrentScene) {
        if (m_Mode == Mode::EDIT) {
            auto& cam = m_CurrentScene->GetEditorCamera();
            cam.ProcessMouseDrag(m_Window);
            cam.ProcessKeyboard(m_Window);
        } else {
            m_CurrentScene->GetGameCamera().ProcessKeyboard(m_Window);
        }
    }
}

void Engine::Render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_CurrentScene) {
        if (m_Mode == Mode::EDIT) m_CurrentScene->RenderEditorView();
        else m_CurrentScene->RenderGameView();
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    RenderEditorUI();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_Window);
}

void Engine::RenderEditorUI() {
    // DockSpaceOverViewport() removed for compatibility

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open Project...")) {
                ImGuiFileDialog::Instance()->OpenDialog(
                    "OpenProjectDlg", "Open Project", ".scene",
                    IGFD::FileDialogConfig{ "." });
            }
            if (ImGui::MenuItem("Save Scene")) {
                if (m_CurrentScene)
                    m_CurrentScene->Save((m_ProjectPath / "Scenes" / "Main.scene").string());
            }
            ImGui::MenuItem(m_Mode == Mode::PLAY ? "Stop" : "Play", nullptr, &m_Mode);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (ImGuiFileDialog::Instance()->Display("OpenProjectDlg")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            auto path = ImGuiFileDialog::Instance()->GetFilePathName();
            OpenProject(path);
        }
        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::Begin("Scene View");
    if (m_CurrentScene) m_CurrentScene->RenderEditorView();
    ImGui::End();

    ImGui::Begin("Game View");
    if (m_CurrentScene) m_CurrentScene->RenderGameView();
    ImGui::End();

    ImGui::Begin("Inspector");
    if (m_CurrentScene) {
        if (ImGui::Button("Add Sphere")) m_CurrentScene->AddPrimitive(PrimitiveType::Sphere);
        ImGui::SameLine(); if (ImGui::Button("Add Camera")) m_CurrentScene->AddCamera();
        ImGui::SameLine(); if (ImGui::Button("Add Light")) m_CurrentScene->AddLight();
        ImGui::Separator(); ImGui::Text("Objects:");
        for (auto& obj : m_CurrentScene->GetRootObjects()) {
            bool sel = obj == m_SelectedObject;
            if (ImGui::Selectable(obj->GetName().c_str(), sel)) m_SelectedObject = obj;
        }
        if (m_SelectedObject) m_SelectedObject->DrawInspector();
    }
    ImGui::End();

    ImGui::Begin("Assets");
    ImGui::Text("No asset browser configured");
    ImGui::End();
}
