cmake_minimum_required(VERSION 3.8.2)

project(SdlTutorialSnake
  VERSION 1.0.0
  DESCRIPTION "SDL2 Snake"
  LANGUAGES C)

find_package(SDL2 COMPONENTS REQUIRED)
find_package(SDL2_ttf COMPONENTS REQUIRED)
find_package(SDL2_image COMPONENTS REQUIRED)
find_package(PNG COMPONENTS REQUIRED)

set(sdl_tutorial_snake_target sdl2snake)

list(APPEND sdl_tutorial_snake_source
  "actor.c"
  "apple_actor.c"
  "background_actor.c")

list(APPEND sdl_tutorial_snake_include
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${SDL_TTF_INCLUDE_DIRS})

list(APPEND sdl_tutorial_snake_libraries
  SDL2_ttf::SDL2_ttf
  SDL2::SDL2-static
  SDL2::SDL2main
  PNG::PNG)

add_executable(${sdl_tutorial_snake_target}
  ${sdl_tutorial_snake_source})

if (gos_experimental_c_sdl_2_definitions)
  target_compile_definitions(${sdl_tutorial_snake_target} PUBLIC
    ${sdl_tutorial_snake_definitions})
endif ()

target_include_directories(${sdl_tutorial_snake_target} PUBLIC
  ${sdl_tutorial_snake_libraries})

target_link_libraries(${sdl_tutorial_snake_target}
  ${sdl_tutorial_snake_libraries})

if(MSVC)
  install(FILES "$<TARGET_PDB_FILE:${sdl_tutorial_snake_target}>"
    DESTINATION pdb
    COMPONENT pdb)
endif(MSVC)

install(TARGETS ${sdl_tutorial_snake_target}
  RUNTIME DESTINATION bin)
