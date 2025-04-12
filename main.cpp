#include "VulkanApplication.h"
#include <iostream>
#include <cstdlib>

int main() {
    try {
        VulkanApplication app(1920, 1080, "Vulkan - Ray Marching");
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
