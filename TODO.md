Stage Six:

VkSurfaceKHR* My_Ptr_Vk_Surface = malloc(sizeof(VkSurfaceKHR));
tp_glfw_create_win_surface_wrapper(My_Empty_Vk_Instance, glfw_window, NULL, My_Ptr_Vk_Surface);

VkSurfaceCapabilitiesKHR* My_Ptr_Vk_Surface_Capabilities = malloc(sizeof(VkSurfaceCapabilitiesKHR));
vkGetPhysicalDeviceSurfaceCapabilitiesKHR(my_phys_devs[0], *My_Ptr_Vk_Surface, My_Ptr_Vk_Surface_Capabilities);
print_surface_caps(My_Ptr_Vk_Surface_Capabilities);

uint32_t my_formats_counter = 0;
get_num_phys_dev_sur_formats(my_phys_devs[0], *My_Ptr_Vk_Surface, &my_formats_counter);
VkSurfaceFormatKHR* formats_array = malloc(my_formats_counter * sizeof(VkSurfaceFormatKHR));
init_phys_dev_sur_formats(my_phys_devs[0], *My_Ptr_Vk_Surface, &my_formats_counter, formats_array);
print_phys_dev_sur_formats(formats_array, &my_formats_counter);  


uint32_t my_presentation_modes_counter = 0;
get_num_phys_dev_sur_pres_modes(&my_phys_devs[0], My_Ptr_Vk_Surface, &my_presentation_modes_counter, NULL);
VkPresentModeKHR* present_modes_array = malloc(my_presentation_modes_counter * sizeof(VkPresentModeKHR));
init_phys_dev_sur_pres_modes(&my_phys_devs[0], My_Ptr_Vk_Surface, &my_presentation_modes_counter, present_modes_array);
print_presentation_modes(present_modes_array, &my_presentation_modes_counter);

VkSwapchainCreateInfoKHR* My_Ptr_Vk_Swapchain_Create_Info = malloc(sizeof(VkSwapchainCreateInfoKHR));
init_swapchain_create_info(My_Ptr_Vk_Swapchain_Create_Info, My_Ptr_Vk_Surface, WIDTH, HEIGHT);
print_swapchain_create_info(My_Ptr_Vk_Swapchain_Create_Info);

VkBool32 surface_support = 0; /* 1 = true, 0 = false */
uint32_t q_fam_idx_of_choice = 0;
check_surface_support(&my_phys_devs[0], &q_fam_idx_of_choice, My_Ptr_Vk_Surface, &surface_support);
act_on_surface_support_result(&surface_support, My_Ptr_Vk_Device, my_phys_devs, My_Ptr_Vk_DeviceCreateInfo);


/* WOHOOO NOW we can create the Swapchain itself!!! :)*/
/** Besides the device layer VK_KHR_validation we activated 
*   later on for the Swapchain we also need extensions activated
*   at the device level. These are VK_KHR_SWAPCHAIN_EXTENSION_NAME
*   that is a makro that will always resolve to the string "VK_KHR_swapchain".
*   As always we will put it in a string array and pass it to the device struct 
**/

===============================================================================================================================

Stage Seven:

VkSwapchainKHR* My_Ptr_Vk_Swapchain = malloc(sizeof(VkSwapchainKHR));
init_swapchain(My_Ptr_Vk_Device, My_Ptr_Vk_Swapchain_Create_Info, NULL, My_Ptr_Vk_Swapchain);

uint32_t swapchain_img_counter = 0;
get_num_swapchain_imgs(*My_Ptr_Vk_Device, *My_Ptr_Vk_Swapchain, &swapchain_img_counter, NULL);
VkImage* array_swapchain_imgs = malloc(swapchain_img_counter * sizeof(VkImage));
init_swapchain_images(*My_Ptr_Vk_Device, *My_Ptr_Vk_Swapchain, &swapchain_img_counter, array_swapchain_imgs);

VkImageViewCreateInfo* My_Ptr_Vk_Img_View_Create_Inf = malloc(sizeof(VkImageViewCreateInfo));
init_img_view_create_info(My_Ptr_Vk_Img_View_Create_Inf, array_swapchain_imgs);


VkImageView* array_img_views = malloc(swapchain_img_counter * sizeof(VkImageView));
 
for(uint32_t i = 0; i < swapchain_img_counter; i++) {
 rintf("Creating image view #%u\n", i);
VkResult res = vkCreateImageView(*My_Ptr_Vk_Device, My_Ptr_Vk_Img_View_Create_Inf, NULL, &array_img_views[i]);

 f(res != VK_SUCCESS) {
printf("Initialization of image view #%u failed\n", i);
exit(12);
}
}

/** OK, now that that is done, our biggest milestone yet awaits us:
*   Create a graphics pipeline with a vertex shader and a fragment shader!
*
*  Shader are being written in their own programming language: GLSL
*  We will start with the vertex shader 
**/

===============================================================================================================================

Stage Eight:


/** OK, now that that is done, our biggest milestone yet awaits us:
*   Create a graphics pipeline with a vertex shader and a fragment shader!
*
*  Shader are being written in their own programming language: GLSL
*  We will start with the vertex shader 
**/

/** Create Create Info for shader modules
* Inside of init_shader_module_create_info() the filesize is determined
* and the file is read into a buffer. Both informations are passed to 
* the VkShaderModuleCreateInfo struct. **/
VkShaderModuleCreateInfo* My_Ptr_Vert_Shader_Create_Info = malloc(sizeof(VkShaderModuleCreateInfo));
VkShaderModuleCreateInfo* My_Ptr_Frag_Shader_Create_Info = malloc(sizeof(VkShaderModuleCreateInfo));
init_shader_module_create_info(My_Ptr_Vert_Shader_Create_Info, "vert.spv");
init_shader_module_create_info(My_Ptr_Frag_Shader_Create_Info, "frag.spv");

