#ifndef NARROW_H_INCLUDED
#define NARROW_H_INCLUDED

void updateNarrow(SDL_Rect *zone, int arg);
void displayNarrow(SDL_Surface *screen, SDL_Rect *zone);
bool deadlyNarrow(Player *p, SDL_Rect *zone);

#endif // NARROW_H_INCLUDED
