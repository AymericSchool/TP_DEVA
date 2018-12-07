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
#include "constantes.h"
#include "sprites.h"

// Fonction qui créé un rect rapidement
SDL_Rect newRect(int x, int y, int h, int w) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.h = h;
    r.w = w;
    return r;
}

Stage loadStage(int s)
{
    Stage st;
    SDL_Rect position = newRect(0, 0, HEIGHT_GAME, WIDTH_GAME);

    // Stage 1
    if (s == 1)
    {
        SDL_Rect *obstacles = malloc(sizeof(SDL_Rect) * 1);
        obstacles[0] = newRect(0,570,10,WIDTH_GAME); // sol
        st.image = IMG_Load(STAGE_01);
        st.position = position;
        st.obstacles = obstacles;
        st.nbObstacles = 1;
        st.x1 = 300;
        st.y1 = 450;
        st.x2 = 980;
        st.y2 = 450;
    }

    // Stage 2 (Super Smash Bros Wii U)
    else if (s == 2)
    {
        SDL_Rect *obstacles = malloc(sizeof(SDL_Rect) * 4);
        obstacles[0] = newRect(244, 477, 10, 838); // grande pf
        obstacles[1] = newRect(342, 354, 10, 192); // pf gauche
        obstacles[2] = newRect(790, 353, 10, 197); // pf droite
        obstacles[3] = newRect(563, 231, 10, 195); // pf haute
        st.image = IMG_Load(STAGE_02);
        st.position = position;
        st.obstacles = obstacles;
        st.nbObstacles = 4;
        st.x1 = 350;
        st.y1 = 240;
        st.x2 = 900;
        st.y2 = 240;
    }

    // Stage 3 (Animal Crossing)
    else if (s == 3)
    {
        SDL_Rect *obstacles = malloc(sizeof(SDL_Rect) * 4);
        obstacles[0] = newRect(172, 556, 10, 956); // grande pf
        obstacles[1] = newRect(76, 327, 10, 246); // pf gauche
        obstacles[2] = newRect(970, 327, 10, 244); // pf droite
        obstacles[3] = newRect(534, 405, 10, 216); // pf milieu
        st.image = IMG_Load(STAGE_03);
        st.position = position;
        st.obstacles = obstacles;
        st.nbObstacles = 4;
        st.x1 = 82;
        st.y1 = 220;
        st.x2 = 1141;
        st.y2 = 224;
    }

    return st;

}



