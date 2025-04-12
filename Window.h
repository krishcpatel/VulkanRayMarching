#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <stdexcept>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    void init();
    bool shouldClose() const;
    void pollEvents();
    GLFWwindow* getNativeWindow() const;

private:
    int m_width, m_height;
    const char* m_title;
    GLFWwindow* m_window;
};

#endif
