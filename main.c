/*
main.c
programme principal
charge le menu, et lance le jeu
*/

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
#include "menu.h"


int main(int argc, char *argv[])
{

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
    // Initialisation de TTF
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF");
        exit(EXIT_FAILURE);
    }


    // Bot
    bool bot = true;

    // Mode
    bool mode = true;
    /* true : vies, false : temps*/

    // Creation des surfaces
    SDL_Surface *screen = NULL, *menu = NULL, *text = NULL, *ver = NULL, *bot_surface = NULL;

    // Police
    TTF_Font *font = NULL, *font2 = NULL;
    font = TTF_OpenFont(FONT_ECRAN_TITRE, 30);
    font2 = TTF_OpenFont(FONT_ECRAN_TITRE, 10);

    // Couleur
    SDL_Color couleur = {255, 255, 255, 0};

    // Position du texte
    SDL_Rect posText = newRect(300, 500, 0, 0);
    SDL_Rect posVer = newRect(1140, 700, 0, 0);
    SDL_Rect posBot = newRect(500, 700, 0, 0);
    char botText[32];

    // Textes
    text = TTF_RenderText_Blended(font, "Appuyez sur la touche RETURN", couleur);
    ver = TTF_RenderText_Solid(font2, VERSION, couleur);
//

    int temps = 0, tempsIni = 0, aff = 0;

    // Creation du rect et surface du menu
    SDL_Rect posMenu;
    posMenu.x = 0; posMenu.y = 0;
    menu = IMG_Load("res/menu.png");

    // Variable de boucle
    int continuer = 1;

    // Ouverture de l'ecran
    screen = SDL_SetVideoMode(WIDTH_GAME, HEIGHT_GAME, 32, SDL_FULLSCREEN | SDL_DOUBLEBUF);
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 255, 255, 255));
    SDL_WM_SetCaption(TITLE_GAME, NULL);


    SDL_Event event;

    while(continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                // On arrete
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        // On arrete
                        continuer = 0;
                        break;
                    case SDLK_q:
                        // On lance le jeu
                        jouer(screen, 1, bot, mode, 3, 4);
                        SDL_BlitSurface(menu, NULL, screen, &posMenu);
                        SDL_BlitSurface(ver, NULL, screen, &posVer);
                        SDL_Flip(screen);
                        SDL_Delay(800);
                        break;
                    case SDLK_b:
                        // On lance le jeu avec stage 2
                        jouer(screen, 2, bot, mode, 1, 2);
                        SDL_BlitSurface(menu, NULL, screen, &posMenu);
                        SDL_BlitSurface(ver, NULL, screen, &posVer);
                        SDL_Flip(screen);
                        SDL_Delay(800);
                        break;
                    case SDLK_c:
                        // On lance le jeu avec stage 3
                        jouer(screen, 3, bot, mode, 1, 2);
                        SDL_BlitSurface(menu, NULL, screen, &posMenu);
                        SDL_BlitSurface(ver, NULL, screen, &posVer);
                        SDL_Flip(screen);
                        SDL_Delay(800);
                        break;
                    case SDLK_o:
                        // On active le bot
                        bot = true;
                        break;
                    case SDLK_n:
                        // On desactive le bot
                        bot = false;
                        break;
                    case SDLK_RETURN:
                        realMenu(screen);
                        SDL_BlitSurface(menu, NULL, screen, &posMenu);
                        SDL_BlitSurface(ver, NULL, screen, &posVer);
                        SDL_Flip(screen);
                        SDL_Delay(800);
                    default:
                        break;
                }
                break;
        }

        // On affiche le menu (si le jeu n'est pas lance)
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, screen, &posMenu);
        SDL_BlitSurface(ver, NULL, screen, &posVer);
        if (bot) sprintf(botText, "IA activee (n pour desactiver)");
        else sprintf(botText, "IA desactivee (o pour activer)");
        bot_surface = TTF_RenderText_Solid(font2, botText, couleur);
        SDL_BlitSurface(bot_surface, NULL, screen, &posBot);

        // Clignotement du texte
        tempsIni = SDL_GetTicks();
        if (tempsIni - temps > 500 && aff == 0)
        {
            aff = 1;
            temps = tempsIni;
        }
        if (tempsIni - temps > 500 && aff == 1)
        {
            SDL_BlitSurface(text, NULL, screen, &posText);
            if(tempsIni - temps > 1500)
            {
                aff = 0;
                temps = tempsIni;
            }
        }

        // Affichage
        SDL_Flip(screen);
    }

    // Quit
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
