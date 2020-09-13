# Places a static or shared (dynamic) library into ../../lib

all: static

dynamic:
	gcc -I../../include -fPIC -c forgo.c
	gcc -shared -o libgosforgo.so forgo.o
	mv -f libgosforgo.so ../../lib
	rm -f forgo.o

static:
	gcc -I../../include -c forgo.c
	ar rc libgosforgo.a forgo.o
	ranlib libgosforgo.a
	mv -f libgosforgo.a ../../lib
	rm -f forgo.o
