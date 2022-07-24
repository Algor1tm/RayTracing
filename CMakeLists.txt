cmake_minimum_required (VERSION 3.16)

project("RayTracing")

add_subdirectory("RayTracing")

set(VENDOR "RayTracing/vendor")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "RayTracing")

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
