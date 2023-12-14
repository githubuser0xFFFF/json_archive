cmake_minimum_required(VERSION 3.14)
project(json_archive LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Boost 1.54.0 REQUIRED COMPONENTS serialization)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_definitions(-DDEBUG=1 -DBOOST_PP_VARIADICS=1)
endif()

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_library(${PROJECT_NAME} SHARED 
  json_iarchive_impl.cpp 
  json_oarchive_impl.cpp 
  json_archive.cpp
)

# Append debug suffix to debug library
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

add_executable(${PROJECT_NAME}_demo demo.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC boost_serialization-mt)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${Boost_INCLUDE_DIRS}
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}
	$<INSTALL_INTERFACE:include>)

target_link_libraries(${PROJECT_NAME}_demo ${PROJECT_NAME})

# Install library
install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install headers
file(GLOB INSTALL_HEADERS "./*.hpp")
install(FILES ${INSTALL_HEADERS}
	      DESTINATION include/boost/archive
)

# Set MinGW-specific linker flags
if (MINGW)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--export-all-symbols")
endif()
