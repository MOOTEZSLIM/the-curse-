#ifndef IMAGE_H
#define IMAGE_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
typedef struct
{
	SDL_Rect pos1;
	SDL_Rect pos2;
	SDL_Surface *img;
}image;
void afficher(image p,SDL_Surface *screen);
SDL_Surface *LoadImg(char ch[50]);
int MouseTest(SDL_Event event ,image P);

#endif
