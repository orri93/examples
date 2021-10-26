cmake_minimum_required(VERSION 3.8.2)

project(SerialWin
  VERSION 1.0.0
  DESCRIPTION "Windows Serial Example"
  LANGUAGES C)

set(serial_win_target serialwin)

list(APPEND serial_win_source
  example.c
  serial.c
  jrk.c)

list(APPEND serial_win_include
  ${CMAKE_SOURCE_DIR})

add_executable(${serial_win_target}
  ${serial_win_source})

target_include_directories(${serial_win_target} PUBLIC
  ${serial_win_include})

install(TARGETS ${serial_win_target}
  RUNTIME DESTINATION bin)
