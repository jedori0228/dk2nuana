cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)

set(CMAKE_CXX_STANDARD 17)

project(dk2nuana VERSION 01.00.00 LANGUAGES CXX)

#Changes default install path to be a subdirectory of the build dir.
#Can set build dir at configure time with -DCMAKE_INSTALL_PREFIX=/install/path
if(CMAKE_INSTALL_PREFIX STREQUAL "" OR CMAKE_INSTALL_PREFIX STREQUAL
  "/usr/local")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}")
elseif(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE DebWithRelInfo)
endif()

find_package(ROOT 6.28.00 REQUIRED)
find_package(dk2nu 1.00.00 REQUIRED)

###### Compiler set up
add_library(dk2nuana_dependencies INTERFACE)
target_link_libraries(dk2nuana_dependencies INTERFACE
  dk2nu::dk2nuTree)
target_include_directories(dk2nuana_dependencies INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include> )
set_target_properties(dk2nuana_dependencies PROPERTIES EXPORT_NAME commondeps)
add_library(dk2nuana::commondeps ALIAS dk2nuana_dependencies)

install(TARGETS dk2nuana_dependencies EXPORT dk2nuana-targets)

add_subdirectory(src/dk2nuana)


install(EXPORT dk2nuana-targets
        NAMESPACE dk2nuana::
        DESTINATION lib/cmake/dk2nuana)

configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/Templates/setup.dk2nuana.sh.in
  ${PROJECT_BINARY_DIR}/setup.dk2nuana.sh @ONLY)
install(PROGRAMS ${PROJECT_BINARY_DIR}/setup.dk2nuana.sh DESTINATION bin)





