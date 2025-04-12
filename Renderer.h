#ifndef RENDERER_H
#define RENDERER_H

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include <shaderc/shaderc.hpp>
#include <string>

class Renderer {
public:
    Renderer();
    ~Renderer();

    // Now take an extra parameter for renderPass.
    void createGraphicsPipeline(VkDevice device, VkRenderPass renderPass);
    void createCommandPool(VkDevice device, uint32_t graphicsFamily);
    void createCommandBuffers(VkDevice device, const std::vector<VkFramebuffer>& framebuffers,
        VkExtent2D extent, VkRenderPass renderPass, VkPipeline graphicsPipeline);
    void createSyncObjects(VkDevice device);
    void drawFrame(VkDevice device, VkQueue graphicsQueue, VkQueue presentQueue,
        VkSwapchainKHR swapChain, const std::vector<VkCommandBuffer>& commandBuffers);
    void cleanup(VkDevice device);

    const std::vector<VkCommandBuffer>& getCommandBuffers() const { return m_commandBuffers; }
    VkPipeline getGraphicsPipeline() const { return m_graphicsPipeline; }

private:
    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_graphicsPipeline;
    VkCommandPool m_commandPool;
    std::vector<VkCommandBuffer> m_commandBuffers;
    VkSemaphore m_imageAvailableSemaphore;
    VkSemaphore m_renderFinishedSemaphore;
    VkFence m_inFlightFence;

    // New member for descriptor set layout
    VkDescriptorSetLayout m_descriptorSetLayout;

    std::string readShaderSource(const std::string& filename);
    std::vector<uint32_t> compileShader(const std::string& source, shaderc_shader_kind kind, const std::string& filename);
    VkShaderModule createShaderModuleFromSource(VkDevice device, const std::vector<uint32_t>& spirvCode);

    VkBuffer m_uniformBuffer;
    VkDeviceMemory m_uniformBufferMemory;
    VkDescriptorPool m_descriptorPool;
    VkDescriptorSet m_descriptorSet;
};

#endif
