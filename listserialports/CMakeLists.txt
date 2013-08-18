project(listserialports)
cmake_minimum_required (VERSION 2.6)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/local-bin/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/local-bin/lib)
set(ARCHIVE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/local-bin/lib)

add_subdirectory(serialportlist)

add_executable(listserialports main.c)
target_link_libraries(listserialports serialportlist)
