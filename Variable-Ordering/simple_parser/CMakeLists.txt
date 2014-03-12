################################################################################

cmake_minimum_required (VERSION 2.8.10)

################################################################################

project (miniparser)

################################################################################

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.54.0 REQUIRED)
message("-- Boost Include: ${Boost_INCLUDE_DIR}")
message("-- Boost Libraries: ${Boost_LIBRARY_DIRS}")

################################################################################

if (NO_COROUTINE)
  add_definitions("-DHAS_NO_BOOST_COROUTINE")
endif ()

add_definitions("-Wall")
add_definitions("-std=c++11")
add_definitions("-ftemplate-depth=256")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_definitions("-stdlib=libc++")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++11 -stdlib=libc++")
  set(CMAKE_CXX_FLAGS_RELEASE "-O4")
endif ()

set( CMAKE_CXX_FLAGS_RELEASE
     "${CMAKE_CXX_FLAGS_RELEASE} -fstrict-aliasing -DNDEBUG")

set( CMAKE_CXX_FLAGS_DEBUG
     "${CMAKE_CXX_FLAGS_DEBUG} -O0")

################################################################################

include_directories("${Boost_INCLUDE_DIRS}")
include_directories("${PROJECT_SOURCE_DIR}/src")

################################################################################

set(SOURCES
    src/main.cc
    src/force/HyperEdge.cpp
    src/force/Variable.cpp
    src/parsers/bpn.cc
    src/parsers/helpers.cc
    src/parsers/parse_error.cc
    src/parsers/parse.cc
    src/parsers/prod.cc
    src/parsers/tina.cc
    src/parsers/xml.cc
    src/pn/module.cc
    src/pn/net.cc
    src/pn/place.cc
    src/pn/transition.cc
    )

add_executable(simple ${SOURCES})
target_link_libraries(simple ${Boost_LIBRARIES})

################################################################################
