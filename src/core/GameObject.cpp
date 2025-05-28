
// === src/core/GameObject.cpp ===
#include "core/GameObject.h"
#include "core/Component.h"
#include <imgui.h>

GameObject::GameObject(const std::string& name):m_Name(name){}
GameObject::~GameObject() = default;

const std::string& GameObject::GetName() const { return m_Name; }
Transform& GameObject::GetTransform() { return m_Transform; }

void GameObject::Update(float dt) { for(auto& c:m_Components) c->Update(dt); }
void GameObject::Render() { for(auto& c:m_Components) c->Render(); }

void GameObject::DrawInspector() {
    ImGui::Text("%s", m_Name.c_str());
    ImGui::DragFloat3("Position", &m_Transform.position.x);
    ImGui::DragFloat3("Rotation", &m_Transform.rotation.x);
    ImGui::DragFloat3("Scale", &m_Transform.scale.x);
}
