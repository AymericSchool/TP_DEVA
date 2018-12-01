#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "player.h"
#include "obstacles.h"
#include "sprites.h"
#include "ia.h"
#include "stats.h"

// Affichage le fond derriere le perso (optimisation)
void affFond(SDL_Surface* screen, SDL_Surface* fond, SDL_Rect* rect)
{
    SDL_Rect rFond = newRect(rect->x, rect->y, rect->h, rect->w);
    rFond.h += 30;
    rFond.w += 30;
    rFond.x -= 15;
    rFond.y -= 15;
    SDL_BlitSurface(fond, &rFond, screen, &rFond);
}
