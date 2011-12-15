include_directories(src)

file(GLOB_RECURSE source_files src/*.cpp src/*.h)
set(EXECUTABLE_OUTPUT_PATH ../bin)

add_executable(server ${source_files})
target_link_libraries(server sfml-network sfml-system)

