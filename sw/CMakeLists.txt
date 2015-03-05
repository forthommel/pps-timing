include_directories(${ROOT_INCLUDE_DIR})
include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/detectors/include)
include_directories(${PROJECT_SOURCE_DIR}/beampockets/include)

file(GLOB sources src/*.cc)
file(GLOB headers include/*.hh)

#----------------------------------------------------------------------------
# Generate the ROOT dictionary to store TObjects directly
# in the output TTrees
#

file(GLOB dict_headers include/*.h)
list(REMOVE_ITEM dict_headers include/LinkDef.h)
file(GLOB dict_sources src/*.cpp)

# message(STATUS "Headers for dictionary : " ${dict_headers})
# message(STATUS "Sources for dictionary : " ${dict_sources})
#message(STATUS "ROOT version: " ${ROOT_VERSION})
#ROOT_GENERATE_DICTIONARY(PPSDict ${dict_headers} LINKDEF include/LinkDef.h)
GENERATE_DICTIONARY(PPSDict ${dict_headers} LINKDEF include/LinkDef.h)
list(APPEND sources PPSDict.cxx)
add_library(PPS SHARED ${dict_sources} PPSDict.cxx)
target_link_libraries(PPS ${ROOT_LIBRARIES} ${ROOT_COMPONENT_LIBRARIES})
##install(TARGETS PPS DESTINATION lib)

list(APPEND headers ${dict_headers})

add_library(sw OBJECT ${sources} ${dict_sources})

