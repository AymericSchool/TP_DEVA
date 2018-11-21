/*
player.c
fonctions relatives a la physique du perso, collisions, sauts et deplacements
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "player.h"
#include "constantes.h"

int h;

// Retourne true si obj est en collision avec un rect de oth
bool colide (SDL_Rect obj, SDL_Rect* oth)
{
    int i;
    for (i = 0; i < 10; i++) {
        // Coin superieur gauche
        if (((oth[i].x <= obj.x) && (obj.x <= oth[i].x + oth[i].w)) && ((oth[i].y <= obj.y) && (obj.y <= oth[i].y + oth[i].h))) return true;
        // Coin inferieur gauche
        if (((oth[i].x <= obj.x) && (obj.x <= oth[i].x + oth[i].w)) && ((oth[i].y <= obj.y + obj.h) && (obj.y + obj.h <= oth[i].y + oth[i].h))) return true;
        // Coin superieur droit
        if (((oth[i].x <= obj.x + obj.w) && (obj.x + obj.w <= oth[i].x + oth[i].w)) && ((oth[i].y <= obj.y) && (obj.y <= oth[i].y + oth[i].h))) return true;
        // Coin inferieur droit
        if (((oth[i].x <= obj.x + obj.w) && (obj.x + obj.w <= oth[i].x + oth[i].w)) && ((oth[i].y <= obj.y + obj.h) && (obj.y + obj.h <= oth[i].y + oth[i].h))) return true;
    }
    // Sinon
    return false;
}

bool colidePlayers (Player *p1, Player *p2)
{
    // Coin superieur gauche
    if (((p1->hitbox.x <= p2->hitbox.x) && (p2->hitbox.x <= p1->hitbox.x + p1->hitbox.w)) && ((p1->hitbox.y <= p2->hitbox.y) && (p2->hitbox.y <= p1->hitbox.y + p1->hitbox.h))) return true;
    // Coin inferieur gauche
    if (((p1->hitbox.x <= p2->hitbox.x) && (p2->hitbox.x <= p1->hitbox.x + p1->hitbox.w)) && ((p1->hitbox.y <= p2->hitbox.y + p2->hitbox.h) && (p2->hitbox.y + p2->hitbox.h <= p1->hitbox.y + p1->hitbox.h))) return true;
    // Coin superieur droit
    if (((p1->hitbox.x <= p2->hitbox.x + p2->hitbox.w) && (p2->hitbox.x + p2->hitbox.w <= p1->hitbox.x + p1->hitbox.w)) && ((p1->hitbox.y <= p2->hitbox.y) && (p2->hitbox.y <= p1->hitbox.y + p1->hitbox.h))) return true;
    // Coin inferieur droit
    if (((p1->hitbox.x <= p2->hitbox.x + p2->hitbox.w) && (p2->hitbox.x + p2->hitbox.w <= p1->hitbox.x + p1->hitbox.w)) && ((p1->hitbox.y <= p2->hitbox.y + p2->hitbox.h) && (p2->hitbox.y + p2->hitbox.h <= p1->hitbox.y + p1->hitbox.h))) return true;
    return false;
}

// Deplace p, selon la direction et les obstacles (pour les collisions)
void moving(Player *p, SDL_Rect* obstacles)
{
    SDL_Rect temp;
    temp = p->hitbox;
    // Saut
    if (p->up) {
        temp.y += p->speed;
        if (colide(temp, obstacles)) {
            p->h = p->hitbox.y - p->jump;
        }
        if (p->hitbox.y > p->h) {
            p->hitbox.y-=p->speed*2;
        }
        else p->h = HEIGHT_GAME - p->hitbox.h;
    }
    else p->h = HEIGHT_GAME - p->hitbox.h;
    // Gauche
    if (p->left) {
        temp.x-=p->speed;
        if (!colide(temp, obstacles)) p->hitbox.x-=p->speed;
    }
    // Droite
    if (p->right) {
        temp.x+=p->speed;
        if (temp.x < WIDTH_GAME - (*p).hitbox.w && !colide(temp, obstacles))  p->hitbox.x+=p->speed;
    }
    // Chute
    temp.y+=p->speed;
    if (!colide(temp, obstacles))  p->hitbox.y+=p->speed;
}

// Initialise un player
Player newPlayer(SDL_Surface *surface, SDL_Rect hitbox, char* type)
{
    Player p;
    p.surface = surface;
    p.hitbox = hitbox;
    p.type = type;
    p.up = 0;
    p.left = 0;
    p.right = 0;
    p.attack = 0;
    p.jump = 250;
    p.speed = 7;
    return p;
}

void hit(Player *p1, Player *p2)
{
    if (colidePlayers(p1, p2))
    {
        if(p1->attack) p2->hitbox.y = 0;
        if(p2->attack) p1->hitbox.y = 0;
    }
}



