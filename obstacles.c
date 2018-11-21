/*
obstacles.c
fonction qui ajoute un nouvel obstacle
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "obstacles.h"


SDL_Rect newRect(int x, int y, int h, int w) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.h = h;
    r.w = w;
    return r;
}



