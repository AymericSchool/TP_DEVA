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
bool colide (SDL_Rect obj, SDL_Rect* oth, int n)
{
    int i;
    for (i = 0; i < n; i++) {
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
void moving(Player *p, SDL_Rect* obstacles, int n)
{
    SDL_Rect temp;
    temp = p->hitbox;
    // Propulsion
        if (p->estPropulse)
        {
            p->right = 0;
            p->left = 0;
            p->stun = true;
            p->hitbox.y-= JUMP_SPEED / 4;
            p->hitbox.x += (JUMP_SPEED * p->sensPropulsion) / 4;
            if (p->hitbox.x > WIDTH_GAME - p->hitbox.w) p->hitbox.x = WIDTH_GAME - p->hitbox.w;
            p->forcePropulsion--;
            if (p->forcePropulsion == 0) {
                    p->estPropulse = 0;
                    p->stun = false;
            }
        }
    // Saut
    if (p->stun == false && p->shield == false) {
        if (p->up) {
            // Creation d'un double temporaire qui regarde si la position est bien sous collision
            temp.y += p->speed;
            if (colide(temp, obstacles, n)) {
                    // Si le joueur est sur le sol, on update sa hauteur max de saut
                p->h = p->hitbox.y - p->jump;
            }
            if (p->hitbox.y > p->h && p->hitbox.y > 0) {
                // Tant que le joueur est sous sa hauteur max, il monte
                p->hitbox.y-=JUMP_SPEED;
            }
            // Reset sa hauteur max, le joueur est donc sous gravite
            else p->h = HEIGHT_GAME - p->hitbox.h;
        }
        else p->h = HEIGHT_GAME - p->hitbox.h;

        // Gauche
        if (p->left) {
            // Creation d'un double temporaire qui regarde si la position est bien sous collision
            temp.x-=p->speed;

            if (!colide(temp, obstacles, n)) {
                    p->hitbox.x-=p->speed;
                    p->distance_travelled++;
            }
            else if (p->surSol) p->hitbox.y--;
        }
        // Droite
        if (p->right) {
                // Creation d'un double temporaire qui regarde si la position est bien sous collision
            temp.x+=p->speed;
            if (temp.x < WIDTH_GAME - (*p).hitbox.w && !colide(temp, obstacles, n))  {
                    p->hitbox.x+=p->speed;
                    p->distance_travelled++;
            }
            else if (p->surSol) p->hitbox.y--;
        }
        // Chute
        temp.y+=p->speed;
        // Creation d'un double temporaire qui regarde si la position est bien sous collision
        if (!colide(temp, obstacles, n))  p->hitbox.y+=FALL_SPEED;
        if (!(p->surSol)) p->hitbox.y++;
    }

    // Sur sol
    temp.y+=temp.h;
    if (colide(temp, obstacles, n)) p->surSol = true;
    else p->surSol = false;

    // Shield into Stun
    if (p->shield) p->timeShield++;
    else if (!(p->stun)) p->timeShield = 0;
    if (p->timeShield >= TIME_SHIELD || p->stun)
    {
        p->stun = true;
        p->shield = 0;
        p->timeShield++;
    }
    if (p->timeShield >= TIME_SHIELD + 150)
    {
        p->stun = false;
        p->timeShield = 0;
    }
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
    p.smash = 0;
    p.attack = 0; // Si la touche attaque est pressee
    p.jump = 200; // Hauteur du saut
    p.speed = 8 / p.type; // vitesse

    p.hp = 50; // HP
    p.hpMax = 50; // HP MAX
    p.canAttack = 1; // Peux attaquer si =1
    p.bufferSmash = 0; // Quand = BIG_ATTACK, smash
    p.estPropulse = 0; // Boolean qui dit si le joueur est propulse
    p.forcePropulsion = 0; // Si le joueur est propulse, voici la force de propulsion
    p.sensPropulsion = 0; // -1 si gauche, 0 si hauteur, 1 si droite
    p.timeBeforeLittleHit = 0; // Si c'est un bot uniquement
    p.big_hit = 0;
    p.victory = 0;
    p.defeat = 0;
    p.distance_travelled = 0;
    p.life = 5; // Nombre de vie du joueur
    p.surSol = true; // Le joueur est sur le sol ?
    p.shield = false; // De base, le joueur ne shield pas
    p.timeShield = 0; // Buffer time du shield (on peux pas en abuser)
    p.stun = false;
    p.points = 0; // Pour le mode temps

    return p;
}
void hit(Player *p1, Player *p2)
{
    if (colidePlayers(p1, p2))
    {

        if(p1->attack && !p1->shield) {
            if (p2->shield == false)
            {
                p2->hp--;
                p1->bufferSmash++;
            }
            if (p1->hitbox.x > p2->hitbox.x) p2->hitbox.x--;
            else p2->hitbox.x++;

        }
        if(p2->attack && !p2->shield) {
            if (p1->shield == false)
            {
                p1->hp--;
                p2->bufferSmash++;
            }
            if (p1->hitbox.x < p2->hitbox.x) p1->hitbox.x--;
            else p1->hitbox.x++;

        }
        if ((p1->bufferSmash >= BIG_ATTACK) && p1->smash) {
            p1->big_hit++;
            p1->bufferSmash = 0;
            p2->hp-=10;
            p2->estPropulse = 1;
            p2->forcePropulsion = 60 - p2->hp;
            if (p1-> hitbox.x > p2->hitbox.x) p2->sensPropulsion = -1;
            else p2->sensPropulsion = 1;
        }
        if ((p2->bufferSmash >= BIG_ATTACK) && p2->smash) {
            p2->big_hit++;
            p2->bufferSmash = 0;
            p1->hp-=10;
            p1->estPropulse = 1;
            p1->forcePropulsion = 60 - p1->hp;
            if (p1-> hitbox.x > p2->hitbox.x) p1->sensPropulsion = 1;
            else p1->sensPropulsion = -1;
        }
    }
    else
    {
        p1->bufferSmash = 0;
        p2->bufferSmash = 0;
    }
    p1->attack = 0;
    p2->attack = 0;
}



