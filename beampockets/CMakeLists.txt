include_directories(${ROOT_INCLUDE_DIR})
include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/sw/include)

file(GLOB sources src/*.cc)
file(GLOB headers include/*.hh)

#----------------------------------------------------------------------------
# Generate the ROOT dictionary to store TObjects directly
# in the output TTrees
#

#file(GLOB dict_headers include/*.h)
#file(GLOB dict_sources src/*.cpp)
#list(REMOVE_ITEM dict_headers include/LinkDef.h)
#message(STATUS "Headers for dictionary : " ${dict_headers})
#message(STATUS "Sources for dictionary : " ${dict_sources})
#ROOT_GENERATE_DICTIONARY(BPDict ${dict_headers} LINKDEF include/LinkDef.h)
#list(APPEND sources BPDict.cxx)
#add_library(BP SHARED ${dict_sources} BPDict.cxx)
#target_link_libraries(BP ${ROOT_LIBRARIES} ${ROOT_COMPONENT_LIBRARIES})
#install(TARGETS PPS DESTINATION lib)

#add_library(beampockets OBJECT ${sources} ${dict_sources})
add_library(beampockets OBJECT ${sources})

