#include <SDL/SDL.h>
#include "image.h"
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Surface *LoadImg(char ch[50])
{
	SDL_Surface *img;
	img=IMG_Load(ch);
	if(img==NULL)
	{
		printf("%s faild load",ch);
	}
	return img;
}

void afficher(image p,SDL_Surface *screen)
{
	SDL_BlitSurface(p.img,&p.pos2,screen,&p.pos1);
}

int MouseTest(SDL_Event event ,image P)
{
	if(event.motion.x > P.pos1.x && event.motion.x < P.pos1.x + P.pos1.w && event.motion.y > P.pos1.y && event.motion.y < P.pos1.y + P.pos1.h)
	{return 1;}
	else{return 0;}
}