/* With the create info let's create the shader module */
VkShaderModule* My_Ptr_Vert_Shader_Mod = malloc(sizeof(VkShaderModule));
VkShaderModule* My_Ptr_Frag_Shader_Mod = malloc(sizeof(VkShaderModule));
init_shader_module(My_Ptr_Vk_Device, My_Ptr_Vert_Shader_Create_Info, NULL, My_Ptr_Vert_Shader_Mod);
init_shader_module(My_Ptr_Vk_Device, My_Ptr_Frag_Shader_Create_Info, NULL, My_Ptr_Frag_Shader_Mod);


===============================================================================================================================

Stage Nine:

/** So we want to create a pipeline. But we cannot directly
*   pass the shader modules into a pipeline. They have to be passed
*   wrapped in another wrapper called VkPipelineShaderStageCreateInfo
*   That is because its pName member takes the entry function you specified
*   in the GLSL file. Besides main() which is the standrd this could
*   be many more functions so a shader module can actually have more
*   than one VkPipelineShaderStageCreateInfo. 
**/

VkPipelineShaderStageCreateInfo* My_Ptr_Vk_Shader_Stage_Create_Info_Vert = malloc(sizeof(VkPipelineShaderStageCreateInfo));
VkPipelineShaderStageCreateInfo* My_Ptr_Vk_Shader_Stage_Create_Info_Frag = malloc(sizeof(VkPipelineShaderStageCreateInfo));
init_pip_shader_stage_create_inf(My_Ptr_Vk_Shader_Stage_Create_Info_Vert, My_Ptr_Vert_Shader_Mod, "main", "vert");
init_pip_shader_stage_create_inf(My_Ptr_Vk_Shader_Stage_Create_Info_Frag, My_Ptr_Vert_Shader_Mod, "main", "frag");

/*Let's make an array of the created VkPipelineShaderStageCreateInfos*/
VkPipelineShaderStageCreateInfo* init_pip_shader_stage_create_info_array = init_pip_shader_stage_create_inf_array(2, My_Ptr_Vk_Shader_Stage_Create_Info_Vert, My_Ptr_Vk_Shader_Stage_Create_Info_Frag);

===============================================================================================================================

Stage Ten:

/** So shaders for the pipeline are prepared. However a pipleline is additionally made of
*   fixed functions. **/
 
/* First fixed function is the vertex input */
VkPipelineVertexInputStateCreateInfo* My_Ptr_Vx_Inp_State_Create_Info = malloc(sizeof(VkPipelineVertexInputStateCreateInfo));
init_pip_shader_vx_inp_state_create_info(My_Ptr_Vx_Inp_State_Create_Info);
/* Second fixed function is the input assembly */
VkPipelineInputAssemblyStateCreateInfo* My_Ptr_Inp_Assem_State_Create_Info = malloc(sizeof(VkPipelineInputAssemblyStateCreateInfo));
init_pip_inp_assem_state_create_info(My_Ptr_Inp_Assem_State_Create_Info);
/* Third fixed function is the view port (part of the screen where you want to draw) */
VkViewport* My_Ptr_Vk_Vu_Port = malloc(sizeof(VkViewport));
init_vu_port(My_Ptr_Vk_Vu_Port, 0.0f, 0.0f, WIDTH, HEIGHT, 0.0f, 1.0f);
/* Fourth fixed function is the scissor */
/* A scissor defines what part STAYS on the screen and not the part that is cut off!*/
VkRect2D* My_Ptr_Scissor = malloc(sizeof(VkRect2D));
init_rect_2d(My_Ptr_Scissor, 0, 0, WIDTH, HEIGHT);
/* View port and scissor need to be combined into a VkPipelineViewPortStateCreateInfo */
VkPipelineViewportStateCreateInfo* My_Ptr_Pip_Vu_Port_State_Create_Info = malloc(sizeof(VkPipelineViewportStateCreateInfo));
init_pip_vu_port_state_create_info(My_Ptr_Pip_Vu_Port_State_Create_Info, My_Ptr_Vk_Vu_Port, My_Ptr_Scissor);
/* Let's create a rasterizer*/
VkPipelineRasterizationStateCreateInfo* My_Ptr_Rasterizer_Create_Info = malloc(sizeof(VkPipelineRasterizationStateCreateInfo));
init_pip_rast_state_create_info(My_Ptr_Rasterizer_Create_Info, 0, 0, VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_CLOCKWISE, 0, 0.0f, 0.0f, 0.0f, 1.0f);
/* Now we take care of multisampling (antialiasing) */
/* Which we will not use :D */
VkPipelineMultisampleStateCreateInfo* My_Ptr_Pip_Multisam_Create_Info = malloc(sizeof(VkPipelineMultisampleStateCreateInfo));
My_Ptr_Pip_Multisam_Create_Info->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
My_Ptr_Pip_Multisam_Create_Info->pNext = NULL;
My_Ptr_Pip_Multisam_Create_Info->flags = 0;
My_Ptr_Pip_Multisam_Create_Info->rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
My_Ptr_Pip_Multisam_Create_Info->sampleShadingEnable = VK_FALSE;
My_Ptr_Pip_Multisam_Create_Info->minSampleShading = 1.0f;
My_Ptr_Pip_Multisam_Create_Info->pSampleMask = NULL;
My_Ptr_Pip_Multisam_Create_Info->alphaToCoverageEnable = VK_FALSE;
My_Ptr_Pip_Multisam_Create_Info->alphaToOneEnable = VK_FALSE;
