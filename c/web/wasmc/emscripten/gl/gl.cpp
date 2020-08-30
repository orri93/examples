/*
 *
 * Compile for emscripten using
 * emcc -Iinclude SingleFileOpenGLTex.cpp \
 *             -O2 -std=c++14 -s TOTAL_MEMORY=33554432 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file examples/data -s USE_SDL=2 -o html/SingleFileOpenGLTex.html
 * where the following images must be located in a subfolder
 *   - examples/data/test.png
 *   - examples/data/cartman.png
 *   - examples/data/cube-negx.png
 *   - examples/data/cube-negz.png
 *
 * Tested against emscripten/1.37.14
 * 
 */

#include "SDL.h"
#include <SDL_image.h>
#ifdef EMSCRIPTEN
#   include <GLES2/gl2.h>
#   include "emscripten.h"
#else
 // OSX only - change on other platforms
#   include <OpenGL/gl3.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
