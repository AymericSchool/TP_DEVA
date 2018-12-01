/*
narrow.c
principe du retricissement de la map
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "player.h"
#include "obstacles.h"
#include "constantes.h"
#include "narrow.h"

/*
PRINCIPE
En deux temps :
    Affichage
Regarde la pos x du rect renvoyé, et créé x lignes de tous les cotés
    Fonctionnement
Si le joueur n'est pas en collision totale avec le rect renvoyé, il meurt
*/

// Prend en parametre la zone viable.
// arg : 0 si on reset
// arg : 1 si on augmente la zone
// arg : -1 si on retrecie la zone
void updateNarrow(SDL_Rect *zone, int arg)
{
    switch(arg)
    {
    case -1:
        zone->x++;
        zone->y++;
        zone->h-=2;
        zone->w-=2;
        break;
    case 0:
        zone->x = 0;
        zone->y = 0;
        zone->h = HEIGHT_GAME;
        zone->w = WIDTH_GAME;
        break;
    case 1:
        zone->x--;
        zone->y--;
        zone->h+=2;
        zone->w+=2;
        break;
    default:
        break;
    }
}

// Affiche les lignes
void displayNarrow(SDL_Surface *screen, SDL_Rect *zone)
{
    // Creation des surfaces
    SDL_Surface *ligne = NULL, *colonne = NULL;
    SDL_Rect position;
    // Ligne
    ligne = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH_GAME, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(ligne, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    // Colonne
    colonne = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, HEIGHT_GAME, 32, 0, 0, 0, 0);
    SDL_FillRect(colonne, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    int i;

    for (i = 0; i < zone->x; i++)
    {
        // Affichage des lignes (haut)
        position.x = 0;
        position.y = i;
        SDL_BlitSurface(ligne, NULL, screen, &position);

        // Affichage des lignes (bas)
        position.x = 0;
        position.y = HEIGHT_GAME - i;
        SDL_BlitSurface(ligne, NULL, screen, &position);

        // Affichage des lignes (gauche)
        position.x = i;
        position.y = 0;
        SDL_BlitSurface(colonne, NULL, screen, &position);

        // Affichage des lignes (droite)
        position.x = WIDTH_GAME - i;
        position.y = 0;
        SDL_BlitSurface(colonne, NULL, screen, &position);
    }

    SDL_Flip(screen);
    SDL_FreeSurface(ligne);
    SDL_FreeSurface(colonne);
}

// Regarde s'il faut tuer le perso
bool deadlyNarrow(Player *p, SDL_Rect *zone)
{
    int i = 0;
    // Coin superieur gauche
    if (p->hitbox.x > zone->x && zone->x + zone->w > p->hitbox.x && p->hitbox.y > zone->y && zone->y + zone->h > p->hitbox.y) i++;
    // Coin superieur droit
    if (p->hitbox.x + p->hitbox.w > zone->x && zone->x + zone->w > p->hitbox.x + p->hitbox.w && p->hitbox.y > zone->y && zone->y + zone->h > p->hitbox.y + p->hitbox.h) i++;
    // Coin inferieur gauche
    if (p->hitbox.x > zone->x && zone->x + zone->w > p->hitbox.x && p->hitbox.y + p->hitbox.h > zone->y && zone->y + zone->h > p->hitbox.y + p->hitbox.h) i++;
    // Coin inferieur droit
    if (p->hitbox.x + p->hitbox.w > zone->x && zone->x + zone->w > p->hitbox.x + p->hitbox.w && p->hitbox.y + p->hitbox.h > zone->y && zone->y + zone->h > p->hitbox.y + p->hitbox.h) i++;

    if (i == 4) return false;
    else return true;
}

