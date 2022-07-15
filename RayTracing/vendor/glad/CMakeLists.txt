cmake_minimum_required(VERSION 3.2)

project(glad C)

include_directories("include/")

add_library(glad STATIC 
	"include/glad/glad.h" 
	"include/KHR/khrplatform.h"
	"src/glad.c")