list(APPEND gos_for_go_library_source
  forgo.c)

#list(APPEND gos_for_go_library_definitions)

list(APPEND gos_for_go_library_include
  ${gos_examples_include})

add_library(${gos_for_go_library_target}
  ${gos_for_go_library_source})

if (gos_for_go_library_definitions)
  target_compile_definitions(${gos_for_go_library_target} PUBLIC
    ${gos_for_go_library_definitions})
endif ()

target_include_directories(${gos_for_go_library_target} PUBLIC
  ${gos_for_go_library_include})

if (gos_for_go_library_public_header)
  set_target_properties(${gos_for_go_library_target}
    PROPERTIES PUBLIC_HEADER
    "${gos_for_go_library_public_header}")
endif ()

install(TARGETS ${gos_for_go_library_target}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/gos
  ARCHIVE DESTINATION lib)
