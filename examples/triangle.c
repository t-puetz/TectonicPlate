#include "../tectonic_plate.h"

#define DEBUG  1
#define WIDTH  1368
#define HEIGHT 720

int main()
{
    /* ================================================================================================= */
    /**
    *  STAGE ONE: Creates VkApplicationInfo, VkInstanceCreateInfo. From those the VkInstance is created!
    *  Finally the GPUs in your system are detected and are stored in and array
    *  in a struct as well as the number of GPUs found
    **/
    /* ================================================================================================= */
    if(!glfwInit()) {
        printf("Initializing GLFW failed. Needed to get required instance extensions\n");
        exit(-3);
    }

    /* Prepare Stage 1*/
    const char* app_nm   = "TectonicPlate Example Triangle";
    uint32_t app_maj_ver = 0;
    uint32_t app_min_ver = 0;
    uint32_t app_pat_ver = 1;

    /* Init Stage 1 */
    Tp_Init_Vk_Stg_One* tp_strct_stg_one = tp_super_init_vulkan_stg_one(app_nm, app_maj_ver, app_min_ver, app_pat_ver);



    char** detectd_avail_lay_nms = tp_get_avail_lay_nms(tp_strct_stg_one);
    /* Print = test Stage 1 info */
    tp_print_vk_app_inf(tp_strct_stg_one, DEBUG);
    tp_print_inst_creat_inf(tp_strct_stg_one, DEBUG);

    /* ================================================================================================= */
    /**
    *  STAGE TWO: Choose your GPU. From that GPU fill VkPhysicalDeviceProperties,
    *  VkPhysicalDeviceFeatures, and VkPhysicalDeviceMemoryProperties
    *  Combine basic GPU info from stage one with the advanced one in a single struct Tp_Init_Vk_Stg_Two
    **/
    /* ================================================================================================= */

    /* Prepare Stage 2 */
    /* Your basic GPU info and number of GPUs are stored in */
    /* tp_strct_stg_one->p_gpus->gpu_arr and tp_strct_stg_one->p_gpus->num_gpus, respectively */
    uint32_t num_gpus_this_system = *(tp_strct_stg_one->p_gpus->num_gpus);

    /* For now I don't know how to detect the best GPU for some puposes, yet */
    /* I am on a PC with an AMD Radeon RX570. It is my only activated and thus detected GPU */
    VkPhysicalDevice* gpu_array    = tp_strct_stg_one->p_gpus->gpu_arr;
    VkPhysicalDevice gpu_of_choice = gpu_array[0];
    tp_strct_stg_one->p_goi = &gpu_of_choice;

    /* Init Stage 2 */
    Tp_Init_Vk_Stg_Two* complete_gpu_info = tp_super_init_vulkan_stg_two(tp_strct_stg_one, &gpu_of_choice);

    /* Print = test Stage 2 Info*/
    tp_print_super_init_stg_two(complete_gpu_info, "all", DEBUG);

    /* ================================================================================================= */
    /**
    *  STAGE THREE: From chosen GPU VkQueueFamilyProperties will be created.
    *  then VkDeviceQueueCreateInfo and VkDeviceCreateInfo follow
    *  Until our stage milestone, the initialization of the logical representation of our GPU.
    **/
    /* ================================================================================================= */

    Tp_Init_Vk_Stg_Three* p_tp_stg_three_strct = tp_super_init_vulkan_stg_three(complete_gpu_info, NULL, 0, NULL, NULL, 0);
    tp_print_dev_q_creat_inf(p_tp_stg_three_strct->p_vk_dev_q_creat_inf, DEBUG);
    tp_print_q_fam_props(p_tp_stg_three_strct->p_vk_q_fam_props, DEBUG);
    tp_print_create_dev_creat_info(p_tp_stg_three_strct->p_vk_dev_creat_inf, DEBUG);

    /* ================================================================================================= */
    /**
    *  STAGE FOUR: "Just" creates VkDevice, the logical representation of the GPU. Vulkan will only
    *  directly talk with logical devices, not the physical ones. Stage three was basically already a lot
    *  of preliminary work for stage four. That's why this stage seems so "small".
    **/
    /* ================================================================================================= */

    Tp_Init_Vk_Stg_Four* p_stg_four_strct = tp_super_init_vulkan_stg_four(p_tp_stg_three_strct);

    /* ================================================================================================= */
    /**
    *  STAGE FIVE: Contains VkExtensionProperties and VkQueue
    **/
    /* ================================================================================================= */

    Tp_Init_Vk_Stg_Five* p_stg_five_strct = tp_super_init_vulkan_stg_five(p_stg_four_strct, NULL);
    tp_print_super_init_stg_five(p_stg_five_strct->p_vk_ext_props_data->p_vk_ext_props, p_stg_five_strct->p_vk_ext_props_data->num_ext_props);
    char** detectd_avail_ext_nms = tp_get_avail_ext_nms(p_stg_five_strct);

    /* ================================================================================================= */
    /**
    *  STAGE SIX: Creates GLFWwindow VkSurfaceKHR, VkSurfaceCapabilitiesKHR,
    *  VkSurfaceFormatKHR, VkSwapchainCreateInfo
    **/
    /* ================================================================================================= */

    Tp_Init_Vk_Stg_Six* p_stg_six_strct = tp_super_init_vulkan_stg_six(p_stg_five_strct, WIDTH, HEIGHT, tp_strct_stg_one->app_nm);
    tp_print_vk_surf_caps_khr(p_stg_six_strct->p_stg_six_vk_sur_data->p_vk_sur_caps_khr);
    tp_print_vk_sur_forms(p_stg_six_strct);
    tp_print_vk_pres_mods(p_stg_six_strct);

    /* ================================================================================================= */
    /**
    *  STAGE Seven: Creates VkSwapchainKHR, VkImage Array, VkImageViewCreateInfo
    *  and stores boolean that indicates Surface support (Will always be true since
    *  program would have crashed and stage seven would have never finished
    **/
    /* ================================================================================================= */

    Tp_Init_Vk_Stg_Seven* p_stg_seven_strct = tp_super_init_vulkan_stg_seven(p_stg_six_strct);

    while(!glfwWindowShouldClose(p_stg_six_strct->p_stg_six_vk_sur_data->p_glfw_window)) {
        glfwPollEvents();
    }

    /* ================================================================================================= */
    /**
    *  free memory
    **/
    /* ================================================================================================= */

    return 0;
}
