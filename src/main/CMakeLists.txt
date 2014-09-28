# OpenNURBS CMake Build system
# see GNU GENERAL PUBLIC LICENSE, version 2, attached

set(name OpenNURBS)

set(sources
  OpenNURBS.cpp
)

add_executable(${name} ${sources})

install(TARGETS OpenNURBS DESTINATION bin)

