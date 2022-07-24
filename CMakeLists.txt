cmake_minimum_required (VERSION 3.16)

project("RayTracing")

add_subdirectory("RayTracing")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "RayTracing")

