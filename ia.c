#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "player.h"
#include "constantes.h"

void move_ia(Player *p1, Player *p2) {

    if (p1->type == 2) // si c'est un bot
    {
        p1->left = 0; // remet tout a zero
        p1->right = 0;
        p1->up = 0;

        if (p1->hitbox.x > p2->hitbox.x) // si p1 est devant p2
        {
            p1->left = 1;
            p1->right = 0;
        }
        else if (p1->hitbox.x < p2->hitbox.x) // si il est derriere
        {
            p1->right = 1;
            p1->left = 0;
        }

        if (colidePlayers(p1, p2)) // si ils sont en collisions
        {
            p2->timeBeforeLittleHit++;
            p2->attack = 0;
            if (p2->timeBeforeLittleHit == TIME_BEFORE_LITTLE_HIT) {
                p2->timeBeforeLittleHit = 0;
                p2->attack = 1;
            }
        }

        if (p2->hitbox.y > p1->hitbox.y) {
            p2->up = 1;
        }
    }

    if (p2->type == 2) // symetrique
    {
        p2->left = 0;
        p2->right = 0;
        p2->up = 0;

        if (p2->hitbox.x > p1->hitbox.x)
        {
            p2->left = 1;
        }
        else if (p2->hitbox.x < p1->hitbox.x)
        {
            p2->right = 1;
        }

        if (colidePlayers(p1, p2))
        {
            p2->timeBeforeLittleHit++;
            p2->attack = 0;
            if (p2->timeBeforeLittleHit == TIME_BEFORE_LITTLE_HIT) {
                p2->timeBeforeLittleHit = 0;
                p2->attack = 1;
            }
        }
        if (p2->hitbox.y > p1->hitbox.y) {
            p2->up = 1;
        }
    }
}
