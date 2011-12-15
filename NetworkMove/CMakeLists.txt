include_directories(src)

file(GLOB_RECURSE source_files src/*.cpp src/*.h)
set(EXECUTABLE_OUTPUT_PATH ../bin)

add_executable(client ${source_files})
target_link_libraries(client sfml-network sfml-graphics sfml-window sfml-system sfgui)
