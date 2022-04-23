add_executable(${NAME} main.cpp)

FIND_PACKAGE(PkgConfig REQUIRED)
FIND_PACKAGE(OpenCL REQUIRED)
PKG_CHECK_MODULES(OPENCL REQUIRED OpenCL)

link_directories(${NAME} PUBLIC modules)
target_include_directories(${NAME} PUBLIC ${OPENCL_INCLUDE_DIRS})

#FIND_PACKAGE(Threads REQUIRED)
#if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Werror=return-type")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
#endif()
#target_link_libraries(${NAME} PUBLIC ${OPENCL_LIBRARIES} Threads::Threads)

add_subdirectory(lodepng)
add_subdirectory(modules)

target_link_libraries(${NAME} PUBLIC pthread)
target_link_libraries(${NAME} PUBLIC lodepng)
target_link_libraries(${NAME} PUBLIC modules)
target_link_libraries(${NAME} PUBLIC OpenCL::OpenCL)
