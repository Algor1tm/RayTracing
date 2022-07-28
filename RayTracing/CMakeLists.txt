cmake_minimum_required (VERSION 3.16)


# Add source to this project's executable.
add_executable (RayTracing 
"src/Core/Application.cpp" 
"src/Core/Application.h" 
"src/Core/Main.cpp" 
"src/Core/Layer.h" 
"src/Core/Time.h" 
"src/Core/Window.h" 
"src/Core/Window.cpp" 
"src/Core/Debug.h"
"src/ImGui/ImGuiBuild.cpp" 
"src/ImGui/ImGuiLayer.h" 
"src/ImGui/ImGuiLayer.cpp" 
"src/RayTracingApplication.cpp"  
"src/Image.h" 
"src/Image.cpp" 
"src/Renderer.h" 
"src/Renderer.cpp" 
"src/Scene.h"  
"src/Random.h" 
"src/Random.cpp"  
"src/ProjectionCamera.h"
"src/ProjectionCamera.cpp" 
"src/Materials/Material.h" 
"src/Materials/Material.cpp"
"src/Utils.h" 
"src/ThreadPool.h"
"src/Scene.cpp" 
"src/Objects/Sphere.h"
"src/Objects/Sphere.cpp"
"src/Objects/GameObject.h"
"src/Objects/GameObject.cpp" 
"src/Objects/Ray.h"
"src/Objects/AABB.h" 
"src/Objects/AABB.cpp" 
"src/Objects/BVH.h"
"src/Objects/BVH.cpp"
"src/Materials/Texture.h" 
"src/Materials/Texture.cpp" 
"src/Materials/PerlinNoise.h" 
"src/Materials/PerlinNoise.cpp"
"vendor/stb_image/stb_image.h"
"vendor/stb_image/stb_image.cpp" 
"src/Objects/Rect.h"
"src/Objects/Rect.cpp" "src/Objects/Box.h" "src/Objects/Box.cpp" "src/Objects/Instances.h" "src/Objects/Instances.cpp" "src/Objects/ConstantMedium.h" "src/Objects/ConstantMedium.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracing PROPERTY CXX_STANDARD 20)
endif()


target_include_directories(RayTracing PUBLIC "src" "vendor")

#GLFW
add_subdirectory("vendor/GLFW")
target_include_directories("RayTracing" PUBLIC "vendor/GLFW/include")
target_link_libraries("RayTracing" glfw)

#glad
add_subdirectory("vendor/glad")
target_include_directories("RayTracing" PUBLIC "vendor/glad/include")
target_link_libraries("RayTracing" glad)

#glm
add_subdirectory("vendor/glm")
target_include_directories("RayTracing" PUBLIC "vendor/glm")
target_link_libraries("RayTracing" glm)

#ImGui
add_subdirectory("vendor/ImGui")
target_include_directories("RayTracing" PUBLIC "vendor/ImGui")
target_link_libraries("RayTracing" ImGui)
