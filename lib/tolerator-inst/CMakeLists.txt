add_library(tolerator-inst
  Tolerator.cpp
)
target_include_directories(tolerator-inst
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_library(tolerator-lib MODULE
  Tolerator.cpp
)
target_include_directories(tolerator-lib
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
