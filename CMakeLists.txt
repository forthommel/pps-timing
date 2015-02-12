cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(PPSsimulation)
set(PPS_MODULES sw detectors beampockets)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
#----------------------------------------------------------------------------

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#----------------------------------------------------------------------------

include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# ROOT include
#----------------------------------------------------------------------------

set(GCC_COMPILE_FLAGS "-Wno-shadow -fPIC")
add_definitions(${GCC_COMPILE_FLAGS})
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_DIR})

foreach(_module ${PPS_MODULES})
  include_directories(${PROJECT_SOURCE_DIR}/${_module}/include)
  add_subdirectory(${_module})
endforeach()

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#----------------------------------------------------------------------------

add_executable(ppsSim main.cc $<TARGET_OBJECTS:detectors> $<TARGET_OBJECTS:sw>)
target_link_libraries(ppsSim ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory
#----------------------------------------------------------------------------

set(PPS_MACROS
  init_geometry.mac
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
add_custom_target(PPSSimul DEPENDS ppsSim)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#----------------------------------------------------------------------------

install(TARGETS ppsSim DESTINATION bin)

#----------------------------------------------------------------------------
# Generate the Doxygen documentation
#----------------------------------------------------------------------------

set(DOC_SOURCE "${PROJECT_SOURCE_DIR}/sw/include ${PROJECT_SOURCE_DIR}/detectors/include")
set(DOC_PROJECT_ROOT ${DOC_SOURCE} CACHE PATH "Root of the project sources")
set(DOC_DIR ${PROJECT_SOURCE_DIR}/doc)
execute_process(COMMAND git -C ${PROJECT_SOURCE_DIR} describe --always OUTPUT_VARIABLE DOC_PROJECT_VERSION ERROR_QUIET)
find_package(Doxygen REQUIRED) # Doxygen
set(DOC_GENERATE_PDF "YES")
## Generate the Doxyfile from template
configure_file(${DOC_DIR}/Doxyfile.in ${DOC_DIR}/Doxyfile @ONLY)
add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${DOC_DIR}/Doxyfile
  DEPENDS ${DOC_DIR}/Doxyfile.in ${DOC_DIR}/Doxyfile
  COMMENT "Generating documentation"
  SOURCES ${DOC_DIR}/Doxyfile
)
set_source_files_properties(${DOC_DIR}/Doxyfile PROPERTIES GENERATED 1)
