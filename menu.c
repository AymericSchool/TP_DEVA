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
#include "stats.h"
#include "sprites.h"
#include "menu.h"

void realMenu(SDL_Surface* screen)
{


    int menuPrin = first;
    int menuStage = stage1;
    int choixPersoJ1 = droid; int j1Pret = 0;
    int choixPersoJ2 = wilber; int j2Pret = 0;
    int etat = menuMain;

    SDL_Surface *menuPrin0, *menuPrin1, *menuPrin2, *menuPrin3, *menuPrin4, *menuPrin5;
    SDL_Surface *statistique, *commentJ, *credit;
    SDL_Rect pos = newRect(0, 0, 0, 0);
    menuPrin0 = IMG_Load("res/Menu/First_Frame_Menu.jpg");
    menuPrin1 = IMG_Load("res/Menu/MenuJouerVies.jpg");
    menuPrin2 = IMG_Load("res/Menu/MenuJouerTemps.jpg");
    menuPrin3 = IMG_Load("res/Menu/MenuCommentJouer.jpg");
    menuPrin4 = IMG_Load("res/Menu/MenuStatistiques.jpg");
    menuPrin5 = IMG_Load("res/Menu/MenuCredits.jpg");
    statistique = IMG_Load("res/Menu/stats.jpg");
    commentJ = IMG_Load("res/Menu/comment_jouer.jpg");
    credit = IMG_Load("res/Menu/Credits.jpg");

    TTF_Font *font;
    font = TTF_OpenFont(FONT_ECRAN_TITRE, 20);
    SDL_Color couleur_noir = {0, 0, 0, 0};

    // Changer le type du bot
    SDL_Surface *typeBot_s = NULL, *surfaceTextType = NULL;
    char textTextType[24] = "A : Changer Mode";
    SDL_Rect posTextType = newRect(720, 650, 0, 0);

    char* typeBot_c;
    typeBot_c = malloc(sizeof(char)*16);
    strcpy(typeBot_c, "Joueur");

    SDL_Rect typeBot_p;
    typeBot_p = newRect(720, 690, 0, 0);
    int type = 0;

    // Stats
    SDL_Surface
    *ds1, *ds2, *ds3, *ds4,
    *ks1, *ks2, *ks3, *ks4,
    *ts1, *ts2, *ts3, *ts4,
    *ws1, *ws2, *ws3, *ws4;

    SDL_Rect
    pds1, pds2, pds3, pds4,
    pks1, pks2, pks3, pks4,
    pts1, pts2, pts3, pts4,
    pws1, pws2, pws3, pws4;

    char* buffer;
    buffer = (char*)malloc(sizeof(char)*16);

    Player temp_droid, temp_kit, temp_tux, temp_wilber;
    // Stats Droid
    temp_droid.num = 1;
    loadStats(&temp_droid);

    sprintf(buffer, "%d", temp_droid.victory);
    ds1 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_droid.defeat);
    ds2 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_droid.distance_travelled);
    ds3 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_droid.big_hit);
    ds4 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    pds1 = newRect(400, 290, 0, 0);
    pds2 = newRect(400, 400, 0, 0);
    pds3 = newRect(400, 500, 0, 0);
    pds4 = newRect(400, 610, 0, 0);

    // Stats Kit
    temp_kit.num = 2;
    loadStats(&temp_kit);

    sprintf(buffer, "%d", temp_kit.victory);
    ks1 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_kit.defeat);
    ks2 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_kit.distance_travelled);
    ks3 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_kit.big_hit);
    ks4 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    pks1 = newRect(630, 290, 0, 0);
    pks2 = newRect(630, 400, 0, 0);
    pks3 = newRect(630, 500, 0, 0);
    pks4 = newRect(630, 610, 0, 0);

    // Stats Tux
    temp_tux.num = 3;
    loadStats(&temp_tux);

    sprintf(buffer, "%d", temp_tux.victory);
    ts1 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_tux.defeat);
    ts2 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_tux.distance_travelled);
    ts3 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_tux.big_hit);
    ts4 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    pts1 = newRect(850, 290, 0, 0);
    pts2 = newRect(850, 400, 0, 0);
    pts3 = newRect(850, 500, 0, 0);
    pts4 = newRect(850, 610, 0, 0);

    // Stats Wilber
    temp_wilber.num = 4;
    loadStats(&temp_wilber);

    sprintf(buffer, "%d", temp_wilber.victory);
    ws1 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_wilber.defeat);
    ws2 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_wilber.distance_travelled);
    ws3 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    sprintf(buffer, "%d", temp_wilber.big_hit);
    ws4 = TTF_RenderText_Blended(font, buffer , couleur_noir);

    pws1 = newRect(1050, 290, 0, 0);
    pws2 = newRect(1050, 400, 0, 0);
    pws3 = newRect(1050, 500, 0, 0);
    pws4 = newRect(1050, 610, 0, 0);










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

    SDL_Surface *sMenuChr, *sIconeJ1, *sIconeJ2, *fondNoir, *pret;
    SDL_Surface *iDroid, *iKit, *iTux, *iWilber;
    SDL_Rect posIconeJ1 = newRect(145, 155, 0, 0);
    SDL_Rect posIconeJ2 = newRect(195, 155, 0, 0);
    SDL_Rect posIJ1 = newRect(300, 485, 0, 0);
    SDL_Rect posIJ2 = newRect(800, 485, 0, 0);
    sMenuChr = IMG_Load("res/Menu/ChrSelect_2.jpg");
    sIconeJ1 = IMG_Load("res/Menu/IconeJ1.png");
    sIconeJ2 = IMG_Load("res/Menu/IconeJ2.png");
    fondNoir = IMG_Load("res/Menu/fondnoir.png");
    pret = IMG_Load("res/Menu/pret.png");
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
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        if (etat == statistiques || etat == comment || etat == cred) {
                            SDL_Delay(500);
                            etat = menuMain;
                        }
                        else if (etat == stageSelect) {
                            SDL_Delay(500);
                            etat = menuMain;
                        }
                        else if (etat == chrSelect) {
                            SDL_Delay(500);
                            etat = stageSelect;
                        }
                        else continuer = 0;
                        break;

                    case SDLK_w:
                        if (etat == menuMain)
                        {
                            switch(menuPrin)
                            {
                            case first:
                                menuPrin = jouerVies;
                                break;
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
                            case first:
                                menuPrin = jouerVies;
                                break;
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
                            case first:
                                menuPrin = jouerVies;
                                break;
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
                            case first:
                                menuPrin = jouerVies;
                                break;
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

                        case SDLK_q:
                            if (etat == chrSelect)
                            {
                                type = (type + 1) % 3;
                                SDL_Delay(200);
                            }
                            break;


                        case SDLK_r:
                            if (etat == statistiques) {
                                resetStats(&temp_droid);
                                resetStats(&temp_kit);
                                resetStats(&temp_tux);
                                resetStats(&temp_wilber);

                                // Stats Droid
                                sprintf(buffer, "%d", temp_droid.victory);
                                ds1 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_droid.defeat);
                                ds2 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_droid.distance_travelled);
                                ds3 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_droid.big_hit);
                                ds4 = TTF_RenderText_Blended(font, buffer , couleur_noir);

                                // Stats Kit
                                sprintf(buffer, "%d", temp_kit.victory);
                                ks1 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_kit.defeat);
                                ks2 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_kit.distance_travelled);
                                ks3 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_kit.big_hit);
                                ks4 = TTF_RenderText_Blended(font, buffer , couleur_noir);

                                // Stats Tux
                                sprintf(buffer, "%d", temp_tux.victory);
                                ts1 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_tux.defeat);
                                ts2 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_tux.distance_travelled);
                                ts3 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_tux.big_hit);
                                ts4 = TTF_RenderText_Blended(font, buffer , couleur_noir);

                                // Stats Wilber
                                sprintf(buffer, "%d", temp_wilber.victory);
                                ws1 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_wilber.defeat);
                                ws2 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_wilber.distance_travelled);
                                ws3 = TTF_RenderText_Blended(font, buffer , couleur_noir);
                                sprintf(buffer, "%d", temp_wilber.big_hit);
                                ws4 = TTF_RenderText_Blended(font, buffer , couleur_noir);

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

                    case SDLK_KP0:
                        if (etat == chrSelect && j2Pret == 0) {
                            j2Pret = 1;
                        }
                        break;

                    case SDLK_RETURN:
                        if (etat == chrSelect && j1Pret && j2Pret) {
                                if (menuPrin == jouerVies)
                                {
                                    if (type == 0){  jouer(screen, menuStage+1, false, true, choixPersoJ1, choixPersoJ2, 0); j1Pret = 0; j2Pret = 0, SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);}
                                    if (type == 1){  jouer(screen, menuStage+1, true, true, choixPersoJ1, choixPersoJ2, 1); j1Pret = 0; j2Pret = 0, SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);}
                                    if (type == 2){  jouer(screen, menuStage+1, true, true, choixPersoJ1, choixPersoJ2, 2); j1Pret = 0; j2Pret = 0, SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);}
                                }

                                else if (menuPrin == jouerTemps)
                                {
                                    if (type == 0){  jouer(screen, menuStage+1, false, false, choixPersoJ1, choixPersoJ2, 0); j1Pret = 0; j2Pret = 0, SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);}
                                    if (type == 1){  jouer(screen, menuStage+1, true, false, choixPersoJ1, choixPersoJ2, 1); j1Pret = 0; j2Pret = 0, SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);}
                                    if (type == 2){  jouer(screen, menuStage+1, true, false, choixPersoJ1, choixPersoJ2, 2); j1Pret = 0; j2Pret = 0, SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);}
                                }


                        }
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }



        switch(etat)
        {
            case menuMain:
                switch(menuPrin)
                {
                case first:
                    SDL_BlitSurface(menuPrin0, NULL, screen, &pos);
                    break;
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
                SDL_BlitSurface(ds1, NULL, screen, &pds1);
                SDL_BlitSurface(ds2, NULL, screen, &pds2);
                SDL_BlitSurface(ds3, NULL, screen, &pds3);
                SDL_BlitSurface(ds4, NULL, screen, &pds4);

                SDL_BlitSurface(ks1, NULL, screen, &pks1);
                SDL_BlitSurface(ks2, NULL, screen, &pks2);
                SDL_BlitSurface(ks3, NULL, screen, &pks3);
                SDL_BlitSurface(ks4, NULL, screen, &pks4);

                SDL_BlitSurface(ts1, NULL, screen, &pts1);
                SDL_BlitSurface(ts2, NULL, screen, &pts2);
                SDL_BlitSurface(ts3, NULL, screen, &pts3);
                SDL_BlitSurface(ts4, NULL, screen, &pts4);

                SDL_BlitSurface(ws1, NULL, screen, &pws1);
                SDL_BlitSurface(ws2, NULL, screen, &pws2);
                SDL_BlitSurface(ws3, NULL, screen, &pws3);
                SDL_BlitSurface(ws4, NULL, screen, &pws4);
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
                if (type == 0) sprintf(typeBot_c, "Joueur");
                if (type == 1) sprintf(typeBot_c, "Bot Facile");
                if (type == 2) sprintf(typeBot_c, "Bot Normal");
                typeBot_s = TTF_RenderText_Blended(font, typeBot_c, couleur_noir);
                surfaceTextType = TTF_RenderText_Blended(font, textTextType, couleur_noir);
                SDL_BlitSurface(surfaceTextType, NULL, screen, &posTextType);
                SDL_BlitSurface(typeBot_s, NULL, screen, &typeBot_p);
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
                if (j1Pret && j2Pret)
                {
                    SDL_BlitSurface(fondNoir, NULL, screen, &pos);
                    SDL_BlitSurface(pret, NULL, screen, &pos);
                }


                break;


        }

        SDL_Flip(screen);

    }



}
