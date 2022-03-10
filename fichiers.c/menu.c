#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "text.h"
#include <SDL/SDL_mixer.h>

int main()
{
	//initialization SDL 
	TTF_Init();
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
	{
		printf("Erreur : %s \n",SDL_GetError());
	}
	
	//variables
	SDL_Surface *screen;
	image BG[3],BTplay[3],BToption[3],BTexit[3],BTreturn[3],BTfscreen[3],BTplus[3],BTminus[3],BTback[3];
	int scloop,iBG,iplay,ioption,iexit,bss,key,ireturn,ifscreen,iplus,iminus,iback,fullscreen,sound;
	text p;
	SDL_Event event;
	unsigned int timer=0;
	
	//main work
	//creation of a window
	screen=SDL_SetVideoMode(1600,839,32,SDL_HWSURFACE || SDL_DOUBLEBUF );
	if(screen==NULL)
	{
		printf("window creation faild :) 1600*839 :) \n");
	}
	
	//powred by :
	p.pos.x=1150;
	p.pos.y=760;
	p.TColor.r=255;
	p.TColor.g=255;
	p.TColor.b=255;
	p.font=NULL;
	p.font=TTF_OpenFont("texture/wheaton capitals.ttf",20);
	if(p.font==NULL)
	{
		printf("font title load failed ");
	}
	strcpy(p.text,"Powered by TEAM LEGENDARYMENOTA");
	/*if(p.surtext==NULL)
	{
		printf("render title failed\n");
	}*/
	
	//music load !!!
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
	{
		printf("%s",Mix_GetError());
	}
	Mix_Music *music;
	Mix_Chunk *BTsound;
	Uint8 volume1 = 0;
	Uint8 volume2 = 32;
	Uint8 volume3 = 128;
    
	music=Mix_LoadMUS("Music/BGmusic2.mp3");
	BTsound=Mix_LoadWAV("Music/press.wav");
	Mix_PlayMusic(music,-1);
	
	//loading and positioning images
	BG[0].img=LoadImg("images/Background1.jpg");
	BG[0].pos1.x=0;
	BG[0].pos1.y=0;
	BG[0].pos1.w=1600;
	BG[0].pos1.h=839;
	BG[0].pos2.x=0;
	BG[0].pos2.y=0;
	BG[0].pos2.w=1600;
	BG[0].pos2.h=839;
	
	BG[1].img=LoadImg("images/hg.jpg");
	BG[1].pos1=BG[0].pos1;
	BG[1].pos2=BG[0].pos1;
	
	BG[2].img=LoadImg("images/Background2.jpg");
	BG[2].pos1=BG[0].pos1;
	BG[2].pos2=BG[0].pos2;
	
	BTplay[0].img=LoadImg("images/Play1.png");
	BTplay[0].pos1.x=100;
	BTplay[0].pos1.y=400;
	BTplay[0].pos1.w=353;
	BTplay[0].pos1.h=85;
	
	BTplay[1].img=LoadImg("images/Play2.png");
	BTplay[1].pos1=BTplay[0].pos1;
	
	BTplay[2].img=LoadImg("images/Play1.png");
	BTplay[2].pos1=BTplay[0].pos1;
	
	BToption[0].img=LoadImg("images/Option1.png");
	BToption[0].pos1=BTplay[0].pos1;
	BToption[0].pos1.y=550;
	
	BToption[1].img=LoadImg("images/Option2.png");
	BToption[1].pos1=BToption[0].pos1;
	
	BToption[2].img=LoadImg("images/Option1.png");
	BToption[2].pos1=BToption[0].pos1;
	
	BTexit[0].img=LoadImg("images/Exit1.png");
	BTexit[0].pos1=BTplay[0].pos1;
	BTexit[0].pos1.y=700;
	
	BTexit[1].img=LoadImg("images/Exit2.png");
	BTexit[1].pos1=BTexit[0].pos1;
	
	BTexit[2].img=LoadImg("images/Exit1.png");
	BTexit[2].pos1=BTexit[0].pos1;
	
	BTreturn[0].img=LoadImg("images/back1.png");
	BTreturn[0].pos1.x=0;
	BTreturn[0].pos1.y=0;
	BTreturn[0].pos1.w=91;
	BTreturn[0].pos1.h=87;
	
	BTreturn[1].img=LoadImg("images/back1.png");
	BTreturn[1].pos1=BTreturn[0].pos1;
	
	BTreturn[2].img=LoadImg("images/back2.png");
	BTreturn[2].pos1=BTreturn[0].pos1;
	
	BTplus[0].img=LoadImg("images/plus1.png");
	BTplus[0].pos1.x=578;
	BTplus[0].pos1.y=316;
	BTplus[0].pos1.w=54;
	BTplus[0].pos1.h=49;
	
	BTplus[1].img=LoadImg("images/plus1.png");
	BTplus[1].pos1=BTplus[0].pos1;
	
	BTplus[2].img=LoadImg("images/plus2.png");
	BTplus[2].pos1=BTplus[0].pos1;
	
	BTminus[0].img=LoadImg("images/minus1.png");
	BTminus[0].pos1=BTplus[0].pos1;
	BTminus[0].pos1.x=928;
	
	BTminus[1].img=LoadImg("images/minus1.png");
	BTminus[1].pos1=BTminus[0].pos1;
	
	BTminus[2].img=LoadImg("images/minus2.png");
	BTminus[2].pos1=BTminus[0].pos1;
	
	BTfscreen[0].img=LoadImg("images/fullscreen1.png");
	BTfscreen[0].pos1.w=219;
	BTfscreen[0].pos1.h=60;
	BTfscreen[0].pos1.x=700;
	BTfscreen[0].pos1.y=552;
	
	BTfscreen[1].img=LoadImg("images/fullscreen1.png");
	BTfscreen[1].pos1=BTfscreen[0].pos1;
	
	BTfscreen[2].img=LoadImg("images/fullscreen2.png");
	BTfscreen[2].pos1=BTfscreen[0].pos1;
	//screen loop :)
	iplay=0;
	ioption=0;
	iexit=0;
	scloop=1;
	iBG=0;
	bss=-1;
	ireturn=0;
	iplus=0;
	iminus=0;
	iback=0;
	ifscreen=0;
	fullscreen=0;
	sound=3;
	printf("i'm ready\n");
	do
	{
		timer=SDL_GetTicks()/1000;
		if(iBG==0)
		{
			//printf("i'm in BG --> %d\n",iBG);
			displayText(p,BG[0].img);
			SDL_Flip(screen);
			afficher(BTplay[iplay],BG[0].img);
			afficher(BToption[ioption],BG[0].img);
			afficher(BTexit[iexit],BG[0].img);
			//BG[0].pos1.x=0;
			//BG[0].pos1.y=0;
			if(bss==0)
			{
				ioption=0;
				iexit=0;
			}
			else if(bss==1)
			{
				iplay=0;
				iexit=0;
			}
			else if(bss==2)
			{
				iplay=0;
				ioption=0;
			}
			else if(key==0)
			{	
				iplay=0;
				ioption=0;
				iexit=0;
			}
		}
		if(iBG==2)
		{
			afficher(BTplus[iplus],BG[2].img);
			afficher(BTreturn[ireturn],BG[2].img);
			afficher(BTminus[iminus],BG[2].img);
			afficher(BTfscreen[ifscreen],BG[2].img);
			SDL_Flip(screen);
		}
		SDL_BlitSurface(BG[iBG].img,&BG[iBG].pos2,screen,&BG[iBG].pos1);
		SDL_Flip(screen);
		SDL_Flip(BG[iBG].img);
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					scloop=0;
					break;
				case SDL_KEYDOWN:
				{	
					Mix_PlayChannel(2, BTsound, 0);
					if(iBG==0)
					{
						if(event.key.keysym.sym == SDLK_ESCAPE)
						{	
							iexit=2;
							key=1;
						}
						else if(event.key.keysym.sym==SDLK_p)
						{
							iplay=2;
							key=1;
						}
						else if(event.key.keysym.sym==SDLK_s)
						{
							ioption=2;
							key=1;
						}
						else if(event.key.keysym.sym==SDLK_RETURN)
						{
							if(bss==0)
							{
								iplay=2;
							}
							else if(bss==1)
							{
								ioption=2;
							}
							else if(bss==2)
							{
								iexit=2;
							}
						}
					}
					else if(iBG==2)
					{
						if(event.key.keysym.sym==SDLK_ESCAPE)
						{
							ireturn=2;
						}
						else if(event.key.keysym.sym==SDLK_PLUS)
						{
							iplus=2;
						}
						else if(event.key.keysym.sym==SDLK_MINUS)
						{
							iminus=2;
						}
						else if (event.key.keysym.sym==SDLK_f)
						{
							ifscreen=2;
						}
					}
					
				}
				break;
				
				case SDL_KEYUP:
					if(iBG==0)
					{
						if(event.key.keysym.sym==SDLK_p)
						{
							iBG=1;
							Mix_PlayChannel(2,BTsound, 0);
						}
						else if(event.key.keysym.sym==SDLK_DOWN)
						{
							bss++;
							if(bss>2){bss=0;}
							iplay=1;
							ioption=1;
							iexit=1;
						}
						else if(event.key.keysym.sym==SDLK_UP)
						{
							bss--;
							if(bss<0){bss=2;}
							iplay=1;
							ioption=1;
							iexit=1;
						}
						
						else if(event.key.keysym.sym==SDLK_s)
						{
							iBG=2;
						}
						else if(event.key.keysym.sym == SDLK_ESCAPE)
						{
								scloop=0;
									
						}
						else if(event.key.keysym.sym==SDLK_RETURN)
						{
							if(bss==0)
							{
								iBG=1;
								bss=-1;
							}
							else if(bss==1)
							{
								iBG=2;
								bss=-1;
							}
							else if(bss==2)
							{
								scloop=0;
							}
						}
					}
					else if (iBG==2)
					{
						if(event.key.keysym.sym==SDLK_ESCAPE)
						{
							iBG=0;
							ioption=0;
						}
					}
				break;
				case SDL_MOUSEMOTION:
					if(iBG==0){
						if(MouseTest(event,BTplay[0]))
						{
								bss=0;
								iplay=1;
						}
						else if(MouseTest(event,BToption[0]))
						{
								bss=1;
								ioption=1;
						}
						else if(MouseTest(event,BTexit[0]))
						{
								bss=2;
								iexit=1;
						}
						else
						{
							bss=-1;
						}
					}
					else if(iBG==2)
					{
						//printf("x-->%d/y-->%d\n",event.motion.x,event.motion.y);
						if(MouseTest(event,BTreturn[0]))
						{
							ireturn=1;
						}
						else if(MouseTest(event,BTplus[0]))
						{
							iplus=1;
						}
						else if(MouseTest(event,BTminus[0]))
						{
							iminus=1;
						}
						else if(MouseTest(event,BTfscreen[0]))
						{
							ifscreen=1;
						}
					}
				break;
				case SDL_MOUSEBUTTONDOWN:
					Mix_PlayChannel(2, BTsound, 0);
					if(iBG==0)
					{
						if(bss==0)
						{
								iplay=2;
						}
						else if(bss==1)
						{
								ioption=2;
						}
						else if(bss==2)
						{
								bss=2;
						}
					}
					else if(iBG==2)
					{
						if(MouseTest(event,BTreturn[0]))
						{
							ireturn=2;
						}
						else if(MouseTest(event,BTplus[0]))
						{
							iplus=2;
							if(sound<4)
							{
								sound++;
								printf("sound higher\n");
								printf("sound ==> %d\n",sound);
								if(sound==3)
									Mix_VolumeMusic(volume3);
								else if(sound==2)
									Mix_VolumeMusic(volume2);
								else
									printf("you reach the maximum\n");
							}							
						}
						else if(MouseTest(event,BTminus[0]))
						{
							iminus=2;
							if(sound>0)
							{
								sound--;
								printf("sound lower\n");
								printf("sound ==> %d\n",sound);
								if(sound==1)
									Mix_VolumeMusic(volume1);
								else if(sound==2)
									Mix_VolumeMusic(volume2);
								else
									printf("you reach the minimum\n");
							}
						}
						
						else if(MouseTest(event,BTfscreen[0]))
						{
							ifscreen=2;
							if(fullscreen==0)
							{
								fullscreen=1;
								screen=SDL_SetVideoMode(1600,839,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
							}
								
							else
							{
								fullscreen=0;
								screen=SDL_SetVideoMode(1600,839,32,SDL_HWSURFACE || SDL_DOUBLEBUF );
							}
								
							printf("fullscreen ==> %d\n",fullscreen);
						}
						
					}
				break;
				case SDL_MOUSEBUTTONUP:
					if(iBG==0){
						if(bss==0)
						{
							iBG=1;
							bss=-1;
						}
						else if(bss==1)
						{
							iBG=2;
							bss=-1;
						}
						else if(bss==2)
						{
							scloop=0;
						}
					}
					else if(iBG==2)
					{
						if(MouseTest(event,BTreturn[0]))
						{
							iBG=0;
							ioption=0;
						}	
						else if(MouseTest(event,BTplus[0]))
						{
							iplus=0;
							printf("sound --> %d\n",sound);
							if(sound>=3)
							{
								sound=3;
								printf("sound ==>max\n");
							}
							// else
							// 	printf("sound = %d\n",sound);
						}
						else if(MouseTest(event,BTminus[0]))
						{
							iminus=0;
							printf("sound --> %d\n",sound);
							if(sound <=1)
							{
								sound=1;
								printf("sound ==>min\n");

							}
							// else
							// 	printf("sound = %d\n",sound);
						}
						else if(MouseTest(event,BTfscreen[0]))
						{
							ifscreen=0;
							printf("fullscreen-->%d\n",fullscreen);
							printf("background-->%d\n",iBG);
							if(fullscreen==0)
								printf("fullscreen mode desactivate \n");
							else
								printf("fullscreen mode activate \n");
						}
					}
				break;
			}
		}
	}while(scloop!=0);
	printf("time : %d s\n",timer);
	
	Mix_FreeMusic(music);
	TTF_CloseFont(p.font);
	
	
	Mix_CloseAudio();
	SDL_FreeSurface(screen);
	for (iBG=0;iBG<3;iBG++)
	{
		SDL_FreeSurface(BG[iBG].img);
	}
	SDL_Flip(screen);
	Mix_FreeChunk (BTsound);
	SDL_Quit();
	return 0;
