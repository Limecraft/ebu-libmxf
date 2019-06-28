cmake_minimum_required(VERSION 2.8)

project (libMXF)

set(CMAKE_MODULE_PATH "${libMXF_SOURCE_DIR}/cmake/modules")

configure_file (
  "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.pc.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc" @ONLY
  )
  
aux_source_directory(${PROJECT_SOURCE_DIR}/mxf libMXF_sources)

include_directories(${PROJECT_SOURCE_DIR})

add_library (libMXF STATIC ${libMXF_sources})

if (MSVC)
    
    include_directories("${PROJECT_SOURCE_DIR}/msvc_build/vs10")


endif (MSVC)
