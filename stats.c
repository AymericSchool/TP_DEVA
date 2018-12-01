#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "player.h"

// Sauvegarde les stats d'un perso
void saveStats(Player p)
{
    FILE *f = NULL;
    char nameFile[32];
    sprintf(nameFile, "res/stat_%d.txt", p.num);
    f = fopen(nameFile, "w");
    fprintf(f, "%d/%d/%d/%d", p.big_hit, p.victory, p.defeat, p.distance_travelled);
    fclose(f);
}

// Charge les stats d'un perso
void loadStats(Player *p)
{
    FILE *f = NULL;
    char nameFile[32];
    sprintf(nameFile, "res/stat_%d.txt", p->num);
    f = fopen(nameFile, "r");
    fscanf(f, "%d/%d/%d/%d", &p->big_hit, &p->victory, &p->defeat, &p->distance_travelled);
    fclose(f);
}

// Reset les stats d'un perso
void resetStats(Player *p)
{
    p->distance_travelled = 0;
    p->defeat = 0;
    p->victory = 0;
    p->big_hit = 0;
}
