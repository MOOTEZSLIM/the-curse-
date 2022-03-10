Game:menu.o
	gcc menu.o image.o text.o -o Game -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
menu.o:menu.c
	gcc -c menu.c -g
image.o:image.c
	gcc -c image.c -g
text.o:text.c
	gcc -c text.c -g
