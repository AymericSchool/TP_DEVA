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
#include "stats.h"

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
    // Propulsion
        if (p->estPropulse)
        {
            p->right = 0;
            p->left = 0;
            p->hitbox.y-= JUMP_SPEED;
            p->hitbox.x += 2*p->speed * p->sensPropulsion;
            if (p->hitbox.x > WIDTH_GAME - p->hitbox.w) p->hitbox.x = WIDTH_GAME - p->hitbox.w;
            p->forcePropulsion--;
            if (p->forcePropulsion == 0) p->estPropulse = 0;
        }
    // Saut
    if (p->up) {
        temp.y += p->speed;
        if (colide(temp, obstacles)) {
            p->h = p->hitbox.y - p->jump;
        }
        if (p->hitbox.y > p->h) {
            p->hitbox.y-=JUMP_SPEED;
        }
        else p->h = HEIGHT_GAME - p->hitbox.h;
    }
    else p->h = HEIGHT_GAME - p->hitbox.h;
    // Gauche
    if (p->left) {
        temp.x-=p->speed;
        if (!colide(temp, obstacles)) {
                p->hitbox.x-=p->speed;
                p->distance_travelled++;
        }
    }
    // Droite
    if (p->right) {
        temp.x+=p->speed;
        if (temp.x < WIDTH_GAME - (*p).hitbox.w && !colide(temp, obstacles))  {
                p->hitbox.x+=p->speed;
                p->distance_travelled++;
        }
    }
    // Chute
    temp.y+=p->speed;
    if (!colide(temp, obstacles))  p->hitbox.y+=FALL_SPEED;
}
// Initialise un player
Player newPlayer(int num, SDL_Surface *surface, SDL_Rect hitbox, int type)
{
    Player p; // Creation du player
    p.surface = surface; // Surface
    p.icone = NULL;
    p.hitbox = hitbox; // Hitbox
    p.num = num;
    p.type = type; // Type du player (IA ou Humain)
    p.up = 0; // Si la touche Up est pressee
    p.left = 0; // Si la touche left est pressee
    p.right = 0; // Si la touche right est pressee
    p.attack = 0; // Si la touche attaque est pressee
    p.jump = 250; // Hauteur du saut
    p.speed = 7; // vitesse
    p.hp = 50; // HP
    p.hpMax = 50; // HP MAX
    p.canAttack = 1; // Peux attaquer si =1
    p.buffer = 0; // Quand =1000, grosse attaque
    p.estPropulse = 0; // Boolean qui dit si le joueur est propulse
    p.forcePropulsion = 0; // Si le joueur est propulse, voici la force de propulsion
    p.sensPropulsion = 0; // -1 si gauche, 0 si hauteur, 1 si droite
    p.timeBeforeLittleHit = 0; // Si c'est un bot uniquement
    p.big_hit = 0;
    p.victory = 0;
    p.defeat = 0;
    p.distance_travelled = 0;
    return p;
}
void hit(Player *p1, Player *p2)
{
    if (colidePlayers(p1, p2))
    {
        if(p1->attack) {
            p2->hp--;
            if (p1->hitbox.x > p2->hitbox.x) p2->hitbox.x--;
            else p2->hitbox.x++;
        }
        if(p2->attack) {
            p1->hp--;
            if (p1->hitbox.x < p2->hitbox.x) p1->hitbox.x--;
            else p1->hitbox.x++;
        }
        if (p1->buffer == BIG_ATTACK) {
            p1->big_hit++;
            p1->buffer = 0;
            p2->hp-=10;
            p2->estPropulse = 1;
            p2->forcePropulsion = p2->hpMax - p2->hp;
            if (p1-> hitbox.x > p2->hitbox.x) p2->sensPropulsion = -1;
            else p2->sensPropulsion = 1;
        }
        if (p2->buffer == BIG_ATTACK) {
            p2->big_hit++;
            p2->buffer = 0;
            p1->hp-=10;
            p1->estPropulse = 1;
            p1->forcePropulsion = p1->hpMax - p1->hp;
            if (p1-> hitbox.x > p2->hitbox.x) p1->sensPropulsion = 1;
            else p1->sensPropulsion = -1;
        }
    }
    p1->attack = 0;
    p2->attack = 0;
}



