#ifndef TEXT_H
#define TEXT_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
	SDL_Rect pos;
	TTF_Font *font;
	SDL_Surface *surtext;
	SDL_Color TColor;
	char text[50];
}text;

void displayText(text t,SDL_Surface *screen);

#endif
