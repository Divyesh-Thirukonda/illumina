
// === src/core/Camera.cpp ===
#include "core/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() = default;

void Camera::ProcessKeyboard(GLFWwindow* window) {
    float delta = m_Speed * 0.016f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_Position += m_Front * delta;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_Position -= m_Front * delta;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * delta;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * delta;
}

void Camera::ProcessMouseDrag(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (m_FirstMouse) {
        m_LastX = xpos;
        m_LastY = ypos;
        m_FirstMouse = false;
    }
    float xoffset = (float)(xpos - m_LastX) * m_Sensitivity;
    float yoffset = (float)(m_LastY - ypos) * m_Sensitivity;
    m_LastX = xpos;
    m_LastY = ypos;

    m_Yaw   += xoffset;
    m_Pitch += yoffset;
    if (m_Pitch > 89.0f) m_Pitch = 89.0f;
    if (m_Pitch < -89.0f) m_Pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
}

void Camera::Apply() {
    glm::mat4 view = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    // load view matrix into shader or fixed-function (not shown)
}
