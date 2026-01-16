cmake_minimum_required( VERSION 3.10 )

project( MLR VERSION 0.1 LANGUAGES CXX )
set(PROJECT_DESCRIPTION "MLR C++ math library")

include(GNUInstallDirs)

if( NOT CMAKE_BUILD_TYPE )
        set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
endif()
set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

if( CMAKE_BUILD_TYPE EQUAL Debug )
	add_compile_options(-g)
endif()
if( CMAKE_GENERATOR_PLATFORM STREQUAL "x64" OR CMAKE_GENERATOR_PLATFORM STREQUAL "x86_64" OR CMAKE_GENERATOR_PLATFORM STREQUAL "AMD64" )
	add_compile_options(-mfpmath=sse)
endif()

add_compile_options(-march=native)
add_compile_options(-O3)
add_compile_options(-ftree-vectorize)
add_compile_options(-fopenmp-simd)
add_compile_options(-D_FILE_OFFSET_BITS=64)
add_compile_options(-fdata-sections)
add_compile_options(-fpermissive)
add_compile_options(-ffunction-sections)
add_compile_options(-Wno-array-bounds)
add_compile_options(-Wno-unused-parameter)
add_compile_options(-Wno-pedantic)
add_compile_options(-Wno-narrowing)
add_link_options(-Wl,--gc-sections)
add_link_options(-Wl,--print-gc-sections)
add_link_options(-Wl,-s)

add_library( mlr INTERFACE )
target_include_directories( mlr INTERFACE
        PUBLIC_HEADER $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PUBLIC_HEADER $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/mlr>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mlr DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT headers)

add_executable( cross examples/cross.cpp )
target_link_libraries( cross mlr )
add_executable( det examples/det.cpp )
target_link_libraries( det mlr )
add_executable( vec examples/vec.cpp )
target_link_libraries( vec mlr )
add_executable( id examples/id.cpp )
target_link_libraries( id mlr )
