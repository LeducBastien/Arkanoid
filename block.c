#include "block.h"

t_block** create_block(int nombre)
{

    t_block** block = malloc(sizeof(t_block*) * nombre);
    for (int x = 0 ; x < nombre ; ++x)
    {
        printf("\n\n%d\n\n", x);
        block[x] = malloc(sizeof(t_block));
        block[x]->hitbox = malloc(sizeof(SDL_Rect));
        block[x]->hit = false;
        block[x]->pv = 1;
        block[x]->heigth = 0;
        block[x]->width = 0;
        block[x]->alive = true;
        block[x]->idx = x;
        block[x]->blank = false;
    }
    return block;
}
void destroy_block(t_block* block)
{
    free(block->skin);
    free(block->hitbox);
    free(block);
}

/*void destroy_wall(t_wall* wall)
{

}*/
