#ifndef BALL_H
#define BALL_H
#include "SDL.h"

typedef struct s_ball
{
    SDL_Rect* hitbox;
    SDL_Texture* skin;
    int t_width;
    int t_heigth;
} t_ball;

t_ball* create_ball();
#endif
