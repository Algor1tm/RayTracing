# CMakeList.txt : CMake project for RayTracing, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

project ("RayTracing")

# Add source to this project's executable.
add_executable (RayTracing 
"RayTracing/src/Core/Application.cpp" 
"RayTracing/src/Core/Application.h" 
"RayTracing/src/Core/Main.cpp" 
"RayTracing/src/Core/Layer.h" 
"RayTracing/src/Core/Time.h" 
"RayTracing/src/Core/Window.h" 
"RayTracing/src/Core/Window.cpp" 
"RayTracing/src/Core/Debug.h"
"RayTracing/src/ImGui/ImGuiBuild.cpp" 
"RayTracing/src/ImGui/ImGuiLayer.h" 
"RayTracing/src/ImGui/ImGuiLayer.cpp" 
"RayTracing/src/RayTracingApplication.cpp"  
"RayTracing/src/Image.h" 
"RayTracing/src/Image.cpp" 
"RayTracing/src/Renderer.h" 
"RayTracing/src/Renderer.cpp" 
"RayTracing/src/Environment.h"
"RayTracing/src/Environment.cpp"
"RayTracing/src/Scene.h"  
"RayTracing/src/Random.h" 
"RayTracing/src/Random.cpp"  
"RayTracing/src/ProjectionCamera.h"
"RayTracing/src/ProjectionCamera.cpp" 
"RayTracing/src/Material.h" 
"RayTracing/src/Material.cpp"
"RayTracing/src/Utils.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracing PROPERTY CXX_STANDARD 20)
endif()


set(VENDOR "RayTracing/vendor")

target_include_directories(${PROJECT_NAME} PUBLIC "RayTracing/src" "${VENDOR}")

#GLFW
add_subdirectory("${VENDOR}/GLFW")
target_include_directories(${PROJECT_NAME} PUBLIC "${VENDOR}/GLFW/include")
target_link_libraries(${PROJECT_NAME} glfw)

#glad
add_subdirectory("${VENDOR}/glad")
target_include_directories(${PROJECT_NAME} PUBLIC "${VENDOR}/glad/include")
target_link_libraries(${PROJECT_NAME} glad)

#glm
add_subdirectory("${VENDOR}/glm")
target_include_directories(${PROJECT_NAME} PUBLIC "${VENDOR}/glm")
target_link_libraries(${PROJECT_NAME} glm)

#ImGui
add_subdirectory("${VENDOR}/ImGui")
target_include_directories(${PROJECT_NAME} PUBLIC "${VENDOR}/ImGui")
target_link_libraries(${PROJECT_NAME} ImGui)
