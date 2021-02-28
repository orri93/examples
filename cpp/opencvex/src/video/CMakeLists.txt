set(opencv_ex_video_target video)

find_package(OpenCV REQUIRED core imgcodecs videoio)

list(APPEND opencv_ex_video_source
  video.cpp)

# list(APPEND opencv_ex_video_include ${OpenCV_INCLUDE_DIRS})

list(APPEND opencv_ex_video_libraries
  ${OpenCV_LIBS})

message(STATUS "  Video Libraries           : ${opencv_ex_video_libraries}")

# if (MSVC)
#   list(APPEND opencv_ex_video_definitions
#     HAVE_M_PI)
# endif (MSVC)

add_executable(${opencv_ex_video_target}
  ${opencv_ex_video_source})

if (opencv_ex_video_definitions)
  target_compile_definitions(${opencv_ex_video_target} PUBLIC
    ${opencv_ex_video_definitions})
endif ()

if (opencv_ex_video_include)
  target_include_directories(${opencv_ex_video_target} PUBLIC
    ${opencv_ex_video_include})
endif ()

target_link_libraries(${opencv_ex_video_target}
  ${opencv_ex_video_libraries})

if(DEPLOY_PDB_FILES)
  install(FILES "$<TARGET_PDB_FILE:${opencv_ex_video_target}>"
    DESTINATION pdb
    COMPONENT pdb)
endif()

install(TARGETS ${opencv_ex_video_target}
  RUNTIME DESTINATION bin)
