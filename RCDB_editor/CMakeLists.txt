include_directories(src)

find_package(Qt4 REQUIRED)

file(GLOB_RECURSE source_files src/*.cpp src/*.h)
set(MOC_FILES src/mainWin.h src/editDialog.h)
set(uic_file src/mainWin.ui src/editDialog.ui)
set(EXECUTABLE_OUTPUT_PATH ../bin)

QT4_WRAP_CPP(QT_MOC_FILE_LIST ${MOC_FILES})
QT4_WRAP_UI(uic_generated_files ${uic_file})

include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_definitions(${QT_DEFINITIONS})

add_executable(RCDB_editor ${source_files} ${QT_MOC_FILE_LIST} ${uic_generated_files})
target_link_libraries(RCDB_editor ${QT_LIBRARIES})
