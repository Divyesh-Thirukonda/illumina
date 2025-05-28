
// src/Engine.cpp
#include "Engine.h"
#include <GLFW/glfw3.h>
#include <iostream>

Engine::Engine() = default;
Engine::~Engine() = default;

bool Engine::Init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    GLFWwindow* window = glfwCreateWindow(800,600,"illumina",nullptr,nullptr);
    if (!window) {
        std::cerr << "Window creation failed" << std::endl;
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
        float dt = now - last;
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

void Engine::Update(float dt) {
    // TODO: game logic
}

void Engine::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(glfwGetCurrentContext());
}
