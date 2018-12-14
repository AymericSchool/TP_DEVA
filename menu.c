
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "player.h"
#include "obstacles.h"
#include "constantes.h"
#include "jeu.h"
<<<<<<< HEAD
#include "stats.h"
#include "sprites.h"
#include "menu.h"

void realMenu(SDL_Surface* screen)
{

    int menuPrin = jouerVies;
    int menuStage = stage1;
    int choixPersoJ1 = droid; int j1Pret = 0;
    int choixPersoJ2 = wilber; int j2Pret = 0;
    int etat = menuMain;

    SDL_Surface *menuPrin1, *menuPrin2, *menuPrin3, *menuPrin4, *menuPrin5;
    SDL_Surface *statistique, *commentJ, *credit;
    SDL_Rect pos = newRect(0, 0, 0, 0);
    menuPrin1 = IMG_Load("res/Menu/MenuJouerVies.jpg");
    menuPrin2 = IMG_Load("res/Menu/MenuJouerTemps.jpg");
    menuPrin3 = IMG_Load("res/Menu/MenuCommentJouer.jpg");
    menuPrin4 = IMG_Load("res/Menu/MenuStatistiques.jpg");
    menuPrin5 = IMG_Load("res/Menu/MenuCredits.jpg");
    statistique = IMG_Load("res/Menu/MenuWIP.jpg");
    commentJ = IMG_Load("res/Menu/MenuWIP.jpg");
    credit = IMG_Load("res/Menu/MenuWIP.jpg");


    SDL_Surface *menuStageS, *selectStage;
    SDL_Rect posSelectStage = newRect(674, 82, 0, 0);
    menuStageS = IMG_Load("res/Menu/StageSelect.jpg");
    selectStage = IMG_Load("res/Menu/CadreSelectStage.png");
    SDL_Surface *sStage1, *sStage2, *sStage3, *sStage4, *sStage5, *sStage6;
    SDL_Rect posStage = newRect(15, 131, 0, 0);
    sStage1 = IMG_Load("res/Menu/stage_01.jpg");
    sStage2 = IMG_Load("res/Menu/stage_02.jpg");
    sStage3 = IMG_Load("res/Menu/stage_03.jpg");
    sStage4 = IMG_Load("res/Menu/stage_04.jpg");
    sStage5 = IMG_Load("res/Menu/stage_05.jpg");
    sStage6 = IMG_Load("res/Menu/stage_06.jpg");

    SDL_Surface *sMenuChr, *sIconeJ1, *sIconeJ2;
    SDL_Surface *iDroid, *iKit, *iTux, *iWilber;
    SDL_Rect posIconeJ1 = newRect(145, 155, 0, 0);
    SDL_Rect posIconeJ2 = newRect(195, 155, 0, 0);
    SDL_Rect posIJ1 = newRect(300, 485, 0, 0);
    SDL_Rect posIJ2 = newRect(800, 485, 0, 0);
    sMenuChr = IMG_Load("res/Menu/ChrSelect.jpg");
    sIconeJ1 = IMG_Load("res/Menu/IconeJ1.png");
    sIconeJ2 = IMG_Load("res/Menu/IconeJ2.png");
    iDroid = IMG_Load(DROID_ICONE);
    iKit = IMG_Load(KIT_ICONE);
    iTux = IMG_Load(TUX_ICONE);
    iWilber = IMG_Load(WILBER_ICONE);



    int continuer = 1;
    SDL_Event event;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        if (etat == statistiques || etat == comment || etat == cred) {
                            etat = menuMain;
                        }
                        else if (etat == stageSelect) {
                            etat = menuMain;
                        }
                        else if (etat == chrSelect) {
                            etat = stageSelect;
                        }


                        else continuer = 0;
                        break;

                    case SDLK_w:
                        if (etat == menuMain)
                        {
                            switch(menuPrin)
                            {
                                case jouerTemps:
                                    menuPrin = jouerVies;
                                    break;
                                case stats:
                                    menuPrin = commentJouer;
                                    break;
                                case credits:
                                    menuPrin = stats;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == stageSelect)
                        {
                            switch(menuStage)
                            {
                                case stage3:
                                    menuStage = stage1;
                                    break;
                                case stage5:
                                    menuStage = stage3;
                                    break;
                                case stage4:
                                    menuStage = stage2;
                                    break;
                                case stage6:
                                    menuStage = stage4;
                                    break;
                                default:
                                    break;
                            }
                        }


                        break;

                    case SDLK_s:
                        if (etat == menuMain)
                        {
                            switch(menuPrin)
                            {
                                case jouerVies:
                                    menuPrin = jouerTemps;
                                    break;
                                case commentJouer:
                                    menuPrin = stats;
                                    break;
                                case stats:
                                    menuPrin = credits;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == stageSelect)
                        {
                            switch(menuStage)
                            {
                                case stage1:
                                    menuStage = stage3;
                                    break;
                                case stage3:
                                    menuStage = stage5;
                                    break;
                                case stage2:
                                    menuStage = stage4;
                                    break;
                                case stage4:
                                    menuStage = stage6;
                                    break;
                                default:
                                    break;
                            }
                        }


                        break;

                    case SDLK_a:
                          if (etat == menuMain)
                        {
                            switch(menuPrin)
                            {
                                case commentJouer:
                                    menuPrin = jouerVies;
                                    break;
                                case credits:
                                    menuPrin = jouerTemps;
                                    break;
                                case stats:
                                    menuPrin = jouerVies;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == stageSelect)
                        {
                            switch(menuStage)
                            {
                                case stage2:
                                    menuStage = stage1;
                                    break;
                                case stage4:
                                    menuStage = stage3;
                                    break;
                                case stage6:
                                    menuStage = stage5;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == chrSelect && j1Pret == 0)
                        {
                            switch(choixPersoJ1)
                            {
                                case wilber:
                                    choixPersoJ1 = tux;
                                    break;
                                case tux:
                                    choixPersoJ1 = kit;
                                    break;
                                case kit:
                                    choixPersoJ1 = droid;
                                    break;
                                default:
                                    break;
                            }
                        }

                        break;

                    case SDLK_d:
                        if (etat == menuMain)
                        {
                            switch(menuPrin)
                            {
                                case jouerVies:
                                    menuPrin = commentJouer;
                                    break;
                                case jouerTemps:
                                    menuPrin = credits;
                                    break;

                            }
                        }

                        else if (etat == stageSelect)
                        {
                            switch(menuStage)
                            {
                                case stage1:
                                    menuStage = stage2;
                                    break;
                                case stage3:
                                    menuStage = stage4;
                                    break;
                                case stage5:
                                    menuStage = stage6;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == chrSelect && j1Pret == 0)
                        {
                            switch(choixPersoJ1)
                            {
                                case tux:
                                    choixPersoJ1 = wilber;
                                    break;
                                case kit:
                                    choixPersoJ1 = tux;
                                    break;
                                case droid:
                                    choixPersoJ1 = kit;
                                    break;
                                default:
                                    break;
                            }
                        }

                        break;


                    case SDLK_RIGHT:
                        if (etat == chrSelect && j2Pret == 0)
                        {
                            switch(choixPersoJ2)
                            {
                                case tux:
                                    choixPersoJ2 = wilber;
                                    break;
                                case kit:
                                    choixPersoJ2 = tux;
                                    break;
                                case droid:
                                    choixPersoJ2 = kit;
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;

                    case SDLK_LEFT:
                        if (etat == chrSelect && j2Pret == 0)
                        {
                            switch(choixPersoJ2)
                            {
                                case wilber:
                                    choixPersoJ2 = tux;
                                    break;
                                case tux:
                                    choixPersoJ2 = kit;
                                    break;
                                case kit:
                                    choixPersoJ2 = droid;
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;



                    case SDLK_SPACE:
                        if (etat == menuMain && menuPrin == stats) {
                            etat = statistiques;
                        }
                        else if (etat == menuMain && menuPrin == credits) {
                            etat = cred;
                        }
                        else if (etat == menuMain && menuPrin == commentJouer) {
                            etat = comment;
                        }
                        else if (etat == menuMain && menuPrin == jouerVies) {
                            etat = stageSelect;
                        }
                         else if (etat == menuMain && menuPrin == jouerTemps) {
                            etat = stageSelect;
                        }
                        else if (etat == stageSelect) {
                            etat = chrSelect;
                        }
                        else if (etat == chrSelect && j1Pret == 0) {
                            j1Pret = 1;
                        }
                        break;
                    default:
                        break;

                    case SDLK_KP0:
                        if (etat == chrSelect && j2Pret == 0) {
                            j2Pret = 1;
                        }

                    case SDLK_RETURN:
                        if (etat == chrSelect && j1Pret && j2Pret) {
                                if (menuPrin == jouerVies)
                                    jouer(screen, menuStage+1, false, true, choixPersoJ1, choixPersoJ2);
                                else if (menuPrin == jouerTemps)
                                    jouer(screen, menuStage+1, false, false, choixPersoJ1, choixPersoJ2);

                        }
                }

            default:
                break;
        }



        switch(etat)
        {
            case menuMain:
                switch(menuPrin)
                {
                    case jouerVies:
                        SDL_BlitSurface(menuPrin1, NULL, screen, &pos);
                        break;
                    case jouerTemps:
                        SDL_BlitSurface(menuPrin2, NULL, screen, &pos);
                        break;
                    case commentJouer:
                        SDL_BlitSurface(menuPrin3, NULL, screen, &pos);
                        break;
                    case stats:
                        SDL_BlitSurface(menuPrin4, NULL, screen, &pos);
                        break;
                    case credits:
                        SDL_BlitSurface(menuPrin5, NULL, screen, &pos);
                        break;
                }
                break;

            case statistiques:
                SDL_BlitSurface(statistique, NULL, screen, &pos);
                break;

            case comment:
                SDL_BlitSurface(commentJ, NULL, screen, &pos);
                break;

            case cred:
                SDL_BlitSurface(credit, NULL, screen, &pos);
                break;

            case stageSelect:
                SDL_BlitSurface(menuStageS, NULL, screen, &pos);
                switch(menuStage)
                {
                    case stage1:
                        posSelectStage.x = 674; posSelectStage.y = 82;
                        SDL_BlitSurface(sStage1, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage2:
                        posSelectStage.x = 953; posSelectStage.y = 82;
                        SDL_BlitSurface(sStage2, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage3:
                        posSelectStage.x = 674; posSelectStage.y = 241;
                        SDL_BlitSurface(sStage3, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage4:
                        posSelectStage.x = 953; posSelectStage.y = 241;
                        SDL_BlitSurface(sStage4, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage5:
                        posSelectStage.x = 674; posSelectStage.y = 399;
                        SDL_BlitSurface(sStage5, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage6:
                        posSelectStage.x = 953; posSelectStage.y = 399;
                        SDL_BlitSurface(sStage6, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                }
                break;

            case chrSelect:
                SDL_BlitSurface(sMenuChr, NULL, screen, &pos);
                switch(choixPersoJ1)
                {
                    case droid:
                        posIconeJ1.x = 145;
                        SDL_BlitSurface(iDroid, NULL, screen, &posIJ1);
                        SDL_BlitSurface(sIconeJ1, NULL, screen, &posIconeJ1);
                        break;
                    case kit:
                        posIconeJ1.x = 420;
                        SDL_BlitSurface(iKit, NULL, screen, &posIJ1);
                        SDL_BlitSurface(sIconeJ1, NULL, screen, &posIconeJ1);
                        break;
                    case tux:
                        posIconeJ1.x = 745;
                        SDL_BlitSurface(iTux, NULL, screen, &posIJ1);
                        SDL_BlitSurface(sIconeJ1, NULL, screen, &posIconeJ1);
                        break;
                    case wilber:
                        posIconeJ1.x = 1040;
                        SDL_BlitSurface(iWilber, NULL, screen, &posIJ1);
                        SDL_BlitSurface(sIconeJ1, NULL, screen, &posIconeJ1);
                        break;
                }
                switch(choixPersoJ2)
                {
                    case droid:
                        posIconeJ2.x = 195;
                        SDL_BlitSurface(iDroid, NULL, screen, &posIJ2);
                        SDL_BlitSurface(sIconeJ2, NULL, screen, &posIconeJ2);
                        break;
                    case kit:
                        posIconeJ2.x = 470;
                        SDL_BlitSurface(iKit, NULL, screen, &posIJ2);
                        SDL_BlitSurface(sIconeJ2, NULL, screen, &posIconeJ2);
                        break;
                    case tux:
                        posIconeJ2.x = 795;
                        SDL_BlitSurface(iTux, NULL, screen, &posIJ2);
                        SDL_BlitSurface(sIconeJ2, NULL, screen, &posIconeJ2);
                        break;
                    case wilber:
                        posIconeJ2.x = 1090;
                        SDL_BlitSurface(iWilber, NULL, screen, &posIJ2);
                        SDL_BlitSurface(sIconeJ2, NULL, screen, &posIconeJ2);
                        break;
                }
                break;


        }
        SDL_Flip(screen);

    }



}
=======
#include "stats.h"
#include "sprites.h"
#include "menu.h"

void realMenu(SDL_Surface* screen)
{

    int menuPrin = jouerVies;
    int menuStage = stage1;
    int choixPersoJ1 = droid; int j1Pret = 0;
    int choixPersoJ2 = wilber; int j2Pret = 0;
    int etat = menuMain;

    SDL_Surface *menuPrin1, *menuPrin2, *menuPrin3, *menuPrin4, *menuPrin5;
    SDL_Surface *statistique, *commentJ, *credit;
    SDL_Rect pos = newRect(0, 0, 0, 0);
    menuPrin1 = IMG_Load("res/Menu/MenuJouerVies.jpg");
    menuPrin2 = IMG_Load("res/Menu/MenuJouerTemps.jpg");
    menuPrin3 = IMG_Load("res/Menu/MenuCommentJouer.jpg");
    menuPrin4 = IMG_Load("res/Menu/MenuStatistiques.jpg");
    menuPrin5 = IMG_Load("res/Menu/MenuCredits.jpg");
    statistique = IMG_Load("res/Menu/MenuWIP.jpg");
    commentJ = IMG_Load("res/Menu/MenuWIP.jpg");
    credit = IMG_Load("res/Menu/MenuWIP.jpg");


    SDL_Surface *menuStageS, *selectStage;
    SDL_Rect posSelectStage = newRect(674, 82, 0, 0);
    menuStageS = IMG_Load("res/Menu/StageSelect.jpg");
    selectStage = IMG_Load("res/Menu/CadreSelectStage.png");
    SDL_Surface *sStage1, *sStage2, *sStage3, *sStage4, *sStage5, *sStage6;
    SDL_Rect posStage = newRect(15, 131, 0, 0);
    sStage1 = IMG_Load("res/Menu/stage_01.jpg");
    sStage2 = IMG_Load("res/Menu/stage_02.jpg");
    sStage3 = IMG_Load("res/Menu/stage_03.jpg");
    sStage4 = IMG_Load("res/Menu/stage_04.jpg");
    sStage5 = IMG_Load("res/Menu/stage_05.jpg");
    sStage6 = IMG_Load("res/Menu/stage_06.jpg");

    SDL_Surface *sMenuChr, *sIconeJ1, *sIconeJ2;
    SDL_Surface *iDroid, *iKit, *iTux, *iWilber;
    SDL_Rect posIconeJ1 = newRect(145, 155, 0, 0);
    SDL_Rect posIconeJ2 = newRect(195, 155, 0, 0);
    SDL_Rect posIJ1 = newRect(300, 485, 0, 0);
    SDL_Rect posIJ2 = newRect(800, 485, 0, 0);
    sMenuChr = IMG_Load("res/Menu/ChrSelect.jpg");
    sIconeJ1 = IMG_Load("res/Menu/IconeJ1.png");
    sIconeJ2 = IMG_Load("res/Menu/IconeJ2.png");
    iDroid = IMG_Load(DROID_ICONE);
    iKit = IMG_Load(KIT_ICONE);
    iTux = IMG_Load(TUX_ICONE);
    iWilber = IMG_Load(WILBER_ICONE);



    int continuer = 1;
    SDL_Event event;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        if (etat == statistiques || etat == comment || etat == cred) {
                            etat = menuMain;
                        }
                        else if (etat == stageSelect) {
                            etat = menuMain;
                        }
                        else if (etat == chrSelect) {
                            etat = stageSelect;
                        }


                        else continuer = 0;
                        break;

                    case SDLK_w:
                        if (etat == menuMain)
                        {
                            switch(menuPrin)
                            {
                                case jouerTemps:
                                    menuPrin = jouerVies;
                                    break;
                                case stats:
                                    menuPrin = commentJouer;
                                    break;
                                case credits:
                                    menuPrin = stats;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == stageSelect)
                        {
                            switch(menuStage)
                            {
                                case stage3:
                                    menuStage = stage1;
                                    break;
                                case stage5:
                                    menuStage = stage3;
                                    break;
                                case stage4:
                                    menuStage = stage2;
                                    break;
                                case stage6:
                                    menuStage = stage4;
                                    break;
                                default:
                                    break;
                            }
                        }


                        break;

                    case SDLK_s:
                        if (etat == menuMain)
                        {
                            switch(menuPrin)
                            {
                                case jouerVies:
                                    menuPrin = jouerTemps;
                                    break;
                                case commentJouer:
                                    menuPrin = stats;
                                    break;
                                case stats:
                                    menuPrin = credits;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == stageSelect)
                        {
                            switch(menuStage)
                            {
                                case stage1:
                                    menuStage = stage3;
                                    break;
                                case stage3:
                                    menuStage = stage5;
                                    break;
                                case stage2:
                                    menuStage = stage4;
                                    break;
                                case stage4:
                                    menuStage = stage6;
                                    break;
                                default:
                                    break;
                            }
                        }


                        break;

                    case SDLK_a:
                          if (etat == menuMain)
                        {
                            switch(menuPrin)
                            {
                                case commentJouer:
                                    menuPrin = jouerVies;
                                    break;
                                case credits:
                                    menuPrin = jouerTemps;
                                    break;
                                case stats:
                                    menuPrin = jouerVies;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == stageSelect)
                        {
                            switch(menuStage)
                            {
                                case stage2:
                                    menuStage = stage1;
                                    break;
                                case stage4:
                                    menuStage = stage3;
                                    break;
                                case stage6:
                                    menuStage = stage5;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == chrSelect && j1Pret == 0)
                        {
                            switch(choixPersoJ1)
                            {
                                case wilber:
                                    choixPersoJ1 = tux;
                                    break;
                                case tux:
                                    choixPersoJ1 = kit;
                                    break;
                                case kit:
                                    choixPersoJ1 = droid;
                                    break;
                                default:
                                    break;
                            }
                        }

                        break;

                    case SDLK_d:
                        if (etat == menuMain)
                        {
                            switch(menuPrin)
                            {
                                case jouerVies:
                                    menuPrin = commentJouer;
                                    break;
                                case jouerTemps:
                                    menuPrin = credits;
                                    break;

                            }
                        }

                        else if (etat == stageSelect)
                        {
                            switch(menuStage)
                            {
                                case stage1:
                                    menuStage = stage2;
                                    break;
                                case stage3:
                                    menuStage = stage4;
                                    break;
                                case stage5:
                                    menuStage = stage6;
                                    break;
                                default:
                                    break;
                            }
                        }

                        else if (etat == chrSelect && j1Pret == 0)
                        {
                            switch(choixPersoJ1)
                            {
                                case tux:
                                    choixPersoJ1 = wilber;
                                    break;
                                case kit:
                                    choixPersoJ1 = tux;
                                    break;
                                case droid:
                                    choixPersoJ1 = kit;
                                    break;
                                default:
                                    break;
                            }
                        }

                        break;


                    case SDLK_RIGHT:
                        if (etat == chrSelect && j2Pret == 0)
                        {
                            switch(choixPersoJ2)
                            {
                                case tux:
                                    choixPersoJ2 = wilber;
                                    break;
                                case kit:
                                    choixPersoJ2 = tux;
                                    break;
                                case droid:
                                    choixPersoJ2 = kit;
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;

                    case SDLK_LEFT:
                        if (etat == chrSelect && j2Pret == 0)
                        {
                            switch(choixPersoJ2)
                            {
                                case wilber:
                                    choixPersoJ2 = tux;
                                    break;
                                case tux:
                                    choixPersoJ2 = kit;
                                    break;
                                case kit:
                                    choixPersoJ2 = droid;
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;



                    case SDLK_SPACE:
                        if (etat == menuMain && menuPrin == stats) {
                            etat = statistiques;
                        }
                        else if (etat == menuMain && menuPrin == credits) {
                            etat = cred;
                        }
                        else if (etat == menuMain && menuPrin == commentJouer) {
                            etat = comment;
                        }
                        else if (etat == menuMain && menuPrin == jouerVies) {
                            etat = stageSelect;
                        }
                         else if (etat == menuMain && menuPrin == jouerTemps) {
                            etat = stageSelect;
                        }
                        else if (etat == stageSelect) {
                            etat = chrSelect;
                        }
                        else if (etat == chrSelect && j1Pret == 0) {
                            j1Pret = 1;
                        }
                        break;
                    default:
                        break;

                    case SDLK_KP0:
                        if (etat == chrSelect && j2Pret == 0) {
                            j2Pret = 1;
                        }

                    case SDLK_RETURN:
                        if (etat == chrSelect && j1Pret && j2Pret) {
                                if (menuPrin == jouerVies)
                                    jouer(screen, stageSelect+1, false, true, choixPersoJ1, choixPersoJ2);
                                else if (menuPrin == jouerTemps)
                                    jouer(screen, stageSelect+1, false, false, choixPersoJ1, choixPersoJ2);

                        }
                }

            default:
                break;
        }



        switch(etat)
        {
            case menuMain:
                switch(menuPrin)
                {
                    case jouerVies:
                        SDL_BlitSurface(menuPrin1, NULL, screen, &pos);
                        break;
                    case jouerTemps:
                        SDL_BlitSurface(menuPrin2, NULL, screen, &pos);
                        break;
                    case commentJouer:
                        SDL_BlitSurface(menuPrin3, NULL, screen, &pos);
                        break;
                    case stats:
                        SDL_BlitSurface(menuPrin4, NULL, screen, &pos);
                        break;
                    case credits:
                        SDL_BlitSurface(menuPrin5, NULL, screen, &pos);
                        break;
                }
                break;

            case statistiques:
                SDL_BlitSurface(statistique, NULL, screen, &pos);
                break;

            case comment:
                SDL_BlitSurface(commentJ, NULL, screen, &pos);
                break;

            case cred:
                SDL_BlitSurface(credit, NULL, screen, &pos);
                break;

            case stageSelect:
                SDL_BlitSurface(menuStageS, NULL, screen, &pos);
                switch(menuStage)
                {
                    case stage1:
                        posSelectStage.x = 674; posSelectStage.y = 82;
                        SDL_BlitSurface(sStage1, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage2:
                        posSelectStage.x = 953; posSelectStage.y = 82;
                        SDL_BlitSurface(sStage2, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage3:
                        posSelectStage.x = 674; posSelectStage.y = 241;
                        SDL_BlitSurface(sStage3, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage4:
                        posSelectStage.x = 953; posSelectStage.y = 241;
                        SDL_BlitSurface(sStage4, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage5:
                        posSelectStage.x = 674; posSelectStage.y = 399;
                        SDL_BlitSurface(sStage5, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                    case stage6:
                        posSelectStage.x = 953; posSelectStage.y = 399;
                        SDL_BlitSurface(sStage6, NULL, screen, &posStage);
                        SDL_BlitSurface(selectStage, NULL, screen, &posSelectStage);
                        break;
                }
                break;

            case chrSelect:
                SDL_BlitSurface(sMenuChr, NULL, screen, &pos);
                switch(choixPersoJ1)
                {
                    case droid:
                        posIconeJ1.x = 145;
                        SDL_BlitSurface(iDroid, NULL, screen, &posIJ1);
                        SDL_BlitSurface(sIconeJ1, NULL, screen, &posIconeJ1);
                        break;
                    case kit:
                        posIconeJ1.x = 420;
                        SDL_BlitSurface(iKit, NULL, screen, &posIJ1);
                        SDL_BlitSurface(sIconeJ1, NULL, screen, &posIconeJ1);
                        break;
                    case tux:
                        posIconeJ1.x = 745;
                        SDL_BlitSurface(iTux, NULL, screen, &posIJ1);
                        SDL_BlitSurface(sIconeJ1, NULL, screen, &posIconeJ1);
                        break;
                    case wilber:
                        posIconeJ1.x = 1040;
                        SDL_BlitSurface(iWilber, NULL, screen, &posIJ1);
                        SDL_BlitSurface(sIconeJ1, NULL, screen, &posIconeJ1);
                        break;
                }
                switch(choixPersoJ2)
                {
                    case droid:
                        posIconeJ2.x = 195;
                        SDL_BlitSurface(iDroid, NULL, screen, &posIJ2);
                        SDL_BlitSurface(sIconeJ2, NULL, screen, &posIconeJ2);
                        break;
                    case kit:
                        posIconeJ2.x = 470;
                        SDL_BlitSurface(iKit, NULL, screen, &posIJ2);
                        SDL_BlitSurface(sIconeJ2, NULL, screen, &posIconeJ2);
                        break;
                    case tux:
                        posIconeJ2.x = 795;
                        SDL_BlitSurface(iTux, NULL, screen, &posIJ2);
                        SDL_BlitSurface(sIconeJ2, NULL, screen, &posIconeJ2);
                        break;
                    case wilber:
                        posIconeJ2.x = 1090;
                        SDL_BlitSurface(iWilber, NULL, screen, &posIJ2);
                        SDL_BlitSurface(sIconeJ2, NULL, screen, &posIconeJ2);
                        break;
                }
                break;


        }
        SDL_Flip(screen);

    }



}
>>>>>>> f268edab0736e9bbb261fe8b14bb32b69495a2df
