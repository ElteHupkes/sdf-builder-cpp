# CMake Required Version
cmake_minimum_required (VERSION 2.8)

# Project Name
project (SdfBuilder)

# Add customized CMAKE modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/")

# Pass source dir to preprocessor
add_definitions(-DSOURCE_DIR=${CMAKE_SOURCE_DIR})

# Include Eigen3, added FindEigen3 in cmake folder
find_package(Eigen3 REQUIRED)

# Include Eigen
include_directories(${CMAKE_SOURCE_DIR} ${EIGEN3_INCLUDE_DIR})

# Set dependency list (currently empty)
set(SDFB_DEPS )

# All files for the SDF builder
file(GLOB_RECURSE
	 SDFBUILDER_SRC
	 sdf_builder/*.cpp
)

# Compiler options
# TODO This currently assumes GCC, add Windows support in due time
add_definitions(-pedantic -Wno-long-long -Wall -Wextra -Wformat=2
                -Wredundant-decls -Wwrite-strings -Wmissing-include-dirs 
                -Wswitch-enum -Wuninitialized 
                -Wswitch-default -Winit-self -Wfloat-equal -fPIC )

# Use C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Debug Flags 
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb3 -DDEBUG")

# Release flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -funroll-loops -finline-functions -fomit-frame-pointer -DNDEBUG")

# Compile sdfbuilder library
add_library(sdfbuilder ${SDFBUILDER_SRC} )
target_link_libraries(sdfbuilder ${SDFB_DEPS})

# Test executable
add_executable(test sdf_builder/test/test.cpp)
target_link_libraries(test sdfbuilder ${SDFB_DEPS})
