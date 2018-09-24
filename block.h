#ifndef BLOCK_H
#define BLOCK_H
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
typedef enum e_type
{
    BREAKBLE = 0,
    UNBREAKABLE,
} t_type;

typedef struct s_block
{
    SDL_Rect* hitbox;
    SDL_Texture* skin;
    int heigth;
    int width;
    int pv;
    bool hit;
    bool alive;
    bool blank;
    int idx;
    t_type type;
} t_block;


t_block** create_block(int);
void destroy_block(t_block* block);

#endif
