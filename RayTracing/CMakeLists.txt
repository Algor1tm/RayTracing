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
"src/Environment.h"
"src/Environment.cpp"
"src/Scene.h"  
"src/Random.h" 
"src/Random.cpp"  
"src/ProjectionCamera.h"
"src/ProjectionCamera.cpp" 
"src/Material.h" 
"src/Material.cpp"
"src/Utils.h" 
"src/ThreadPool.h"
"src/Scene.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracing PROPERTY CXX_STANDARD 20)
endif()
