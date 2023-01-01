
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# If you need to specify the paths to clang or opt on your system, do so here
find_program(CLANG
  NAMES clang-15 clang
  # PATHS # Add custom paths here
  DOC "Clang compiler"
)
if (NOT CLANG)
    message(FATAL_ERROR "Unable to locate clang.")
endif()

find_program(OPT
  NAMES opt-15 opt
  # PATHS # Add custom paths here
  DOC "LLVM opt utility"
)
if (NOT OPT)
    message(FATAL_ERROR "Unable to locate opt.")
endif()


add_library(doctest-main OBJECT
  "doctest.cpp"
)
set_property(TARGET doctest-main PROPERTY POSITION_INDEPENDENT_CODE ON)

# First, we traverse all files in `c`, adding targets that produce bitcode
# in the `ll` directory. Each unit test will analyze this bitcode, linking in
# any helper behavior from custom libraries along the way. This allows reuse
# of instrumented code to test different cases while still allowing isolation
# of the individual test cases.

file(GLOB c_files "${CMAKE_CURRENT_SOURCE_DIR}/c/*.c")
foreach(c_file ${c_files})
  get_filename_component(testcase ${c_file} NAME_WE)

  set(OUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ll/${testcase}.ll")
  add_custom_command(OUTPUT ${OUT_PATH}
    COMMAND ${CLANG} -emit-llvm -S ${c_file} -o - | ${OPT} -mem2reg -S -o ${OUT_PATH}
    DEPENDS ${c_file}
    COMMENT "Compiling to .ll: ${OUT_PATH}"
    VERBATIM
  )
  add_custom_target(${testcase}_ll DEPENDS ${OUT_PATH})
  set_property(TARGET ${testcase}_ll PROPERTY EXCLUDE_FROM_ALL OFF)
endforeach()


file(GLOB unit_files "${CMAKE_CURRENT_SOURCE_DIR}/unit/*.cpp")
foreach(unit_file ${unit_files})
  get_filename_component(testcase ${unit_file} NAME_WE)

  add_library(unit-${testcase} OBJECT)
  target_sources(unit-${testcase}
    PRIVATE
      ${unit_file}
  )
  target_include_directories(unit-${testcase}
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}
  )
  set_target_properties(unit-${testcase} PROPERTIES
    POSITION_INDEPENDENT_CODE ON
  )
endforeach()

set(INSTRUMENTATION_TARGETS)

function(add_simple_unit_test unit_name policy)
  set(TEST_ID "unit--${policy}--${unit_name}")
  set(OUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_ID}")
  add_custom_command(OUTPUT ${OUT_PATH}
    COMMAND "$<TARGET_FILE:tolerator>"
      --${policy}
      ${CMAKE_CURRENT_SOURCE_DIR}/ll/${unit_name}.ll
      -o ${OUT_PATH}
      -e $<TARGET_OBJECTS:doctest-main>
      -e $<TARGET_OBJECTS:unit-${unit_name}>
    DEPENDS tolerator ${unit_name}_ll unit-${unit_name} doctest-main tolerator-rt
    COMMENT "Instrumenting test for ${OUT_PATH}"
    VERBATIM
  )
  add_custom_target(${TEST_ID}_test DEPENDS ${OUT_PATH} tolerator tolerator-rt)
  list(APPEND INSTRUMENTATION_TARGETS "${TEST_ID}_test")
  set(INSTRUMENTATION_TARGETS "${INSTRUMENTATION_TARGETS}" PARENT_SCOPE)

  add_test(NAME "${TEST_ID}"
    COMMAND ${OUT_PATH}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )
  set_tests_properties("${TEST_ID}" PROPERTIES
    FIXTURES_REQUIRED instrumentation_phase
    LABELS "${testcase} ${policy}"
  )
endfunction(add_simple_unit_test)


