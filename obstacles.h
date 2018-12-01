#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED

SDL_Rect newRect(int x, int y, int h, int w);

typedef struct {
    SDL_Rect *obstacles;
    int nbObstacles;
    SDL_Surface* image;
    SDL_Rect position;

    int x1, y1, x2, y2;

} Stage;

Stage loadStage(int s);

#endif // OBSTACLES_H_INCLUDED
