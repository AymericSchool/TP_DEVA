/*
jeu.c
programme qui lance le jeu sur la surface donnee
tout commence ici
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "player.h"
#include "obstacles.h"
#include "sprites.h"

void jouer(SDL_Surface* screen) {
    SDL_Surface *j1 = NULL, *j2 = NULL, *box = NULL, *green_box = NULL;
    SDL_Surface *stage = NULL;
    SDL_Rect pos_stage = newRect(0,0,0,0);

    int continuer = 1;

    // Creation du Rect des persos
    SDL_Rect pos_j1 = newRect(100,100,96,64);
    Player p1 = newPlayer(j1, pos_j1, "humain");

    SDL_Rect pos_j2 = newRect(200,100,96,64);;
    Player p2 = newPlayer(j2, pos_j2, "humain");

    // Tableau d'obstacles
    SDL_Rect *obstacles;
    obstacles = malloc(sizeof(SDL_Rect) * 100);

    // Creation des obstacles
    obstacles[0] = newRect(0,HEIGHT_GAME,50,WIDTH_GAME); // sol
    obstacles[1] = newRect(300,572,28,50); // box bleue
    obstacles[2] = newRect(500,200,100,100); // box verte

     // Chargement des images
    p1.surface = IMG_Load(DROID_00);
    p2.surface = IMG_Load(KIT_00);
    box = IMG_Load(BLUE_BOX);
    green_box = IMG_Load(GREEN_BOX);
    stage = IMG_Load(STAGE_01);

    // Rester appuye sur la touche
    SDL_EnableKeyRepeat(10,10);

    // Creation de l'event, et variable de la boucle principale
    SDL_Event event;

    // Boucle principale
    while (continuer) {
        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            // On quitte
            continuer = 0;
        case SDL_KEYDOWN:
            // Une touche est pressee
            switch (event.key.keysym.sym)
            {
            case J1_UP:
                // Touche espace pressee
                p1.up = 1;
                break;
            case J1_LEFT:
                // Touche gauche pressee
                p1.left = 1;
                break;
            case J1_RIGHT:
                // Touche droite pressee
                p1.right = 1;
                break;
            case J1_ATTACK:
                // Touche attaque pressee
                p1.attack = 1;
                break;
            case J2_UP:
                // Touche espace pressee
                p2.up = 1;
                break;
            case J2_LEFT:
                // Touche gauche pressee
                p2.left = 1;
                break;
            case J2_RIGHT:
                // Touche droite pressee
                p2.right = 1;
                break;
            case J2_ATTACK:
                // Touche attaque pressee
                p2.attack = 1;
                break;
            case SDLK_ESCAPE:
                // Touche echap, on stop
                continuer = 0;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
                case J1_UP:
                    // Touche espace relachee
                    p1.up = 0;
                    break;
                case J1_LEFT:
                    // Touche gauche relachee
                    p1.left = 0;
                    break;
                case J1_RIGHT:
                    // Touche droite relachee
                    p1.right = 0;
                    break;
                case J1_ATTACK:
                    // Touche attaque relachee
                    p1.attack = 0;
                    break;
                case J2_UP:
                    // Touche espace relachee
                    p2.up = 0;
                    break;
                case J2_LEFT:
                    // Touche gauche relachee
                    p2.left = 0;
                    break;
                case J2_RIGHT:
                    // Touche droite relachee
                    p2.right = 0;
                 case J2_ATTACK:
                    // Touche attaque relachee
                    p2.attack = 0;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
        }

         moving(&p1, obstacles);
         moving(&p2, obstacles);
         hit(&p1, &p2);

         // Affichage
        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 255, 255, 255));
        SDL_BlitSurface(stage, NULL, screen, &pos_stage);
        SDL_BlitSurface(p1.surface, NULL, screen, &p1.hitbox);
        SDL_BlitSurface(p2.surface, NULL, screen, &p2.hitbox);
        SDL_BlitSurface(box, NULL, screen, &obstacles[1]);
        SDL_BlitSurface(green_box, NULL, screen, &obstacles[2]);
        SDL_Flip(screen);
        }

    // Liberation memoire
    SDL_FreeSurface(p1.surface);
    SDL_FreeSurface(p2.surface);
    SDL_FreeSurface(box);
    SDL_FreeSurface(green_box);
}
