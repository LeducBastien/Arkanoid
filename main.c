#include "world.h"

int main()
{
    t_world* world = init_world(245, 240, false, 10, 3);
    bool watchdog = true;
    float time_old, time_new, delta_time;
    time_old = SDL_GetTicks();
    while(watchdog)
    {
        time_new = SDL_GetTicks();
        delta_time = time_new - time_old;
        watchdog = run(world, delta_time);
        time_old = time_new;
    }
    return 0;
}
