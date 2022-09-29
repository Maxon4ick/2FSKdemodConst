cmake_minimum_required(VERSION 3.0)
project (Pll)


file(GLOB_RECURSE  SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})


target_link_libraries(${PROJECT_NAME})

include("unittestFil.cmake")

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
