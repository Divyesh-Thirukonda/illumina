#include "Engine.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

Engine::Engine() = default;
Engine::~Engine() = default;

bool Engine::Init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }
    GLFWwindow* window = glfwCreateWindow(800, 600, "Illumina", nullptr, nullptr);
    if (!window) {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    m_Running = true;
    return true;
}

void Engine::Run() {
    float last = static_cast<float>(glfwGetTime());
    while (m_Running) {
        float now = static_cast<float>(glfwGetTime());
        float dt  = now - last;
        last = now;

        ProcessInput();
        Update(dt);
        Render();
    }
}

void Engine::Shutdown() {
    glfwTerminate();
}

void Engine::ProcessInput() {
    glfwPollEvents();
    if (glfwWindowShouldClose(glfwGetCurrentContext()))
        m_Running = false;
}

void Engine::Update(float /*dt*/) {
    // TODO: game or editor logic
}

void Engine::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(glfwGetCurrentContext());
}

bool Engine::CreateProject(const std::string& name,
                           const std::filesystem::path& rootDir)
{
    try {
        // build the project root
        m_ProjectPath = rootDir / name;
        // typical Unity layout
        std::filesystem::create_directories(m_ProjectPath / "Assets");
        std::filesystem::create_directories(m_ProjectPath / "Scenes");
        std::filesystem::create_directories(m_ProjectPath / "Scripts");

        // write a stub scene file
        std::ofstream sceneFile(m_ProjectPath / "Scenes" / "Main.scene");
        sceneFile << "# Illumina Main Scene\n";
        sceneFile << "Camera { position = (0,0,10) }\n";
        sceneFile << "GameObject { name = \"Cube\", transform = (0,0,0) }\n";
        sceneFile.close();

        std::cout << "Successfully created project at: "
                  << m_ProjectPath << "\n";
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating project: " << e.what() << "\n";
        return false;
    }
}
