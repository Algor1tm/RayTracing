# CMakeList.txt : CMake project for RayTracing, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

project ("RayTracing")

# Add source to this project's executable.
add_executable (RayTracing "RayTracing/src/RayTracing.cpp" "RayTracing/src/RayTracing.h" "RayTracing/src/ImGuiBuild.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracing PROPERTY CXX_STANDARD 20)
endif()


set(VENDOR "RayTracing/vendor")

target_include_directories(${PROJECT_NAME} PUBLIC "${VENDOR}")

add_subdirectory("${VENDOR}/GLFW")
target_include_directories(${PROJECT_NAME} PUBLIC "${VENDOR}/GLFW/include")
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory("${VENDOR}/glad")
target_include_directories(${PROJECT_NAME} PUBLIC "${VENDOR}/glad/include")
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory("${VENDOR}/glm")
target_include_directories(${PROJECT_NAME} PUBLIC "${VENDOR}/glm")
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory("${VENDOR}/ImGui")
target_include_directories(${PROJECT_NAME} PUBLIC "${VENDOR}/ImGui")
target_link_libraries(${PROJECT_NAME} ImGui)

# TODO: Add tests and install targets if needed.
