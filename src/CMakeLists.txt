# OpenNURBS CMake Build system
# see GNU GENERAL PUBLIC LICENSE, version 2, attached

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(
  main
  geom_defs
)
add_subdirectory(main)