function(add_simple_system_target name policy)
  set(TEST_ID "system--${policy}--${name}")
  set(OUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_ID}")
  add_custom_command(OUTPUT ${OUT_PATH}
    COMMAND "$<TARGET_FILE:tolerator>"
      --${policy}
      ${CMAKE_CURRENT_SOURCE_DIR}/ll/${name}.ll
      -o ${OUT_PATH}
    DEPENDS tolerator ${name}_ll tolerator-rt
    COMMENT "Instrumenting test for ${OUT_PATH}"
    VERBATIM
  )
  add_custom_target(${TEST_ID}_test DEPENDS ${OUT_PATH} tolerator tolerator-rt)
  list(APPEND INSTRUMENTATION_TARGETS "${TEST_ID}_test")
  set(INSTRUMENTATION_TARGETS "${INSTRUMENTATION_TARGETS}" PARENT_SCOPE)
endfunction(add_simple_system_target)


set(SYSTEM_TEST_COUNT 0)

function(add_system_test system_target policy increase_count)
  set(TEST_PROGRAM "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/system--${policy}--${system_target}")
  set(TEST_ID "system--${SYSTEM_TEST_COUNT}--${policy}--${system_target}")
  add_test(NAME "${TEST_ID}"
    COMMAND ${TEST_PROGRAM} ${ARGN}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )
  set_tests_properties("${TEST_ID}" PROPERTIES
    FIXTURES_REQUIRED instrumentation_phase
    LABELS "${testcase} ${policy}"
  )

  if (increase_count)
    math(EXPR SYSTEM_TEST_COUNT "${SYSTEM_TEST_COUNT}+1")
  endif()
  set(SYSTEM_TEST_COUNT ${SYSTEM_TEST_COUNT} PARENT_SCOPE)
endfunction(add_system_test)


function(simple_all_policies_unit_test unit_name)
  add_simple_unit_test(${unit_name} log)
  add_simple_unit_test(${unit_name} ignore)
  add_simple_unit_test(${unit_name} defaults)
  add_simple_unit_test(${unit_name} returns)
  set(INSTRUMENTATION_TARGETS "${INSTRUMENTATION_TARGETS}" PARENT_SCOPE)
endfunction(simple_all_policies_unit_test)


function(simple_all_policies_system_target name)
  add_simple_system_target(${name} log)
  add_simple_system_target(${name} ignore)
  add_simple_system_target(${name} defaults)
  add_simple_system_target(${name} returns)
  set(INSTRUMENTATION_TARGETS "${INSTRUMENTATION_TARGETS}" PARENT_SCOPE)
endfunction(simple_all_policies_system_target)


function(simple_all_policies_system_test name)
  add_system_test(${name} log NO ${ARGN})
  add_system_test(${name} ignore NO ${ARGN})
  add_system_test(${name} defaults NO ${ARGN})
  add_system_test(${name} returns YES ${ARGN})
  set(SYSTEM_TEST_COUNT ${SYSTEM_TEST_COUNT} PARENT_SCOPE)
endfunction(simple_all_policies_system_test)


simple_all_policies_unit_test(signed-int-division)
simple_all_policies_unit_test(signed-char-division)
simple_all_policies_unit_test(unsigned-char-division)

simple_all_policies_unit_test(free-middle)
simple_all_policies_unit_test(free-local)
simple_all_policies_unit_test(free-global)
simple_all_policies_unit_test(free-wild)
simple_all_policies_unit_test(free-twice)

simple_all_policies_unit_test(read-local-byte-array)
simple_all_policies_unit_test(store-local-byte-array)

simple_all_policies_unit_test(read-malloc-byte)
simple_all_policies_unit_test(store-malloc-byte)

simple_all_policies_unit_test(read-global-byte)
simple_all_policies_unit_test(store-global-byte)

simple_all_policies_unit_test(read-malloc-overlap)

simple_all_policies_unit_test(read-malloc-after-free)
simple_all_policies_unit_test(read-local-after-return)

simple_all_policies_unit_test(read-failure-propagates)

###### Interaction!
# Invalid read causes zero return and division by 0, which is used as an index.

simple_all_policies_system_target(local-arrays)
simple_all_policies_system_test(local-arrays a b c d e f g h i j)

add_test(NAME "instrument_tests"
  COMMAND "${CMAKE_COMMAND}"
    --build "${CMAKE_BINARY_DIR}"
    --config "$<CONFIG>"
    --target ${INSTRUMENTATION_TARGETS}
)
set_tests_properties("instrument_tests" PROPERTIES FIXTURES_SETUP instrumentation_phase)
