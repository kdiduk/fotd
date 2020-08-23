#include <stdint.h>
#include <stdio.h>
#include "player.h"

uint8_t posx = 0;
uint8_t posy = 0;


#define INK_WHITE_CTRL "\x10\x07"
#define PAPER_BLACK_CTRL "\x11\x30"

void player_init(void)
{
}

void player_draw(void)
{
    puts("\x16\x0A\x0C" INK_WHITE_CTRL PAPER_BLACK_CTRL "@");
}

