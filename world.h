#ifndef WORLD_H
#define WORLD_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "player.h"
#include "block.h"
#include "ball.h"

typedef struct s_world
{
    SDL_Window* p_window;
    SDL_Renderer* p_renderer;
    int win_h;
    int win_w;
    float speed;
    float delta_time;
    t_block** blocks;
    t_player* player;
    t_ball* ball;
    int block_rows;
    int block_columns;
} t_world;

t_world* init_world(int heigth, int weigth, bool fullscreen, int enemies_rows, int enemies_columns);
t_world* create_world(int width, int heigth, bool fullscreen, int enemies_rows, int enemies_columns);
void init_level(t_world* world);
int init_component();
bool run(t_world* world, int delta_time);
bool event_occured(t_world* world);
void render_world(t_world* world);
void render_player(t_world* world);
void load_game_texture(t_world* world);
void check_collision(t_world* world);
void game_over(t_world* world);
void render_lvl(t_world* world);
void render_ball(t_world* world);

#endif
