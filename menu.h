#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED



void realMenu(SDL_Surface* screen);

enum {jouerVies, jouerTemps, commentJouer, stats, credits, first};
enum {stage1, stage2, stage3, stage4, stage5, stage6};
enum {null, droid, kit, tux, wilber};
enum {menuMain, stageSelect, chrSelect, comment, statistiques, cred};

#endif // MENU_H_INCLUDED
