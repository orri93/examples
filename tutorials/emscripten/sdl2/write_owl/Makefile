CC = emcc
all: write_owl.c
	$(CC) write_owl.c -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file assets -o write_owl.html

