#ifndef VULKANAPPLICATION_H
#define VULKANAPPLICATION_H

#include "Window.h"
#include "DeviceManager.h"
#include "SwapChain.h"
#include "Renderer.h"

class VulkanApplication {
public:
    VulkanApplication(int width, int height, const char* title);
    ~VulkanApplication();
    void run();
private:
    void init();
    void mainLoop();
    void cleanup();

    Window* m_window;
    DeviceManager* m_deviceManager;
    SwapChain* m_swapChain;
    Renderer* m_renderer;
    bool m_cleaned;
};

#endif
