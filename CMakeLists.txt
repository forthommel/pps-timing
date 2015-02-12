cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(PPSsimulation)

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

#----------------------------------------------------------------------------
# ROOT include
#
set(GCC_COMPILE_FLAGS "-Wno-shadow -fPIC")
add_definitions(${GCC_COMPILE_FLAGS})
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_DIR})


include_directories(${PROJECT_SOURCE_DIR}/sw/include)
include_directories(${PROJECT_SOURCE_DIR}/detectors/include)
add_subdirectory(sw)
add_subdirectory(detectors)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

add_executable(PPSsim main.cc $<TARGET_OBJECTS:detectors> $<TARGET_OBJECTS:sw>)
target_link_libraries(PPSsim ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#

set(PPS_MACROS
  init.mac
  init_vis.mac vis.mac viswrl.mac
  run1.mac run2.mac
)

foreach(_script ${PPS_MACROS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/test/${_script}
    ${PROJECT_BINARY_DIR}/test/${_script}
    COPYONLY
  )
endforeach()
configure_file(${PROJECT_SOURCE_DIR}/test/rootlogon.C ${PROJECT_BINARY_DIR}/rootlogon.C COPYONLY)

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#

add_custom_target(ppsSim DEPENDS PPSsim)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#

install(TARGETS PPSsim DESTINATION bin)

