# CMake Required Version
cmake_minimum_required (VERSION 2.8)

# Project Name
project (SdfBuilder)

# Add customized CMAKE modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Pass source dir to preprocessor
add_definitions(-DSOURCE_DIR=${CMAKE_SOURCE_DIR})

# Include Eigen3, added FindEigen3 in cmake folder
find_package(Eigen3 REQUIRED)

# Include Eigen
include_directories(EIGEN3_INCLUDE_DIR)

# All files for the SDF builder
file(GLOB_RECURSE
	 SDFBUILDER_SRC
	 ./*.cpp
)

# Compile sdfbuilder library
add_library(sdfbuilder ${SDFBUILDER_SRC} )
