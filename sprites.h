/*
sprites.h
stocke les chemins des images du jeu
*/

#ifndef SPRITES_H_INCLUDED
#define SPRITES_H_INCLUDED

// Images
#define BLUE_BOX            "res/box.jpg"
#define GREEN_BOX          "res/green_box.jpg"
#define STAGE_01                "res/stage_01.jpg"
#define STAGE_02                "res/stage_02.jpg"
#define STAGE_03                "res/stage_03.jpg"
#define STAGE_04                "res/stage_04.jpg"
#define STAGE_05                "res/stage_05.jpg"
#define STAGE_06                "res/stage_06.jpg"

// Droid
#define DROID_ICONE     "res/droid/droid_icone.jpg"
#define DROID_00            "res/droid/droid_000.png"
#define DROID_09            "res/droid/droid_009.png"
#define DROID_13            "res/droid/droid_013.png"
#define DROID_15            "res/droid/droid_015.png"

// Tux
#define TUX_ICONE     "res/tux/tux_icone.jpg"
#define TUX_00            "res/tux/tux_000.png"
#define TUX_09            "res/tux/tux_009.png"
#define TUX_13            "res/tux/tux_013.png"
#define TUX_15            "res/tux/tux_015.png"

// Wilber
#define WILBER_ICONE     "res/wilber/wilber_icone.jpg"
#define WILBER_00            "res/wilber/wilber_000.png"
#define WILBER_09            "res/wilber/wilber_009.png"
#define WILBER_13            "res/wilber/wilber_013.png"
#define WILBER_15            "res/wilber/wilber_015.png"

// Kit
#define KIT_ICONE     "res/kit/kit_icone.jpg"
#define KIT_00            "res/kit/kit_000.png"
#define KIT_09            "res/kit/kit_009.png"
#define KIT_13            "res/kit/kit_013.png"
#define KIT_15            "res/kit/kit_015.png"

// Smash Counter
#define SMASH_1         "res/smash_count/smash_1.png"
#define SMASH_2         "res/smash_count/smash_2.png"
#define SMASH_3         "res/smash_count/smash_3.png"
#define SMASH_4         "res/smash_count/smash_4.png"
#define SMASH_5         "res/smash_count/smash_5.png"
#define SMASH_6         "res/smash_count/smash_6.png"
#define SMASH_7         "res/smash_count/smash_7.png"
#define SMASH_8         "res/smash_count/smash_8.png"
#define SMASH_9         "res/smash_count/smash_9.png"

void affFond(SDL_Surface* screen, SDL_Surface* fond, SDL_Rect* rect);

#endif // SPRITES_H_INCLUDED
