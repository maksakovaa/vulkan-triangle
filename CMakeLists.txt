cmake_minimum_required(VERSION 3.5.0)
project(HelloTriangle VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
find_package(Vulkan REQUIRED)
find_package(glfw3 3.4 REQUIRED)
add_executable(HelloTriangle main.cpp vulkan.cpp)
target_link_libraries(HelloTriangle glfw Vulkan::Vulkan)
