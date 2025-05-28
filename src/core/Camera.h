
// === src/core/Camera.h ===
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
    Camera();
    void ProcessKeyboard(GLFWwindow* window);
    void ProcessMouseDrag(GLFWwindow* window);
    void Apply();
private:
    glm::vec3 m_Position{0.0f, 0.0f, 5.0f};
    glm::vec3 m_Front{0.0f, 0.0f, -1.0f};
    glm::vec3 m_Up{0.0f, 1.0f, 0.0f};
    float m_Yaw = -90.0f;
    float m_Pitch = 0.0f;
    float m_Speed = 5.0f;
    float m_Sensitivity = 0.1f;
    bool m_FirstMouse = true;
    double m_LastX = 0.0, m_LastY = 0.0;
};
