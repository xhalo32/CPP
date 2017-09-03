cmake_minimum_required (VERSION 2.6)

project(nmines)
find_package( Curses REQUIRED )

add_executable(nmines main.cpp screens.cpp)

include_directories( ${CURSES_INCLUDE_DIRS} )
target_link_libraries( nmines ${CURSES_LIBRARIES} )
