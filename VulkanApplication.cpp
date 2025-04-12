#include "VulkanApplication.h"
#include <stdexcept>
#include <iostream>

VulkanApplication::VulkanApplication(int width, int height, const char* title)
    : m_cleaned(false)
{
    m_window = new Window(width, height, title);
    m_deviceManager = new DeviceManager();
    m_swapChain = new SwapChain();
    m_renderer = new Renderer();
}

VulkanApplication::~VulkanApplication() {
    cleanup();
    delete m_renderer;
    delete m_swapChain;
    delete m_deviceManager;
    delete m_window;
}

void VulkanApplication::init() {
    m_window->init();

    // Gather required extensions from GLFW.
    std::vector<const char*> extensions;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    for (uint32_t i = 0; i < glfwExtensionCount; i++) {
        extensions.push_back(glfwExtensions[i]);
    }

    m_deviceManager->createInstance(extensions);
    m_deviceManager->createSurface(m_window->getNativeWindow());
    m_deviceManager->pickPhysicalDevice();
    m_deviceManager->createLogicalDevice();

    // Initialize swap chain with window dimensions.
    m_swapChain->init(m_deviceManager->getDevice(), m_deviceManager->getPhysicalDevice(),
        m_deviceManager->getSurface(), 1920, 1080);

    // Create the graphics pipeline using the valid render pass from the swap chain.
    m_renderer->createGraphicsPipeline(m_deviceManager->getDevice(), m_swapChain->getRenderPass());

    // For the command pool, we assume the graphics queue family index is 0 (adjust if needed).
    m_renderer->createCommandPool(m_deviceManager->getDevice(), 0);

    // Now use the framebuffers from the swap chain to record command buffers.
    m_renderer->createCommandBuffers(m_deviceManager->getDevice(), m_swapChain->getFramebuffers(),
        m_swapChain->getExtent(), m_swapChain->getRenderPass(),
        m_renderer->getGraphicsPipeline());

    m_renderer->createSyncObjects(m_deviceManager->getDevice());
}

void VulkanApplication::mainLoop() {
    while (!m_window->shouldClose()) {
        m_window->pollEvents();
        m_renderer->drawFrame(m_deviceManager->getDevice(), m_deviceManager->getGraphicsQueue(),
            m_deviceManager->getPresentQueue(), m_swapChain->getSwapChain(),
            m_renderer->getCommandBuffers());
    }
    vkDeviceWaitIdle(m_deviceManager->getDevice());
}

// Make sure cleanup is performed only once.
void VulkanApplication::cleanup() {
    if (m_cleaned)
        return;
    m_renderer->cleanup(m_deviceManager->getDevice());
    m_swapChain->cleanup(m_deviceManager->getDevice());
    m_cleaned = true;
}

// run() calls init(), mainLoop(), then cleanup().
void VulkanApplication::run() {
    init();
    mainLoop();
    cleanup();
}
