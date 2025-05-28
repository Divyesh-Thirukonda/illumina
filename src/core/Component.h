
// === src/core/Component.h ===
#pragma once

class GameObject;

class Component {
public:
    virtual ~Component() = default;
    virtual void Update(float dt) {}
    virtual void Render() {}
protected:
    GameObject* m_Host = nullptr;
};