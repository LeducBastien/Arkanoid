#include "ball.h"

t_ball* create_ball()
{
    t_ball* ball = malloc(sizeof(t_ball));
    ball->hitbox = malloc(sizeof(SDL_Rect));
    return ball;
}
