all:
	gcc -std=c99 main.c -Isrc/include -Lsrc/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main