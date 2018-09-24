#include "player.h"
t_player* init_player()
{
    t_player* player = malloc(sizeof(t_player));
    player->hitbox = malloc(sizeof(SDL_Rect));
    player->moving = 0;
    return player;
}

void destroy_player(t_player* player)
{
    free(player->hitbox);
    free(player);
}


