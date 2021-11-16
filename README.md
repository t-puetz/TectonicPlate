# TectonicPlate

At the moment this is more like a wrapper library that wrapps Vulkan functions and uses GLFW.

Thanks and Danke to the German YouTuber Brotcrunsher.
Deine Tutorials sind einfach super!

#### Note

Today I found out that some distros install NVIDIA stuff even though you have an AMD-only system. I think it happened on my devices because of Steam. If you have NVIDIA packages installed and you have an AMD only system running the triangle example will cause a mutex lock after it passed /usr/lib/libGLX_nvidia.so.

So uninstall nvidia packages in that case!

UPDATE: Artix Linux dev told me I should have paid attention to my package manager when steam asked me what to install alongside of it. He was right. I will still leave this here because it could still happen to someone else.