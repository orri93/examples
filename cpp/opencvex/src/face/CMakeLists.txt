set(opencv_ex_face_target face)

find_package(OpenCV REQUIRED core imgcodecs objdetect videoio)

list(APPEND opencv_ex_face_source
  face.cpp)

# list(APPEND opencv_ex_face_include )

list(APPEND opencv_ex_face_libraries
  ${OpenCV_LIBS})

message(STATUS "  Face Libraries            : ${opencv_ex_face_libraries}")

# if (MSVC)
#   list(APPEND opencv_ex_face_definitions
#     HAVE_M_PI)
# endif (MSVC)

add_executable(${opencv_ex_face_target}
  ${opencv_ex_face_source})

if (opencv_ex_face_definitions)
  target_compile_definitions(${opencv_ex_face_target} PUBLIC
    ${opencv_ex_face_definitions})
endif ()

if (opencv_ex_face_include)
  target_include_directories(${opencv_ex_face_target} PUBLIC
    ${opencv_ex_face_include})
endif ()

target_link_libraries(${opencv_ex_face_target}
  ${opencv_ex_face_libraries})

if(DEPLOY_PDB_FILES)
  install(FILES "$<TARGET_PDB_FILE:${opencv_ex_face_target}>"
    DESTINATION pdb
    COMPONENT pdb)
endif()

install(TARGETS ${opencv_ex_face_target}
  RUNTIME DESTINATION bin)
