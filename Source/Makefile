SDL_CFLAGS=`sdl2-config --cflags --libs`

main : main.o plateau.o piece.o screen.o map.o deplacement.o
	gcc -o main main.o plateau.o piece.o screen.o map.o deplacement.o $(SDL_CFLAGS)

main.o : main.c
	gcc -o main.o -c main.c -Wall

plateau.o : plateau.c
	gcc -o plateau.o -c plateau.c -Wall

piece.o : piece.c
	gcc -o piece.o -c piece.c -Wall

screen.o : screen.c
	gcc -o screen.o -c screen.c -Wall $(SDL_CFLAGS)

map.o : map.c
	gcc -o map.o -c map.c -Wall $(SDL_CFLAGS)

deplacement.o : deplacement.c
	gcc -o deplacement.o -c deplacement.c -Wall

clean :
	rm -f *.o

run : 
	./main