cmake_minimum_required(VERSION 3.18)

project(pdtt)

include(cmake/CompileOptions.cmake)
include(cmake/Debug.cmake)
include(cmake/Libraries.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/Config.cmake)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
    "src/*.cc"
)
list(REMOVE_ITEM SRCS main.cc)

add_executable(main
  src/main.cc ${SRCS}
)

target_include_directories(main PRIVATE
  include
  ${CURSES_INCLUDE_DIR}
  ${PDARGS_INCLUDE_DIR}
)

target_link_libraries(main PRIVATE
  ${CURSES_LIBRARIES}
)
