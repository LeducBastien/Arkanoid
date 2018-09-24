#include "world.h"
/*************************************************************************************************************************************************************/
int init_component()
{
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        printf("\tWorld - SLD Init... : FAILURE!\n");
        return -1;
    }
    else
        printf("World - SLD Init... : SUCCESS!\n");
    
    return 0;

}
/*************************************************************************************************************************************************************/
t_world* create_world(int width, int heigth, bool fullscreen, int rows, int columns)
{
    printf("Creating world...\n");
    t_world* world = malloc(sizeof(t_world));
    if(SDL_CreateWindowAndRenderer(width, heigth, fullscreen, &world->p_window, &world->p_renderer))
    {
        printf("\tWorld - Create Window... : FAILURE!\n");
        return NULL;
    }
    else
        printf("World - Create Window... : SUCCESS!\n");
    world->win_h = heigth;
    world->win_w = width;
    t_player* player = init_player();
    t_block** blocks = create_block(rows*columns);
    t_ball* ball = create_ball();
     
    player->hitbox->x = width/2;
    player->hitbox->y = heigth/1.1;
    world->blocks = blocks;
    world->speed = 1.0f;
    world->player = player;
    world->block_rows = rows;
    world->block_columns = columns;
    load_game_texture(world);
    ball->hitbox->x = (player->t_width / 2) + (ball->t_width / 2);
    ball->hitbox->y = (player->t_heigth - ball->t_heigth);
    world->ball = ball;
    init_level(world);
    return world;
}

/*************************************************************************************************************************************************************/
t_world* init_world(int heigth, int weigth, bool fullscreen, int block_rows, int blocks_columns)
{
    printf("Initiate world...\n");
    if(init_component())
        return NULL;
    t_world* world = create_world(heigth, weigth, fullscreen, block_rows, blocks_columns);
    return world;
}
/*************************************************************************************************************************************************************/
bool run(t_world* world, int delta_time)
{
    printf("Running world...\n");
    world->delta_time = delta_time;
    if(!event_occured(world))
        return false;
    render_world(world);
    render_lvl(world);
    render_ball(world);
    render_player(world);
    return true;
}
/*************************************************************************************************************************************************************/
bool event_occured(t_world* world)
{
    printf("Analyzing occured event...\n");

    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE] == 1)
    {
        return false;
    }

    else if(state[SDL_SCANCODE_SPACE] == 1)
    {
        printf("SPACE Reco !\n");
    }
    
    else if (state[SDL_SCANCODE_RIGHT] == 1)
    {
        
        if (world->player->hitbox->x > world->win_w - world->player->hitbox->w) 
            world->player->moving = 0;
        else
            world->player->moving = 1;
    }
    
    else if (state[SDL_SCANCODE_LEFT] == 1)
    {
        if(world->player->hitbox->x <= 0)
            world->player->moving = 0;
        else
            world->player->moving = -1;
    }
    else if(state[SDL_SCANCODE_GRAVE]){}
        //secret_code
    else
        world->player->moving = 0;
    return true;
}
/*************************************************************************************************************************************************************/
void render_world(t_world* world)
{

    printf("Rendering world...\n");
    SDL_SetRenderDrawColor(world->p_renderer, 0, 0, 0, 255);
    SDL_RenderClear(world->p_renderer);
}
/*************************************************************************************************************************************************************/
void render_player(t_world* world)
{
    printf("Rendering player...\n");
    if(world->player->moving)
        world->player->hitbox->x += world->player->moving * (world->delta_time*world->speed);
    else
        world->player->hitbox->x = world->player->hitbox->x;

    world->player->hitbox->w = world->player->t_width;
    world->player->hitbox->h = world->player->t_heigth;
    SDL_RenderCopyEx(world->p_renderer, world->player->p_texture, NULL, world->player->hitbox, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(world->p_renderer); 
}
/*************************************************************************************************************************************************************/
void load_game_texture(t_world* world)
{
    printf("Loading game texture...\n");
    world->ball->skin = IMG_LoadTexture(world->p_renderer, "ball.png");
    if(!world->ball->skin)    
        return;
    world->player->p_texture = IMG_LoadTexture(world->p_renderer, "bar.png");
    if(!world->player->p_texture)    
        return;
    SDL_QueryTexture(world->ball->skin, NULL, NULL, &world->ball->t_width, &world->ball->t_heigth);
    SDL_QueryTexture(world->player->p_texture, NULL, NULL, &world->player->t_width, &world->player->t_heigth);
}
/*************************************************************************************************************************************************************/
void check_collision(t_world* world)
{
    
    printf("Checking collision...\n");
    (void)world;
}
/*************************************************************************************************************************************************************/void game_over(t_world* world)
{
    printf("Gaming over...\n");
    SDL_SetRenderDrawColor(world->p_renderer, 255, 0, 0, 125);
    SDL_RenderClear(world->p_renderer);
}
/*************************************************************************************************************************************************************/
void init_level(t_world* world)
{
    SDL_Texture* sprite[3];
    (void)sprite;
    char c = '0';
    bool readable = true;
    FILE* file = fopen("One.lvl", "r");
    while(readable)
    {
        for(int x = 0 ; x < world->block_columns ; ++x)
        {
            for(int i = 0 ; i < world->block_rows ; ++i)
            {
                readable = fread(&c, sizeof(char), 1, file);
                if (c == 'b')
                {
                    printf("\n\ni : %d, x: %d, (x * 5) + i %d\n\n", i, x, (x * world->block_rows) + i);
                    world->blocks[(x * world->block_rows) + i]->hitbox->x = (25 * i) + 1;
                    world->blocks[(x * world->block_rows) + i]->hitbox->y = (15 * x) + 1;
                    world->blocks[(x * world->block_rows) + i]->hitbox->w = 25;
                    world->blocks[(x * world->block_rows) + i]->hitbox->h = 15;
                    world->blocks[(x * world->block_rows) + i]->alive = true;
                    world->blocks[(x * world->block_rows) + i]->blank = false;
                    printf("\n\nColor!\n\n");
                }
                if (c == '-')
                {
                    world->blocks[(x * world->block_rows) + i]->alive =true ;
                    world->blocks[(x * world->block_rows) + i]->blank = true;
                    world->blocks[(x * world->block_rows) + i]->hitbox->x = (25 * i)+1;
                    world->blocks[(x * world->block_rows) + i]->hitbox->y = (15 * x)+1;
                    world->blocks[(x * world->block_rows) + i]->hitbox->w = 25;
                    world->blocks[(x * world->block_rows) + i]->hitbox->h = 15;

                }
                
            }
        }
        
    }
}
void render_lvl(t_world* world)
{
    for (int i = 0 ; i < world->block_rows * world->block_columns ; ++i)
    {
        if(world->blocks[i]->alive && !world->blocks[i]->blank)
        {
            SDL_SetRenderDrawColor(world->p_renderer, 0, 0, 255, 255);
            SDL_RenderDrawRect(world->p_renderer, world->blocks[i]->hitbox);
        }
        else if(world->blocks[i]->alive && world->blocks[i]->blank)
        {
            SDL_SetRenderDrawColor(world->p_renderer, 0, 0, 0, 0);
            SDL_RenderDrawRect(world->p_renderer, world->blocks[i]->hitbox);
        }
    }

}

void render_ball(t_world* world)
{
    printf("Ball pos x(%d), y(%d)\n", world->ball->hitbox->x, world->ball->hitbox->y);
    SDL_RenderCopyEx(world->p_renderer, world->ball->skin, NULL, world->ball->hitbox, 0, NULL, SDL_FLIP_NONE);
}
