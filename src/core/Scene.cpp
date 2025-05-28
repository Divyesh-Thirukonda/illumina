
// === src/core/Scene.cpp ===
#include "core/Scene.h"
#include <algorithm>

Scene::Scene(const std::string& sceneFile) { Load(sceneFile); }
Scene::~Scene() = default;

void Scene::SaveDefault(const std::string& path) {
    // write empty scene file
}

void Scene::Load(const std::string& path) {
    m_RootObjects.clear();
}

void Scene::Update(float dt) {
    for (auto& o : m_RootObjects) o->Update(dt);
}

void Scene::RenderEditorView() {
    m_EditorCamera.Apply();
    for (auto& o : m_RootObjects) o->Render();
}

void Scene::RenderGameView() {
    m_GameCamera.Apply();
    for (auto& o : m_RootObjects) o->Render();
}

void Scene::AddPrimitive(PrimitiveType type) {
    // create sphere/light/camera based on type
}

void Scene::AddCamera() {}
void Scene::AddLight() {}

std::vector<std::shared_ptr<GameObject>>& Scene::GetRootObjects() { return m_RootObjects; }
Camera& Scene::GetEditorCamera() { return m_EditorCamera; }
Camera& Scene::GetGameCamera() { return m_GameCamera; }
void Scene::Save(const std::string& path) {
    // write scene to file
}

