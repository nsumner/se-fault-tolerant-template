
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake" 
               "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(tolerator)
target_sources(tolerator
  PRIVATE
    main.cpp
)

llvm_map_components_to_libnames(REQ_LLVM_LIBRARIES ${LLVM_TARGETS_TO_BUILD}
        asmparser core linker bitreader bitwriter irreader ipo scalaropts
        analysis target mc support
)

target_link_libraries(tolerator
  PRIVATE
    tolerator-inst
    ${REQ_LLVM_LIBRARIES}
)

# Platform dependencies.
if( WIN32 )
  find_library(SHLWAPI_LIBRARY shlwapi)
  target_link_libraries(tolerator
    PRIVATE
      ${SHLWAPI_LIBRARY}
  )
else()
  find_package(Threads REQUIRED)
  find_package(Curses REQUIRED)
  target_link_libraries(tolerator
    PRIVATE
      ${CMAKE_THREAD_LIBS_INIT}
      ${CMAKE_DL_LIBS}
      ${CURSES_LIBRARIES}
  )
endif()

target_compile_features(tolerator PUBLIC cxx_std_20)
set_target_properties(tolerator PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX ""
)

install(TARGETS tolerator
  RUNTIME DESTINATION bin
)

