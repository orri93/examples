set(goodmain_target goodmain)

list(APPEND goodmain_source
  goodmain.c)

if (MSVC)
  list(APPEND goodmain_definitions
    _CRT_SECURE_NO_WARNINGS)
endif (MSVC)

add_executable(${goodmain_target} ${goodmain_source})

if (goodmain_definitions)
  target_compile_definitions(${goodmain_target} PUBLIC ${goodmain_definitions})
endif ()
