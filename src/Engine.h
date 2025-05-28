#pragma once

#include <string>
#include <filesystem>
#include <memory>
#include "core/Scene.h"
#include "core/GameObject.h"

struct GLFWwindow;

class Engine {
public:
    Engine();
    ~Engine();

    bool Init(const std::string& title = "Illumina");
    void Run();
    void Shutdown();

    bool CreateProject(const std::string& name, const std::filesystem::path& rootDir);
    bool OpenProject(const std::filesystem::path& projectDir);

private:
    void ProcessInput();
    void Render();
    void RenderEditorUI();

    enum class Mode { EDIT, PLAY };
    Mode m_Mode = Mode::EDIT;

    std::shared_ptr<Scene> m_CurrentScene;
    std::filesystem::path m_ProjectPath;
    GLFWwindow* m_Window = nullptr;
    std::shared_ptr<GameObject> m_SelectedObject;
};
