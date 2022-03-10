#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "text.h"

void displayText(text t,SDL_Surface *screen)
{
	t.surtext=TTF_RenderText_Solid(t.font,t.text,t.TColor);
	SDL_BlitSurface(t.surtext,NULL,screen,&t.pos);
}
