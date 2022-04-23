cmake_minimum_required(VERSION 3.12)

SET(NAME image_resizer)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${NAME} LANGUAGES CXX)
project(${NAME} VERSION 1.0.0)

add_subdirectory(sources)

#target_link_libraries(${NAME} PUBLIC pthread)

set_target_properties(${NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/output/x64/debug
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/output/x64/release
)
