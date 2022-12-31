add_library(tolerator-inst)
target_sources(tolerator-inst
  PRIVATE
    Tolerator.cpp
)
target_include_directories(tolerator-inst
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
target_compile_features(tolerator-inst PUBLIC cxx_std_20)
set_target_properties(tolerator-inst PROPERTIES
  LINKER_LANGUAGE CXX
)

add_library(tolerator-lib MODULE)
target_sources(tolerator-lib
  PRIVATE
    Tolerator.cpp
)
target_compile_features(tolerator-lib PUBLIC cxx_std_20)
target_include_directories(tolerator-lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
set_target_properties(tolerator-lib PROPERTIES
  LINKER_LANGUAGE CXX
)
