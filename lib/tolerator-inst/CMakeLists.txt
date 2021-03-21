add_library(tolerator-inst
  Tolerator.cpp
)
target_include_directories(tolerator-inst
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
set_target_properties(tolerator-inst PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

add_library(tolerator-lib MODULE
  Tolerator.cpp
)
target_include_directories(tolerator-lib
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
set_target_properties(tolerator-lib PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)
