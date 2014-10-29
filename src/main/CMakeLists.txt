# OpenNURBS CMake Build system
# see GNU GENERAL PUBLIC LICENSE, version 2, attached

set(name OpenNURBS_Demo)

set(sources
  OpenNURBS.cpp
)

set(libname OpenNURBS)
set(libsources
  ../geom_defs/gCurve.hpp
  ../geom_defs/gPoint.hpp
)

add_executable(${name} ${sources})
add_library(${libname} ${libsources})

set_target_properties(${libname} PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS OpenNURBS DESTINATION bin)

