#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(quarticL)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# ROOT include
#
set(GCC_COMPILE_FLAGS "-Wno-shadow -fPIC")
add_definitions(${GCC_COMPILE_FLAGS})
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Generate the ROOT dictionary to store TObjects directly
# in the output TTrees
#

file(GLOB dict_headers ${PROJECT_SOURCE_DIR}/include/QuartLRunInfo.hh)
file(GLOB dict_sources ${PROJECT_SOURCE_DIR}/src/QuartLRunInfo.cc)
ROOT_GENERATE_DICTIONARY(PPSDict ${dict_headers} LINKDEF "${PROJECT_SOURCE_DIR}/include/LinkDef.h")
list(APPEND sources PPSDict.cxx)
#message(STATUS "Headers for dictionary : " ${dict_headers})
#message(STATUS "Sources for dictionary : " ${dict_sources})
add_library(PPS SHARED ${dict_sources} PPSDict.cxx)
target_link_libraries(PPS ${ROOT_LIBRARIES} ${ROOT_COMPONENT_LIBRARIES})
install(TARGETS PPS DESTINATION lib)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

add_executable(QuartL QuartL.cc ${sources} ${headers})
target_link_libraries(QuartL ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#

set(QUARTICL_SCRIPTS
  QuartL.in
  QuartL.out
  init.mac
  init_vis.mac
  run1.mac
  run2.mac
  vis.mac
  viswrl.mac
  rootlogon.C
  )

foreach(_script ${QUARTICL_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#

add_custom_target(quarticL DEPENDS QuartL)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#

install(TARGETS QuartL DESTINATION bin)

