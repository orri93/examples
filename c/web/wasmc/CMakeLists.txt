cmake_minimum_required(VERSION 3.0.0)
project(examples-c-web-wasmc VERSION 0.1.0)

set(gos_examples_c_web_wasmc_target ecwasmc)

find_path(gos_emscripten_include_dir NAMES emscripten.h wasm_simd128.h
  HINTS "$ENV{EMSDK}/upstream/emscripten/system/include"
  DOC "emscripten include directory containing the emscripten header file"
  REQUIRED)

message(STATUS "Emscripten include directory: ${gos_emscripten_include_dir}")

add_library(${gos_examples_c_web_wasmc_target} fib.c "emscripten/sdl/hello_world_sdl.c" "emscripten/gl/gl.cpp")

target_include_directories(${gos_examples_c_web_wasmc_target} PUBLIC
  ${gos_emscripten_include_dir})

