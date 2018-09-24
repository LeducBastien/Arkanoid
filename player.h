#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <SDL_image.h>
typedef struct s_player
{
    SDL_Rect* hitbox;
    int moving; // R / L ?
    SDL_Texture* p_texture;
    int t_heigth;
    int t_width;
} t_player;

t_player* init_player();
void destroy_player(t_player* player);
#endif


