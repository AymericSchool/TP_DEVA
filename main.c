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

    // Creation des surfaces
    SDL_Surface *screen = NULL, *menu = NULL;

    // Creation du rect et surface du menu
    SDL_Rect posMenu;
    posMenu.x = 0; posMenu.y = 0;
    menu = IMG_Load("res/menu.jpg");

    // Variable de boucle
    int continuer = 1;

    // Ouverture de l'ecran
    screen = SDL_SetVideoMode(WIDTH_GAME,HEIGHT_GAME,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 255, 255, 255));
    SDL_WM_SetCaption(TITLE_GAME, NULL);

    SDL_Event event;

    while(continuer)
    {
        SDL_WaitEvent(&event);
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
                    case SDLK_RETURN:
                        // On lance le jeu
                        jouer(screen);
                        break;
                    default:
                        break;
                }
                break;
        }

        // On affiche le menu (si le jeu n'est pas lance)
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, screen, &posMenu);
        SDL_Flip(screen);
    }

    // Quit
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
