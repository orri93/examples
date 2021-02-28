set(opencv_ex_display_target display)

find_package(OpenCV REQUIRED core highgui)

list(APPEND opencv_ex_display_source
  display.cpp)

# list(APPEND opencv_ex_display_include )

list(APPEND opencv_ex_display_libraries
  ${OpenCV_LIBS})

message(STATUS "  Display Libraries         : ${opencv_ex_display_libraries}")

# if (MSVC)
#   list(APPEND opencv_ex_display_definitions
#     HAVE_M_PI)
# endif (MSVC)

add_executable(${opencv_ex_display_target}
  ${opencv_ex_display_source})

if (opencv_ex_display_definitions)
  target_compile_definitions(${opencv_ex_display_target} PUBLIC
    ${opencv_ex_display_definitions})
endif ()

if (opencv_ex_display_include)
  target_include_directories(${opencv_ex_display_target} PUBLIC
    ${opencv_ex_display_include})
endif ()

target_link_libraries(${opencv_ex_display_target}
  ${opencv_ex_display_libraries})

if(DEPLOY_PDB_FILES)
  install(FILES "$<TARGET_PDB_FILE:${opencv_ex_display_target}>"
    DESTINATION pdb
    COMPONENT pdb)
endif()

install(TARGETS ${opencv_ex_display_target}
  RUNTIME DESTINATION bin)
