add_library(tolerator-rt
  runtime.cpp
)
set_target_properties(tolerator-rt PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)
