
// src/Engine.h
#pragma once

class Engine {
public:
    Engine();
    ~Engine();
    bool Init();
    void Run();
    void Shutdown();

private:
    void ProcessInput();
    void Update(float dt);
    void Render();

    bool m_Running = false;
};