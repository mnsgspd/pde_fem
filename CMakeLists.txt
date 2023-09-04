### cmake ../ -DVTK_DIR=~/third_party/VTK-9.2.6/build -DCOMPILER_TYPE=GNU -DNLOHMANN_JSON_INCLUDE_DIR=~/third_party/json-develop/include/ -DEIGEN3_INCLUDE_DIR=~/third_party/eigen-3.4.0/
### -DCMAKE_BUILD_TYPE=Debug
### -DCOMPILER_TYPE=Intel -DCOMPILER_TYPE=GNU

cmake_minimum_required(VERSION 3.10)
project(fem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add compiler flags if needed
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option for selecting the compiler type
set(COMPILER_TYPE "GNU" CACHE STRING "Select the compiler type: GNU or Intel")
set_property(CACHE COMPILER_TYPE PROPERTY STRINGS "GNU" "Intel")

# Set flags based on the selected compiler
if(COMPILER_TYPE STREQUAL "GNU")
  # Flags for g++
  set(CMAKE_CXX_COMPILER "g++")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address -fsanitize=undefined -Wall -Wextra -Wpedantic")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -fopenmp") 
elseif(COMPILER_TYPE STREQUAL "Intel")
  # Flags for Intel
  set(CMAKE_CXX_COMPILER "icpx")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -xHost -qopt-report=5 -parallel")
else()
  message(FATAL_ERROR "Invalid compiler type!")
endif()

# Find VTK packages. If installed via apt or other package managers, CMake should find them automatically.
find_package(VTK REQUIRED)

# Try to find Eigen3 using find_package
find_package(Eigen3 QUIET)

if (NOT Eigen3_FOUND)
  # If Eigen3 was not found, specify a path manually
  set(EIGEN3_INCLUDE_DIR "" CACHE PATH "Path to Eigen3 header files")
  include_directories(${EIGEN3_INCLUDE_DIR})
else()
  include_directories(${EIGEN3_INCLUDE_DIR})
endif()

# Specify the location of the nlohmann/json header file. 
# We'll set a default assumption it's in the project's 'external' directory, but this can be overridden by a command line option.
set(NLOHMANN_JSON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external" CACHE PATH "Path to nlohmann/json header file")

# Check for the existence of nlohmann/json.hpp in the specified directory
if(NOT EXISTS ${NLOHMANN_JSON_INCLUDE_DIR}/nlohmann/json.hpp)
  message(FATAL_ERROR "nlohmann/json.hpp not found in specified path: ${NLOHMANN_JSON_INCLUDE_DIR}")
endif()

# Include directories
include_directories(
  ${EIGEN3_INCLUDE_DIR}
  ${NLOHMANN_JSON_INCLUDE_DIR}
  )

# Specify source files
set(SOURCES 
  src/main.cpp
  src/fem_simulation.cpp
  src/generator.cpp
  src/output_writer.cpp
  src/assemblers/helmholtz_assembler.cpp
  src/assemblers/poisson_assembler.cpp
  src/solvers/conjugate_gradient.cpp
  )

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against the VTK library
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
add_definitions(${VTK_DEFINITIONS})

# Include project-specific directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
