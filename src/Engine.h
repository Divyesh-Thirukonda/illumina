#pragma once

#include <string>
#include <filesystem>

class Engine {
public:
    Engine();
    ~Engine();

    /// Initialize the rendering window & context
    bool Init();

    /// Main loop (when running a built project or editor)
    void Run();

    /// Clean up
    void Shutdown();

    /// Create the on-disk structure for a brand new project.
    /// name: project folder name
    /// rootDir: where to create it (will do rootDir/name)
    bool CreateProject(const std::string& name,
                       const std::filesystem::path& rootDir);

private:
    void ProcessInput();
    void Update(float dt);
    void Render();

    bool m_Running = false;
    std::filesystem::path m_ProjectPath;
};
