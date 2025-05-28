
// === src/core/Scene.h ===
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "core/Camera.h"
#include "GameObject.h"
#include "PrimitiveType.h"

class Scene {
public:
    explicit Scene(const std::string& sceneFile);
    ~Scene();

    static void SaveDefault(const std::string& path);

    void Update(float dt);
    void RenderEditorView();
    void RenderGameView();

    void AddPrimitive(PrimitiveType type);
    void AddCamera();
    void AddLight();

    std::vector<std::shared_ptr<GameObject>>& GetRootObjects();
    Camera& GetEditorCamera();
    Camera& GetGameCamera();
    void Save(const std::string& path);

private:
    void Load(const std::string& path);
    std::vector<std::shared_ptr<GameObject>> m_RootObjects;
    Camera m_EditorCamera;
    Camera m_GameCamera;
};
