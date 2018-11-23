/*
jeu.c
programme qui lance le jeu sur la surface donnee
tout commence ici
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "player.h"
#include "obstacles.h"
#include "sprites.h"
#include "ia.h"
#include "stats.h"

void jouer(SDL_Surface* screen) {
    SDL_Surface *j1 = NULL, *j2 = NULL, *green_box = NULL, *text1 = NULL, *text2 = NULL, *text3 = NULL;
    SDL_Surface *stage = NULL;
    SDL_Rect pos_stage = newRect(0,0,0,0);

    char vie1[7], vie2[7], fps[15];

    TTF_Font *font = NULL, *font2 = NULL;
    font = TTF_OpenFont(FONT_UBUNTU, 65);
    font2 = TTF_OpenFont(FONT_UBUNTU, 20);

    SDL_Color couleur_blanc = {255, 255, 255, 0};
    SDL_Color couleur_jaune = {255, 255, 0, 0};
    SDL_Color couleur_orange = {255, 128, 0, 0};
    SDL_Color couleur_rouge = {255, 0, 0, 0};

    SDL_Rect pos_text1 = newRect(200, 600, 100, 100);
    SDL_Rect pos_text2 = newRect(1000, 600, 100, 100);

    SDL_Rect pos_icone1 = newRect(50, 600, 100, 100);
    SDL_Rect pos_icone2 = newRect(850, 600, 100, 100);

    int continuer = 1;
    int temps = 0, tempsIni = 0, nbFps;

    SDL_Rect pos_fps_counter = newRect(WIDTH_GAME - 100, 0, 0, 0);

    // Creation du Rect des persos
    SDL_Rect pos_j1 = newRect(200,150,96,64);
    Player p1 = newPlayer(1, j1, pos_j1, 1);
    p1.speed = 8;
    loadStats(&p1);



    SDL_Rect pos_j2 = newRect(1000,150,96,64);
    Player p2 = newPlayer(2, j2, pos_j2, 1);
    p2.speed = 8;
    loadStats(&p2);

    // Tableau d'obstacles
    SDL_Rect *obstacles;
    obstacles = malloc(sizeof(SDL_Rect) * 100);

    // Creation des obstacles
    obstacles[0] = newRect(0,HEIGHT_GAME - 150,50,WIDTH_GAME); // sol
    obstacles[2] = newRect(500,200,100,100); // box verte

     // Chargement des images
    p1.surface = IMG_Load(DROID_00);
    p1.icone = IMG_Load(DROID_ICONE);
    p2.surface = IMG_Load(KIT_00);
    p2.icone = IMG_Load(KIT_ICONE);

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
                        if (p1.type == 1) p1.up = 1;
                        break;
                    case J1_LEFT:
                        // Touche gauche pressee
                        if (p1.type == 1) p1.left = 1;
                        break;
                    case J1_RIGHT:
                        // Touche droite pressee
                        if (p1.type == 1) p1.right = 1;
                        break;
                    case J1_ATTACK:
                        // Touche attaque pressee
                        if (p1.canAttack && p1.type == 1) {
                            p1.attack = 1;
                            p1.canAttack = 0;
                        }
                        if (p1.type == 1) p1.buffer++;
                        break;


                    case J2_UP:
                        // Touche espace pressee
                        if (p2.type == 1) p2.up = 1;
                        break;
                    case J2_LEFT:
                        // Touche gauche pressee
                        if (p2.type == 1) p2.left = 1;
                        break;
                    case J2_RIGHT:
                        // Touche droite pressee
                        if (p2.type == 1) p2.right = 1;
                        break;
                    case J2_ATTACK:
                        // Touche attaque pressee
                        if (p2.canAttack && p2.type == 1) {
                            p2.attack = 1;
                            p2.canAttack = 0;
                        }
                        if (p2.type == 1) p2.buffer++;
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
                            if (p1.type == 1) p1.up = 0;
                            break;
                        case J1_LEFT:
                            // Touche gauche relachee
                            if (p1.type == 1) p1.left = 0;
                            break;
                        case J1_RIGHT:
                            // Touche droite relachee
                            if (p1.type == 1) p1.right = 0;
                            break;
                        case J1_ATTACK:
                            // Touche attaque relachee
                            if (p1.type == 1) p1.attack = 0;
                            if (p1.type == 1) p1.canAttack = 1;
                            if (p1.type == 1) p1.buffer = 0;
                            break;


                    case J2_UP:
                        // Touche espace relachee
                        if (p2.type == 1) p2.up = 0;
                        break;
                    case J2_LEFT:
                        // Touche gauche relachee
                        if (p2.type == 1) p2.left = 0;
                        break;
                    case J2_RIGHT:
                        // Touche droite relachee
                        if (p2.type == 1) p2.right = 0;
                     case J2_ATTACK:
                        // Touche attaque relachee
                        if (p2.type == 1) p2.attack = 0;
                        if (p2.type == 1) p2.canAttack = 1;
                        if (p2.type == 1) p2.buffer = 0;
                        break;

                default:
                    break;
            }
            break;
        default:
            break;
        }

    // Deplacements
        move_ia(&p1, &p2);
        moving(&p1, obstacles);
        moving(&p2, obstacles);
    // Coups
        hit(&p1, &p2);
    // HUD
        sprintf(vie1, "%d%%", p1.hpMax - p1.hp);
        sprintf(vie2, "%d%%", p2.hpMax - p2.hp);

        if (p1.hpMax - p1.hp < 25) text1 = TTF_RenderText_Solid(font, vie1, couleur_blanc);
        if (p1.hpMax - p1.hp > 25) text1 = TTF_RenderText_Solid(font, vie1, couleur_jaune);
        if (p1.hpMax - p1.hp > 50) text1 = TTF_RenderText_Solid(font, vie1, couleur_orange);
        if (p1.hpMax - p1.hp > 75) text1 = TTF_RenderText_Solid(font, vie1, couleur_rouge);

        if (p2.hpMax - p2.hp < 25) text2 = TTF_RenderText_Solid(font, vie2, couleur_blanc);
        if (p2.hpMax - p2.hp > 25) text2 = TTF_RenderText_Solid(font, vie2, couleur_jaune);
        if (p2.hpMax - p2.hp > 50) text2 = TTF_RenderText_Solid(font, vie2, couleur_orange);
        if (p2.hpMax - p2.hp > 75) text2 = TTF_RenderText_Solid(font, vie2, couleur_rouge);

        // Fichiers
        saveStats(p1);
        saveStats(p2);

        //Fps Counter
        temps = tempsIni;
        tempsIni = SDL_GetTicks();
        nbFps = 1000 / (tempsIni - temps);
        sprintf(fps, "FPS : %d", nbFps);
        text3 = TTF_RenderText_Solid(font2, fps, couleur_blanc);


         // Affichage
        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(stage, NULL, screen, &pos_stage);
        SDL_BlitSurface(p1.surface, NULL, screen, &p1.hitbox);
        SDL_BlitSurface(p2.surface, NULL, screen, &p2.hitbox);
        SDL_BlitSurface(green_box, NULL, screen, &obstacles[2]);
        SDL_BlitSurface(p1.icone, NULL, screen, &pos_icone1);
        SDL_BlitSurface(p2.icone, NULL, screen, &pos_icone2);
        SDL_BlitSurface(text1, NULL, screen, &pos_text1);
        SDL_BlitSurface(text2, NULL, screen, &pos_text2);
        SDL_BlitSurface(text3, NULL, screen, &pos_fps_counter);
        SDL_Flip(screen);
        }

    // Liberation memoire
    SDL_FreeSurface(p1.surface);
    SDL_FreeSurface(p2.surface);
    SDL_FreeSurface(text1);
    SDL_FreeSurface(text2);
    SDL_FreeSurface(p1.icone);
    SDL_FreeSurface(p2.icone);
    SDL_FreeSurface(stage);
    SDL_FreeSurface(green_box);
}
