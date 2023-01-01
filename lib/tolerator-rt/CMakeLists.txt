add_library(tolerator-rt)
target_sources(tolerator-rt
  PRIVATE
    runtime.cpp
)
target_compile_features(tolerator-rt PUBLIC cxx_std_20)
set_target_properties(tolerator-rt PROPERTIES
  LINKER_LANGUAGE CXX
  POSITION_INDEPENDENT_CODE ON
)
