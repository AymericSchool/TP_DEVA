#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>


#include "player.h"
#include "time.h"

void move_ia(Player *p1, Player *p2, int niveauBot) {

    if (p2->type == 2)
    {
        p2->left = 0;
        p2->right = 0;
        p2->up = 0;

        if (p2->hitbox.x > p1->hitbox.x + 20)
        {
            p2->left = 1;
        }
        else if (p2->hitbox.x < p1->hitbox.x - 20)
        {
            p2->right = 1;
        }

        if (colidePlayers(p1, p2))
        {
            p2->timeBeforeLittleHit++;
            p2->attack = 0;
            if (p2->timeBeforeLittleHit > TIME_BEFORE_LITTLE_HIT) {
                p2->timeBeforeLittleHit = 0;
                p2->attack = 1;
            }
        }

        if (p2->hitbox.y > p1->hitbox.y + 5) {
            p2->up = 1;
        }

        if (colidePlayers(p1,p2) && p2->bufferSmash == BIG_ATTACK) {
            p2->big_hit++;
            p2->bufferSmash = 0;
            p1->hp-=10;
            p1->estPropulse = 1;
            p1->forcePropulsion = p1->hpMax - p1->hp;
            if (p1-> hitbox.x > p2->hitbox.x) p1->sensPropulsion = 1;
            else p1->sensPropulsion = -1;
        }

        // Niveau 2
        if (niveauBot == 2)
        {
            // Plus rapide
            p2->speed = 5;
            if (colidePlayers(p1, p2)) {
                    // Chance de frapper davantages
                    p2->timeBeforeLittleHit+= 1 - rand()%3;
                    // Chance de shield
                    if (rand()%193 == 0) p2->shield = 1;
            }

            if (p2->timeShield > 100) p2->shield = 0;
        }
    }
}
