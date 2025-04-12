# Vulkan Ray Marching

A learning project focused on using the Vulkan graphics API to implement ray marching techniques.

## Prerequisites

- Visual Studio 2022 or later
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home)
- [GLM (OpenGL Mathematics)](https://github.com/g-truc/glm)
- [GLFW](https://www.glfw.org/)

## Setup Instructions

1. Clone this repository:
   ```bash
   git clone https://github.com/krishcpatel/VulkanRayMarching.git
   ```

2. Open the solution file in **Visual Studio 2022+**.

3. Add the following include directories:
   - `VulkanSDK\Include`
   - `glm`
   - `glfw3\include`

4. Add the following library directories:
   - `VulkanSDK\Lib`
   - `glfw3\lib-vc2022`

5. Link the following libraries:
   - `vulkan-1.lib`
   - `glfw3.lib`
   - `shaderc_combinedd.lib` *(for Debug builds)*
   - `shaderc_combined.lib` *(for Release builds)*

## Notes

- This project is intended for learning and experimentation with Vulkan.
- No CMake build system is used; setup is handled directly through Visual Studio.

