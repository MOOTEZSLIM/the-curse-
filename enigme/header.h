#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

typedef struct enigme
{
    char Question1[100], Answer1[100], Answer2[100] , Answer3[100],
correct[100];
SDL_Surface *Question,*Reponse1,*Reponse2,*Reponse3;
    SDL_Rect Question1Pos, Answer1Pos, Answer2Pos, Answer3Pos ;
    TTF_Font *Font;
    int InputUser, solution;
} enigme;

void Init_Enigme(enigme *e,char *nomfichier);
void animer_Enigme(enigme *e);
void sauvegarder (SDL_Surface * ecran,enigme e,int x);
void afficher_Enigme(personne p ,background b,char *nomfichier);
int charger(personne p ,background b,char *nomfichier);






#endif
 // HEADER_H_INCLUDED
