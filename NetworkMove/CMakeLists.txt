include_directories(src ../shared_lib/src)
link_directories(../lib /usr/local/lib)

file(GLOB_RECURSE source_files src/*.cpp src/*.h)
set(EXECUTABLE_OUTPUT_PATH ../bin)

if(DEBUG)
    add_definitions(-g)
endif()

add_executable(client ${source_files})
target_link_libraries(client sfml-network sfml-graphics sfml-audio sfml-window sfml-system util CEGUIBase CEGUIOpenGLRenderer)
install(TARGETS client DESTINATION ${INSTALL_PATH})
