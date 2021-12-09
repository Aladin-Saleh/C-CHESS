SDL_CFLAGS=`sdl2-config --cflags --libs`

main : main.o plateau.o piece.o screen.o map.o deplacement.o manger.o mat.o promotion.o
	gcc -o main main.o plateau.o piece.o screen.o map.o deplacement.o manger.o mat.o promotion.o $(SDL_CFLAGS)

main.o : main.c
	gcc -o main.o -c main.c 

plateau.o : plateau.c
	gcc -o plateau.o -c plateau.c 

piece.o : piece.c
	gcc -o piece.o -c piece.c 

screen.o : screen.c
	gcc -o screen.o -c screen.c  $(SDL_CFLAGS)

map.o : map.c
	gcc -o map.o -c map.c  $(SDL_CFLAGS)

deplacement.o : deplacement.c
	gcc -o deplacement.o -c deplacement.c 
	
manger.o : manger.c
	gcc -o manger.o -c manger.c

mat.o : mat.c
	gcc -o mat.o -c mat.c

promotion.o : promotion.c
	gcc -o promotion.o -c promotion.c

clean :
	rm -f *.o

run : 
	./main