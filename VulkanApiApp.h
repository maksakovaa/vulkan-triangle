#ifndef VULKAN_API_APP
#define VULKAN_API_APP

#include "constants.h"

class VulkanApiApp
{
public:
    void run();
private:    //Methods
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    void createInstance();
    void pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
    void createLogicalDevice();
    void createSurface();
    void checkExtensions();
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT,
        VkDebugUtilsMessageTypeFlagsEXT,
        const VkDebugUtilsMessengerCallbackDataEXT*,
        void*);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    VkResult CreateDebugUtilsMessengerEXT(
        VkInstance,
        const VkDebugUtilsMessengerCreateInfoEXT*,
        const VkAllocationCallbacks*,
        VkDebugUtilsMessengerEXT*);
    static void DestroyDebugUtilsMessengerEXT(VkInstance, VkDebugUtilsMessengerEXT,
        const VkAllocationCallbacks*);
    //Swap chain
    bool checkDeviceExtensionsSupport(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createSwapChain();
    void recreateSwapChain();
    void cleanupSwapChain();
    //Image views
    void createImageViews();
    //Graphics pipeline
    void createGraphicsPipeline();
    static std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    //Render passes
    void createRenderPass();
    //Framebuffers
    void createFrameBuffers();
    //Command buffers
    void createCommandPool();
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    //Rendering
    void drawFrame();
    void createSyncObjects();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    //Vertex buffer
    void createVertexBuffer();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags,
        VkBuffer&, VkDeviceMemory&);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    //Index buffer
    void createIndexBuffer();
    //Descriptor set layout
    void createDescriptorSetLayout();
    void createUniformBuffers();
    void updateUniformBuffer(uint32_t currentImage);
    void createDescriptorPool();
    void createDescriptorSets();

    //Texture mapping
    void createTextureImage();
    void createImage(uint32_t, uint32_t, VkFormat, VkImageTiling, VkImageUsageFlags, 
        VkMemoryPropertyFlags, VkImage&, VkDeviceMemory&);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void transitionImageLayout(VkImage, VkFormat, VkImageLayout, VkImageLayout);
    void copyBufferToImage(VkBuffer, VkImage, uint32_t, uint32_t);

    void createTextureImageView();
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

    void createTextureSampler();

    //Depth image and view
    void createDepthResources();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);
private:    //Objects
    GLFWwindow* window;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;
    //Swap chain
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    //ImageViews
    std::vector<VkImageView> swapChainImageViews;

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    //Framebuffers
    std::vector<VkFramebuffer> swapChainFramebuffers;
    //Command buffers
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    //Rendering
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    uint32_t currentFrame = 0;

    bool framebufferResized = false;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    //Index buffer
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    //Texture mapping
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    //Depth image and view
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
};
#endif