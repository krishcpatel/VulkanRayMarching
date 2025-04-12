#include "Window.h"

Window::Window(int width, int height, const char* title)
    : m_width(width), m_height(height), m_title(title), m_window(nullptr) {
}

void Window::init() {
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    if (!m_window)
        throw std::runtime_error("Failed to create GLFW window");
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

GLFWwindow* Window::getNativeWindow() const {
    return m_window;
}

Window::~Window() {
    if (m_window)
        glfwDestroyWindow(m_window);
    glfwTerminate();
}
