#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include <algorithm>

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class SwapChain {
public:
    SwapChain();
    ~SwapChain();

    void init(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, int width, int height);
    VkFormat getImageFormat() const { return m_imageFormat; }
    VkExtent2D getExtent() const { return m_extent; }
    VkSwapchainKHR getSwapChain() const { return m_swapChain; }
    const std::vector<VkImageView>& getImageViews() const { return m_imageViews; }
    const std::vector<VkFramebuffer>& getFramebuffers() const { return m_framebuffers; }
    VkRenderPass getRenderPass() const { return m_renderPass; }

    void cleanup(VkDevice device);

private:
    VkSwapchainKHR m_swapChain;
    std::vector<VkImage> m_images;
    VkFormat m_imageFormat;
    VkExtent2D m_extent;
    std::vector<VkImageView> m_imageViews;
    VkRenderPass m_renderPass;
    std::vector<VkFramebuffer> m_framebuffers;

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& modes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, int width, int height);
    void createSwapChain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, int width, int height);
    void createImageViews(VkDevice device);
    void createRenderPass(VkDevice device);
    void createFramebuffers(VkDevice device);
};

#endif
