if (GOS_USE_GTEST_PACKAGE OR GOS_USE_GTEST_DISCOVER)
  include(GoogleTest)
endif ()

set(gos_for_go_test_target goscdrillingtest)
set(gos_for_go_test_name goscdrillingtest)

list(APPEND gos_for_go_test_source
  forgo.cpp)

#list(APPEND gos_for_go_test_definitions
#  _CRT_SECURE_NO_WARNINGS)

list(APPEND gos_for_go_test_include
  ${gos_examples_gtest_include}
  ${gos_examples_include})

add_executable(${gos_for_go_test_target}
  ${gos_for_go_test_source})

if (gos_for_go_test_definitions)
  target_compile_definitions(${gos_for_go_test_target} PUBLIC
    ${gos_for_go_test_definitions})
endif ()

target_include_directories(${gos_for_go_test_target} PUBLIC
  ${gos_for_go_test_include})

target_link_libraries(${gos_for_go_test_target}
  ${gos_examples_gtest_libraries}
  ${gos_for_go_library_target})

#if(CLANG_TIDY_EXE)
#  set_target_properties(${gos_for_go_test_target} PROPERTIES
#    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
#endif()

if (GOS_USE_GTEST_PACKAGE OR GOS_USE_GTEST_DISCOVER)
  gtest_discover_tests(${gos_for_go_test_target}
    XML_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/xmlout)
else ()
  add_test(NAME ${gos_for_go_test_name} COMMAND
    ${gos_for_go_test_target})
endif ()
