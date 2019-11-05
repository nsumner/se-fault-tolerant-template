
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# If you need to specify the path to clang on your system, do so here
set(CLANG "clang")


add_library(doctest-main OBJECT
  "doctest.cpp"
)


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
    COMMAND ${CLANG} -emit-llvm -S ${c_file} -o ${OUT_PATH}
    DEPENDS ${c_file}
    BYPRODUCTS ${OUT_PATH}
    COMMENT "Compiling to .ll: ${OUT_PATH}"
    VERBATIM
  )
  add_custom_target(${testcase}_ll DEPENDS ${OUT_PATH})
  set_property(TARGET ${testcase}_ll PROPERTY EXCLUDE_FROM_ALL OFF)
endforeach()


file(GLOB unit_files "${CMAKE_CURRENT_SOURCE_DIR}/unit/*.cpp")
foreach(unit_file ${unit_files})
  get_filename_component(testcase ${unit_file} NAME_WE)
  
  add_library(unit-${testcase} OBJECT
    ${unit_file}
  )
  target_include_directories(unit-${testcase} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
endforeach()


function(add_simple_unit_test unit_name policy)
  set(TEST_ID "unit--${policy}--${unit_name}")
  set(OUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_ID}")
  add_custom_command(OUTPUT ${OUT_PATH}
    COMMAND "$<TARGET_FILE:tolerator>" --${policy} ${CMAKE_CURRENT_SOURCE_DIR}/ll/${unit_name}.ll -o ${OUT_PATH} -e $<TARGET_OBJECTS:doctest-main> -e $<TARGET_OBJECTS:unit-${unit_name}>
    DEPENDS ${unit_name}_ll unit-${unit_name} doctest-main
    BYPRODUCTS ${OUT_PATH}
    COMMENT "Instrumenting test for ${OUT_PATH}"
    VERBATIM
  )
  add_custom_target(${TEST_ID}_test DEPENDS ${OUT_PATH})
  set_property(TARGET ${TEST_ID}_test PROPERTY EXCLUDE_FROM_ALL OFF)

  
  add_test(NAME "${TEST_ID}"
    COMMAND ${OUT_PATH}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )
  set_tests_properties("${TEST_ID}" PROPERTIES LABELS "${testcase} ${policy}")
endfunction(add_simple_unit_test)


function(add_simple_system_target name policy)
  set(TEST_ID "system--${policy}--${name}")
  set(OUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_ID}")
  add_custom_command(OUTPUT ${OUT_PATH}
    COMMAND "$<TARGET_FILE:tolerator>" --${policy} ${CMAKE_CURRENT_SOURCE_DIR}/ll/${name}.ll -o ${OUT_PATH}
    DEPENDS ${name}_ll
    BYPRODUCTS ${OUT_PATH}
    COMMENT "Instrumenting test for ${OUT_PATH}"
    VERBATIM
  )
  add_custom_target(${TEST_ID}_test DEPENDS ${OUT_PATH})
  set_property(TARGET ${TEST_ID}_test PROPERTY EXCLUDE_FROM_ALL OFF)
endfunction(add_simple_system_target)


function(add_system_test system_target policy)
  set(TEST_ID "system--${policy}--${system_target}")
  set(OUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_ID}")
  add_test(NAME "${TEST_ID}"
    COMMAND ${OUT_PATH} ${ARGN}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )
  set_tests_properties("${TEST_ID}" PROPERTIES LABELS "${testcase} ${policy}")
endfunction(add_system_test)


function(simple_all_policies_unit_test unit_name)
  add_simple_unit_test(${unit_name} log)
  add_simple_unit_test(${unit_name} ignore)
  add_simple_unit_test(${unit_name} defaults)
  add_simple_unit_test(${unit_name} returns)
endfunction(simple_all_policies_unit_test)


function(simple_all_policies_system_target name)
  add_simple_system_target(${name} log)
  add_simple_system_target(${name} ignore)
  add_simple_system_target(${name} defaults)
  add_simple_system_target(${name} returns)
endfunction(simple_all_policies_system_target)


function(simple_all_policies_system_test name)
  add_system_test(${name} log ${ARGN})
  add_system_test(${name} ignore ${ARGN})
  add_system_test(${name} defaults ${ARGN})
  add_system_test(${name} returns ${ARGN})
endfunction(simple_all_policies_system_test)


simple_all_policies_unit_test(signed-int-division)
simple_all_policies_unit_test(signed-char-division)
simple_all_policies_unit_test(unsigned-char-division)


simple_all_policies_system_target(local-arrays)
simple_all_policies_system_test(local-arrays a b c d e f g h i j)
