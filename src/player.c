#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

#define AT_CTRL ('\x16')
#define INK_PAPER_CTRLSTR "\x10\x07" "\x11\x30"
#define CTRLBUF_LEN (8)
#define PLAYER_CHAR ('@')

char ctrlbuf[CTRLBUF_LEN];
static uint8_t posx = 0;
static uint8_t posy = 0;


void player_init(void)
{
}

void player_setpos(uint8_t x, uint8_t y)
{
    posx = x;
    posy = y;
}

uint8_t player_posx(void)
{
    return posx;
}

uint8_t player_posy(void)
{
    return posy;
}

void player_move(enum direction d)
{
    switch (d) {
    case north:
	posy--;
	break;
    case south:
	posy++;
	break;
    case west:
	posx--;
	break;
    case east:
	posx++;
	break;
    case nortwest:
	posx--;
	posy--;
	break;
    case northeast:
	posx++;
	posy--;
	break;
    case southwest:
	posx--;
	posy--;
	break;
    case southeast:
	posx++;
	posy--;
	break;
    }
}

void player_draw(void)
{
    puts(INK_PAPER_CTRLSTR);

    ctrlbuf[0] = AT_CTRL;
    ctrlbuf[1] = posx+1;
    ctrlbuf[2] = posy+1;
    ctrlbuf[3] = PLAYER_CHAR;
    ctrlbuf[4] = '\0';

    puts(ctrlbuf);
}
