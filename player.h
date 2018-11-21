#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

// Touches Clavier J1
#define J1_UP                  SDLK_w
#define J1_RIGHT            SDLK_d
#define J1_LEFT                 SDLK_a
#define J1_ATTACK           SDLK_SPACE

// Touches Clavier J2
#define J2_UP                  SDLK_UP
#define J2_RIGHT            SDLK_RIGHT
#define J2_LEFT                 SDLK_LEFT
#define J2_ATTACK           SDLK_KP0

// Constante de combat
#define BIG_ATTACK      50



#include <stdbool.h>

// Type Player
typedef struct {
    SDL_Surface *surface;
    SDL_Rect hitbox;
    char* type;
    int h;
    int jump;
    int speed;

    int up;
    int right;
    int left;
    int attack;

    int hp;
    int hpMax;
    int canAttack;
    int buffer;
    int estPropulse;
    int forcePropulsion;
    int sensPropulsion;

} Player;

// Collisions
bool colide (SDL_Rect obj, SDL_Rect* oth);
bool colidePlayers (Player *p1, Player *p2);
// Deplacements
void moving(Player* p, SDL_Rect* obstacles);
// Combats
void hit(Player *p1, Player *p2);
// Creation de joueur
Player newPlayer(SDL_Surface *surface, SDL_Rect hitbox, char* type);


#endif // PLAYER_H_INCLUDED
