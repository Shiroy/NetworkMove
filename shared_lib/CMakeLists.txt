if(DEBUG)
    add_definitions(-g)
endif()

include_directories(src)

set(LIBRARY_OUTPUT_PATH ../lib)

file(GLOB_RECURSE src_files src/*.cpp src/*.h)
add_library(util STATIC ${src_files})
