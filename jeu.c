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

void jouer(SDL_Surface* screen, int stageChoisi, bool bot, bool mode, int player1, int player2, int niveauBot) {
    // Creation des surfaces
    SDL_Surface *j1 = NULL, *j2 = NULL, *text1 = NULL, *text2 = NULL, *text3 = NULL, *life1, *life2, *surface_debug, *timerSurface = NULL;

    // Smash Counter
    SDL_Surface
    *s1 = IMG_Load(SMASH_1),
    *s2 = IMG_Load(SMASH_2),
    *s3 = IMG_Load(SMASH_3),
    *s4 = IMG_Load(SMASH_4),
    *s5 = IMG_Load(SMASH_5),
    *s6 = IMG_Load(SMASH_6),
    *s7 = IMG_Load(SMASH_7),
    *s8 = IMG_Load(SMASH_8),
    *s9 = IMG_Load(SMASH_9);

    // Load du stage
    Stage st = loadStage(stageChoisi);

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
    char vie1[8], vie2[8], fps[8], nbLife1[16], nbLife2[16], text_debug[128], timerText[64];


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
    //SDL_Rect pos_debug = newRect(0, 0, 0, 0);
    SDL_Rect pos_timer = newRect(0,0,0,0);

    // Position des icones des perso
    SDL_Rect pos_icone1 = newRect(50, 600, 100, 100);
    SDL_Rect pos_icone2 = newRect(850, 600, 100, 100);

    // Variable principale
    int continuer = 1;

    // Variables pour le compteur de FPS
    int temps = 0, tempsIni = 0, nbFps;
    int  timerTemps = LIMIT_TIME;

    // Variable pour le narrow
    int tempsNarrow = SDL_GetTicks();

    // Creation du Rect des persos
    SDL_Rect pos_j1 = newRect(st.x1,st.y1,96,64);
    Player p1 = newPlayer(player1, j1, pos_j1, 1);
    Player p2;
    loadStats(&p1);

    SDL_Rect pos_j2 = newRect(st.x2,st.y2,96,64);
    if (bot) p2 = newPlayer(player2, j2, pos_j2, 2);
    else p2 = newPlayer(player2, j2, pos_j2, 1);
    loadStats(&p2);

    SDL_Surface *punch1 = NULL, *stun1 = NULL, *shield1 = NULL, *def1 = NULL;
    SDL_Surface *punch2 = NULL, *stun2 = NULL, *shield2 = NULL, *def2 = NULL;
    bool attack1 = false;
    bool attack2 = false;

    switch (player1)
    {
    case 1:
        p1.jump = 250;
        p1.speed = 7;
        p1.surface = IMG_Load(DROID_00);
        p1.icone = IMG_Load(DROID_ICONE);
        punch1 = IMG_Load(DROID_09);
        stun1 = IMG_Load(DROID_13);
        shield1 = IMG_Load(DROID_15);
        def1 = p1.surface;
        break;

    case 2:
        p1.jump = 150;
        p1.speed = 10;
        p1.surface = IMG_Load(KIT_00);
        p1.icone = IMG_Load(KIT_ICONE);
        punch1 = IMG_Load(KIT_09);
        stun1 = IMG_Load(KIT_13);
        shield1 = IMG_Load(KIT_15);
        def1 = p1.surface;
        break;

    case 3:
        p1.hp = 60;
        p1.hpMax = 60;
        p1.life = 4;
        p1.surface = IMG_Load(TUX_00);
        p1.icone = IMG_Load(TUX_ICONE);
        punch1 = IMG_Load(TUX_09);
        stun1 = IMG_Load(TUX_13);
        shield1 = IMG_Load(TUX_15);
        def1 = p1.surface;
        break;

    case 4:
        p1.hp = 40;
        p1.hpMax = 40;
        p1.life = 6;
        p1.surface = IMG_Load(WILBER_00);
        p1.icone = IMG_Load(WILBER_ICONE);
        punch1 = IMG_Load(WILBER_09);
        stun1 = IMG_Load(WILBER_13);
        shield1 = IMG_Load(WILBER_15);
        def1 = p1.surface;
        break;

    default:
        break;
    }

    switch (player2)
    {
    case 1:
        p2.jump = 250;
        p2.speed = 7;
        p2.surface = IMG_Load(DROID_00);
        p2.icone = IMG_Load(DROID_ICONE);
        punch2 = IMG_Load(DROID_09);
        stun2 = IMG_Load(DROID_13);
        shield2 = IMG_Load(DROID_15);
        def2 = p2.surface;
        break;
    case 2:
        p2.jump = 150;
        p2.speed = 10;
        p2.surface = IMG_Load(KIT_00);
        p2.icone = IMG_Load(KIT_ICONE);
        punch2 = IMG_Load(KIT_09);
        stun2 = IMG_Load(KIT_13);
        shield2 = IMG_Load(KIT_15);
        def2 = p2.surface;
        break;
        break;
    case 3:
        p2.hp = 60;
        p2.hpMax = 60;
        p2.life = 4;
        p2.surface = IMG_Load(TUX_00);
        p2.icone = IMG_Load(TUX_ICONE);
        punch2 = IMG_Load(TUX_09);
        stun2 = IMG_Load(TUX_13);
        shield2 = IMG_Load(TUX_15);
        def2 = p2.surface;
        break;
        break;
    case 4:
        p2.hp = 40;
        p2.hpMax = 40;
        p2.life = 6;
        p2.surface = IMG_Load(WILBER_00);
        p2.icone = IMG_Load(WILBER_ICONE);
        punch2 = IMG_Load(WILBER_09);
        stun2 = IMG_Load(WILBER_13);
        shield2 = IMG_Load(WILBER_15);
        def2 = p2.surface;
        break;
        break;
    default:
        break;
    }

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
                            attack1 = true;
                            p1.attack = 1;
                            p1.canAttack = 0;
                        }
                        break;

                    case J1_SHIELD:
                        // Touche shield
                        if (!p1.stun) p1.shield = true;
                        break;

                    case J1_SMASH:
                        // Attaque smash
                        p1.smash = 1;
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
                            attack2 = true;
                            p2.attack = 1;
                            p2.canAttack = 0;
                        }
                        break;

                    case J2_SHIELD:
                        // Touche shield
                        if (!p2.stun) p2.shield = true;
                        break;

                    case J2_SMASH:
                        p2.smash = 1;
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
                            if (p1.type == 1) attack1 = false;
                            break;

                    case J1_SHIELD:
                        // Touche shield
                        p1.shield = false;
                        break;

                    case J1_SMASH:
                        p1.smash = 0;
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
                        if (p2.type == 1) attack2 = false;
                        break;

                    case J2_SHIELD:
                        // Touche shield
                        p2.shield = false;
                        break;

                    case J2_SMASH:
                        p2.smash = 0;
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
        moving(&p1, st.obstacles, st.nbObstacles);
        moving(&p2, st.obstacles, st.nbObstacles);

    // Coups
        hit(&p1, &p2);

    // Mort par le Narrow
        if (deadlyNarrow(&p1, &pos_narrow)) {
                if (mode) p1.life--;
                else
                {
                    p1.points--;
                    p2.points++;
                }
                updateNarrow(&pos_narrow, 0);
                p1.hitbox.x = st.x1;
                p1.hitbox.y = st.y1;
                p1.hp = p1.hpMax;
                p1.estPropulse = 0;
                p1.stun = false;
                // Affichage du stage en arriere plan
                SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0, 0, 0));
                SDL_BlitSurface(st.image, NULL, screen, &st.position);

        }
        if (deadlyNarrow(&p2, &pos_narrow)) {
                if (mode) p2.life--;
                else
                {
                    p1.points++;
                    p2.points--;
                }
                updateNarrow(&pos_narrow, 0);
                p2.hitbox.x = st.x2;
                p2.hitbox.y = st.y2;
                p2.hp = p2.hpMax;
                p2.estPropulse = 0;
                p2.stun = false;
                // Affichage du stage en arriere plan
                SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0, 0, 0));
                SDL_BlitSurface(st.image, NULL, screen, &st.position);
        }

    // HUD
    if (mode)
    {
        sprintf(vie1, "%d%%", 100 - (p1.hp * 100) / p1.hpMax);
        sprintf(vie2, "%d%%", 100 - (p2.hp * 100) / p2.hpMax);
        sprintf(nbLife1, "Vie(s) : %d", p1.life);
        sprintf(nbLife2, "Vie(s) : %d", p2.life);
    }
    else
    {
        sprintf(nbLife1, "Point(s) : %d", p1.points);
        sprintf(nbLife2, "Point(s) : %d", p2.points);
    }

        sprintf(text_debug, "p1 smash %d", p1.smash);

        // Affichage des PV des persos

            if (100 - (p1.hp * 100) / p1.hpMax < 25) text1 = TTF_RenderText_Solid(font, vie1, couleur_blanc);
            if (100 - (p1.hp * 100) / p1.hpMax > 25) text1 = TTF_RenderText_Solid(font, vie1, couleur_jaune);
            if (100 - (p1.hp * 100) / p1.hpMax > 50) text1 = TTF_RenderText_Solid(font, vie1, couleur_orange);
            if (100 - (p1.hp * 100) / p1.hpMax > 75) text1 = TTF_RenderText_Solid(font, vie1, couleur_rouge);

            if (100 - (p2.hp * 100) / p2.hpMax < 25) text2 = TTF_RenderText_Solid(font, vie2, couleur_blanc);
            if (100 - (p2.hp * 100) / p2.hpMax > 25) text2 = TTF_RenderText_Solid(font, vie2, couleur_jaune);
            if (100 - (p2.hp * 100) / p2.hpMax > 50) text2 = TTF_RenderText_Solid(font, vie2, couleur_orange);
            if (100 - (p2.hp * 100) / p2.hpMax > 75) text2 = TTF_RenderText_Solid(font, vie2, couleur_rouge);




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

        // Timer
        if (!mode)
        {
            timerTemps--;
            sprintf(timerText, "Timer : %dmin%.2d", ((timerTemps) / 100)/60, ((timerTemps)/100)%60);
            timerSurface = TTF_RenderText_Solid(font2, timerText, couleur_blanc);
        }



        // Le narrow retrecit (normal)
        tempsNarrow = SDL_GetTicks();
        if (tempsNarrow % 50 == 0) updateNarrow(&pos_narrow, -1);

        // Conditions de victoires
        if (mode)
        {
            if (p1.life == 0)
            {
                p1.defeat++;
                p2.victory++;
                saveStats(p1);
                saveStats(p2);
                continuer = 0;
            }
            else if (p2.life == 0)
            {
                p1.victory++;
                p2.defeat++;
                saveStats(p1);
                saveStats(p2);
                continuer = 0;
            }
        }
        else if (!mode)
        {
            if (((timerTemps) / 100) == 0) continuer = 0;
        }

        // Affichage du stage
        affFond(screen, st.image, &p1.hitbox);
        affFond(screen, st.image, &p2.hitbox);
        affFond(screen, st.image, &pos_text1);
        affFond(screen, st.image, &pos_text2);
        affFond(screen, st.image, &pos_fps_counter);
        affFond(screen, st.image, &pos_timer);
        //affFond(screen, st.image, &pos_debug);

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



        if (attack1) p1.surface = punch1;
        else if (p1.stun) p1.surface = stun1;
        else if (p1.shield) p1.surface = shield1;
        else p1.surface = def1;

        if (attack2) p2.surface = punch2;
        else if (p2.stun) p2.surface = stun2;
        else if (p2.shield) p2.surface = shield2;
        else p2.surface = def2;





        // Affichage des sprites et des texts
        SDL_BlitSurface(p1.surface, NULL, screen, &p1.hitbox);
        SDL_BlitSurface(p2.surface, NULL, screen, &p2.hitbox);
        SDL_BlitSurface(p1.icone, NULL, screen, &pos_icone1);
        switch (p1.bufferSmash)
        {
        case 0:
            break;
        case 1:
            SDL_BlitSurface(s1, NULL, screen, &pos_icone1);
            break;
        case 2:
            SDL_BlitSurface(s2, NULL, screen, &pos_icone1);
            break;
        case 3:
            SDL_BlitSurface(s3, NULL, screen, &pos_icone1);
            break;
        case 4:
            SDL_BlitSurface(s4, NULL, screen, &pos_icone1);
            break;
        case 5:
            SDL_BlitSurface(s5, NULL, screen, &pos_icone1);
            break;
        case 6:
            SDL_BlitSurface(s6, NULL, screen, &pos_icone1);
            break;
        case 7:
            SDL_BlitSurface(s7, NULL, screen, &pos_icone1);
            break;
        case 8:
            SDL_BlitSurface(s8, NULL, screen, &pos_icone1);
            break;
        default:
            SDL_BlitSurface(s9, NULL, screen, &pos_icone1);
            break;
        }
        SDL_BlitSurface(p2.icone, NULL, screen, &pos_icone2);
        switch (p2.bufferSmash)
        {
        case 0:
            break;
        case 1:
            SDL_BlitSurface(s1, NULL, screen, &pos_icone2);
            break;
        case 2:
            SDL_BlitSurface(s2, NULL, screen, &pos_icone2);
            break;
        case 3:
            SDL_BlitSurface(s3, NULL, screen, &pos_icone2);
            break;
        case 4:
            SDL_BlitSurface(s4, NULL, screen, &pos_icone2);
            break;
        case 5:
            SDL_BlitSurface(s5, NULL, screen, &pos_icone2);
            break;
        case 6:
            SDL_BlitSurface(s6, NULL, screen, &pos_icone2);
            break;
        case 7:
            SDL_BlitSurface(s7, NULL, screen, &pos_icone2);
            break;
        case 8:
            SDL_BlitSurface(s8, NULL, screen, &pos_icone2);
            break;
        default:
            SDL_BlitSurface(s9, NULL, screen, &pos_icone2);
            break;
        }
        if (mode) SDL_BlitSurface(text1, NULL, screen, &pos_text1);
        if (mode) SDL_BlitSurface(text2, NULL, screen, &pos_text2);
        SDL_BlitSurface(text3, NULL, screen, &pos_fps_counter);
        SDL_BlitSurface(timerSurface, NULL, screen, &pos_timer);
        //SDL_BlitSurface(surface_debug, NULL, screen, &pos_debug);
        SDL_BlitSurface(life1, NULL, screen, &pos_life1);
        SDL_BlitSurface(life2, NULL, screen, &pos_life2);


        SDL_Flip(screen);
        }

    // Liberation memoire
    SDL_FreeSurface(p1.surface);
    SDL_FreeSurface(p2.surface);
    SDL_FreeSurface(text1);
    SDL_FreeSurface(s1);
    SDL_FreeSurface(s2);
    SDL_FreeSurface(s3);
    SDL_FreeSurface(s4);
    SDL_FreeSurface(s5);
    SDL_FreeSurface(s6);
    SDL_FreeSurface(s7);
    SDL_FreeSurface(s8);
    SDL_FreeSurface(s9);
    SDL_FreeSurface(text2);
    SDL_FreeSurface(timerSurface);
    SDL_FreeSurface(life1);
    SDL_FreeSurface(life2);
    SDL_FreeSurface(surface_debug);
    SDL_FreeSurface(text3);
    SDL_FreeSurface(p1.icone);
    SDL_FreeSurface(p2.icone);
    SDL_FreeSurface(ligne);
    SDL_FreeSurface(colonne);
    SDL_FreeSurface(st.image);
}
