include_directories(${ROOT_INCLUDE_DIR})
include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/sw/include)

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
ROOT_GENERATE_DICTIONARY(QuartLDict ${dict_headers} LINKDEF include/LinkDef.h)
list(APPEND sources QuartLDict.cxx)
add_library(QuartL SHARED ${dict_sources} QuartLDict.cxx)
target_link_libraries(QuartL ${ROOT_LIBRARIES} ${ROOT_COMPONENT_LIBRARIES})
#install(TARGETS PPS DESTINATION lib)

list(APPEND headers ${dict_headers})

#message(STATUS "Headers for detectors : " ${headers})

add_library(detectors OBJECT ${sources} ${dict_sources})

