FIND_PACKAGE(PkgConfig REQUIRED)
#PKG_CHECK_MODULES(OPENCL REQUIRED OpenCL)
FIND_PACKAGE(OpenCL REQUIRED)

#FIND_PACKAGE(Threads REQUIRED)
#if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Werror=return-type")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
#endif()

add_library(
  modules
  kernel_helpers.h
  preprocessor.h
  Basic.h
  SImage.h
  WorkGroup.h
  OpenCL.h
  OpenCL.cpp
  OpenCLIPP.h
  Buffer.h
  Buffer.cpp
  Conversions.h
  Conversions.cpp
  Filters.h
  Filters.cpp
  Image.h
  Image.cpp
  Program.h
  Program.cpp
  Transform.h
  Transform.cpp)

target_include_directories(modules PUBLIC
  ${OPENCL_INCLUDE_DIRS}
  "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(modules PUBLIC ${OPENCL_LIBRARIES} pthread)
target_link_libraries(modules PUBLIC OpenCL::OpenCL)
