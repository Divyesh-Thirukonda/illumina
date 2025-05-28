
// === src/core/GameObject.h ===
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Transform.h"

class Component;

class GameObject {
public:
    explicit GameObject(const std::string& name);
    ~GameObject();

    const std::string& GetName() const;
    Transform& GetTransform();

    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args) {
        auto comp = std::make_shared<T>(std::forward<Args>(args)...);
        comp->m_Host = this;
        m_Components.push_back(comp);
        return comp;
    }

    void Update(float dt);
    void Render();
    void DrawInspector();

private:
    std::string m_Name;
    Transform m_Transform;
    std::vector<std::shared_ptr<Component>> m_Components;
};

