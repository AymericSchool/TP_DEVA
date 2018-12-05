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
#include "narrow.h"

void jouer(SDL_Surface* screen) {
    // Creation des surfaces
    SDL_Surface *j1 = NULL, *j2 = NULL, *text1 = NULL, *text2 = NULL, *text3 = NULL, *life1, *life2, *surface_debug;

    // Load du stage
    int stageChoisi = 2;
    Stage st = loadStage(stageChoisi);

    // Niveau du bot
    int niveauBot = 1;

    SDL_Rect pos_narrow = newRect(0,0,HEIGHT_GAME,WIDTH_GAME);

    // Narrow
    SDL_Surface *ligne = NULL, *colonne = NULL;
    SDL_Rect position;
        // Ligne
    ligne = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH_GAME, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(ligne, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        // Colonne
    colonne = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, HEIGHT_GAME, 32, 0, 0, 0, 0);
    SDL_FillRect(colonne, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
      int i;

    // Pour les textes
    char vie1[8], vie2[8], fps[8], nbLife1[16], nbLife2[16], text_debug[128];

    // Polices
    TTF_Font *font = NULL, *font2 = NULL;
    font = TTF_OpenFont(FONT_UBUNTU, 65);
    font2 = TTF_OpenFont(FONT_UBUNTU, 20);

    // Couleurs
    SDL_Color couleur_blanc = {255, 255, 255, 0};
    SDL_Color couleur_jaune = {255, 255, 0, 0};
    SDL_Color couleur_orange = {255, 128, 0, 0};
    SDL_Color couleur_rouge = {255, 0, 0, 0};

    //Position des textes
    SDL_Rect pos_text1 = newRect(200, 600, 0, 0);
    SDL_Rect pos_text2 = newRect(1000, 600, 0, 0);
    SDL_Rect pos_fps_counter = newRect(WIDTH_GAME - 100, 0, 0, 0);
    SDL_Rect pos_life1 = newRect(200, 700, 0, 0);
    SDL_Rect pos_life2 = newRect(1000, 700, 0, 0);
    SDL_Rect pos_debug = newRect(0, 0, 0, 0);

    // Position des icones des perso
    SDL_Rect pos_icone1 = newRect(50, 600, 100, 100);
    SDL_Rect pos_icone2 = newRect(850, 600, 100, 100);

    // Variable principale
    int continuer = 1;

    // Variables pour le compteur de FPS
    int temps = 0, tempsIni = 0, nbFps;

    // Variable pour le narrow
    int tempsNarrow = SDL_GetTicks();

    // Creation du Rect des persos
    SDL_Rect pos_j1 = newRect(st.x1,st.y1,96,64);
    Player p1 = newPlayer(1, j1, pos_j1, 1);
    loadStats(&p1);

    SDL_Rect pos_j2 = newRect(st.x2,st.y2,96,64);
    Player p2 = newPlayer(2, j2, pos_j2, 2);
    loadStats(&p2);

     // Chargement des images
    p1.surface = IMG_Load(DROID_00);
    p1.icone = IMG_Load(DROID_ICONE);
    p2.surface = IMG_Load(KIT_00);
    p2.icone = IMG_Load(KIT_ICONE);

    // Rester appuye sur la touche
    SDL_EnableKeyRepeat(10,10);

    // Creation de l'event, et variable de la boucle principale
    SDL_Event event;

    // Affichage du stage en arriere plan
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface(st.image, NULL, screen, &st.position);

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

                    case J1_SHIELD:
                        // Touche shield
                        p1.shield = true;
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

                    case J2_SHIELD:
                        // Touche shield
                        p2.shield = true;
                        break;

                    case SDLK_KP_PLUS:
                        updateNarrow(&pos_narrow, 1);
                        break;
                    case SDLK_KP_MINUS:
                        updateNarrow(&pos_narrow, -1);
                        break;
                    case SDLK_KP_DIVIDE:
                        updateNarrow(&pos_narrow, 0);
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

                    case J1_SHIELD:
                        // Touche shield
                        p1.shield = false;
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

                    case J2_SHIELD:
                        // Touche shield
                        p2.shield = false;
                        break;

                default:
                    break;
            }
            break;
        default:
            break;
        }

    // Deplacements
        move_ia(&p1, &p2, niveauBot);
        moving(&p1, st.obstacles);
        moving(&p2, st.obstacles);

    // Coups
        hit(&p1, &p2);

    // Mort par le Narrow
        if (deadlyNarrow(&p1, &pos_narrow)) {
                p1.life--;
                updateNarrow(&pos_narrow, 0);
                p1.hitbox.x = st.x1;
                p1.hitbox.y = st.y1;
                p1.hp = p1.hpMax;
                p1.estPropulse = 0;
                // Affichage du stage en arriere plan
                SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0, 0, 0));
                SDL_BlitSurface(st.image, NULL, screen, &st.position);

        }
        if (deadlyNarrow(&p2, &pos_narrow)) {
                p2.life--;
                updateNarrow(&pos_narrow, 0);
                p2.hitbox.x = st.x2;
                p2.hitbox.y = st.y2;
                p2.hp = p2.hpMax;
                p2.estPropulse = 0;
                // Affichage du stage en arriere plan
                SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0, 0, 0));
                SDL_BlitSurface(st.image, NULL, screen, &st.position);
        }

    // HUD
        sprintf(vie1, "%d%%", p1.hpMax - p1.hp);
        sprintf(vie2, "%d%%", p2.hpMax - p2.hp);
        sprintf(nbLife1, "Vie(s) : %d", p1.life);
        sprintf(nbLife2, "Vie(s) : %d", p2.life);
        sprintf(text_debug, "Shield : %d, Stun : %d, TimeShield : %d", p1.shield, p1.stun, p1.timeShield);

        // Affichage des PV des persos
        if (p1.hpMax - p1.hp < 25) text1 = TTF_RenderText_Solid(font, vie1, couleur_blanc);
        if (p1.hpMax - p1.hp > 25) text1 = TTF_RenderText_Solid(font, vie1, couleur_jaune);
        if (p1.hpMax - p1.hp > 50) text1 = TTF_RenderText_Solid(font, vie1, couleur_orange);
        if (p1.hpMax - p1.hp > 75) text1 = TTF_RenderText_Solid(font, vie1, couleur_rouge);

        if (p2.hpMax - p2.hp < 25) text2 = TTF_RenderText_Solid(font, vie2, couleur_blanc);
        if (p2.hpMax - p2.hp > 25) text2 = TTF_RenderText_Solid(font, vie2, couleur_jaune);
        if (p2.hpMax - p2.hp > 50) text2 = TTF_RenderText_Solid(font, vie2, couleur_orange);
        if (p2.hpMax - p2.hp > 75) text2 = TTF_RenderText_Solid(font, vie2, couleur_rouge);

        life1 = TTF_RenderText_Solid(font2, nbLife1, couleur_blanc);
        life2 = TTF_RenderText_Solid(font2, nbLife2, couleur_blanc);
        surface_debug = TTF_RenderText_Solid(font2, text_debug, couleur_jaune);

        // Fichiers
        saveStats(p1);
        saveStats(p2);

        //Fps Counter
        temps = tempsIni;
        tempsIni = SDL_GetTicks();
        nbFps = 1000 / (tempsIni - temps);
        sprintf(fps, "FPS : %d", nbFps);
        text3 = TTF_RenderText_Solid(font2, fps, couleur_blanc);

        // Le narrow retrecit (normal)
        tempsNarrow = SDL_GetTicks();
        if (tempsNarrow % 50 == 0) updateNarrow(&pos_narrow, -1);



        // Affichage du stage
        affFond(screen, st.image, &p1.hitbox);
        affFond(screen, st.image, &p2.hitbox);
        affFond(screen, st.image, &pos_text1);
        affFond(screen, st.image, &pos_text2);
        affFond(screen, st.image, &pos_fps_counter);
        affFond(screen, st.image, &pos_debug);

        // Affichage du narrow
        for (i = 0; i < pos_narrow.x; i++)
        {
            // Affichage des lignes (haut)
            position.x = 0;
            position.y = i;
            SDL_BlitSurface(ligne, NULL, screen, &position);

            // Affichage des lignes (bas)
            position.x = 0;
            position.y = HEIGHT_GAME - i;
            SDL_BlitSurface(ligne, NULL, screen, &position);

            // Affichage des lignes (gauche)
            position.x = i;
            position.y = 0;
            SDL_BlitSurface(colonne, NULL, screen, &position);

            // Affichage des lignes (droite)
            position.x = WIDTH_GAME - i;
            position.y = 0;
            SDL_BlitSurface(colonne, NULL, screen, &position);
        }

        // Affichage des sprites et des texts
        SDL_BlitSurface(p1.surface, NULL, screen, &p1.hitbox);
        SDL_BlitSurface(p2.surface, NULL, screen, &p2.hitbox);
        SDL_BlitSurface(p1.icone, NULL, screen, &pos_icone1);
        SDL_BlitSurface(p2.icone, NULL, screen, &pos_icone2);
        SDL_BlitSurface(text1, NULL, screen, &pos_text1);
        SDL_BlitSurface(text2, NULL, screen, &pos_text2);
        SDL_BlitSurface(text3, NULL, screen, &pos_fps_counter);
        SDL_BlitSurface(surface_debug, NULL, screen, &pos_debug);
        SDL_BlitSurface(life1, NULL, screen, &pos_life1);
        SDL_BlitSurface(life2, NULL, screen, &pos_life2);

        SDL_Flip(screen);
        }

    // Liberation memoire
    SDL_FreeSurface(p1.surface);
    SDL_FreeSurface(p2.surface);
    SDL_FreeSurface(text1);
    SDL_FreeSurface(text2);
    SDL_FreeSurface(life1);
    SDL_FreeSurface(life2);
    SDL_FreeSurface(text3);
    SDL_FreeSurface(p1.icone);
    SDL_FreeSurface(p2.icone);
    SDL_FreeSurface(ligne);
    SDL_FreeSurface(colonne);
    SDL_FreeSurface(st.image);
}
