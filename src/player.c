#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

#define MIN_POSX (0)
#define MAX_POSX (31)
#define MIN_POSY (1)
#define MAX_POSY (20)

static uint8_t posx = MIN_POSX;
static uint8_t posy = MIN_POSY;


void player_init(void)
{
}

void player_setpos(uint8_t x, uint8_t y)
{
        posx = x;
        posy = y;
}

void player_moveby(uint8_t dx, uint8_t dy)
{
        posx += dx;
        posy += dy;
}

uint8_t player_posx(void)
{
        return posx;
}

uint8_t player_posy(void)
{
        return posy;
}

/* EOF */
