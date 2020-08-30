#include <arch/zx.h>
#include <stdbool.h>
#include <stdio.h>
#include "forest.h"
#include "level.h"
#include "player.h"


#define AT_CTRL ('\x16')
#define INK_CTRL ('\x10')
#define PAPER_CTRL ('\x11')
#define LEVEL_ROWS (20)
#define INVALID_MAX (10)
#define CTRLBUF_LEN (6)

static uint8_t invalid_x[INVALID_MAX];
static uint8_t invalid_y[INVALID_MAX];
static uint8_t invalid_count = 0;
static char ctrlbuf[CTRLBUF_LEN];


static void set_ink_paper(uint8_t ink, uint8_t paper);
static bool can_move(int8_t tx, int8_t ty);
static void draw_player(void);
static void draw_tile(uint8_t x, uint8_t y);

void level_init(void)
{
    set_ink_paper(INK_WHITE, INK_BLACK);
    for (uint8_t y = 0; y < FOREST_HEIGHT; ++y) {
	for (uint8_t x = 0; x < FOREST_WIDTH; ++x) {
	    draw_tile(x, y);
	}
    }

    player_setpos(forest_entrance_x(), forest_entrance_y());
    draw_player();
}

void level_draw(void)
{
    for (int i = 0; i < invalid_count; ++i) {
	draw_tile(invalid_x[i], invalid_y[i]);
    }
    invalid_count = 0;

    draw_player();
}

void level_player_move(uint8_t direction)
{
    int8_t dx = 0;
    int8_t dy = 0;
    switch (direction) {
    case 'y':
	dx--;
	dy--;
	break;
    case 'u':
	dx++;
	dy--;
	break;
    case 'h':
	dx--;
	break;
    case 'k':
	dy--;
	break;
    case 'j':
	dy++;
	break;
    case 'l':
	dx++;
	break;
    case 'b':
	dx--;
	dy++;
	break;
    case 'n':
	dx++;
	dy++;
	break;
    }


    if (can_move(player_posx() + dx, player_posy() + dy)) {
	invalid_x[invalid_count] = player_posx();
	invalid_y[invalid_count] = player_posy();
	invalid_count++;

	player_moveby(dx, dy);
    }
}


static void set_ink_paper(uint8_t ink, uint8_t paper)
{
    ctrlbuf[0] = INK_CTRL;
    ctrlbuf[1] = 0x30 + ink;
    ctrlbuf[2] = PAPER_CTRL;
    ctrlbuf[3] = 0x30 + paper;
    ctrlbuf[4] = '\0';
    puts(ctrlbuf);
}

static bool can_move(int8_t tx, int8_t ty)
{
    if (tx < 0 || tx > 31) {
	return false;
    }

    if (ty < 1 || ty > 20) {
	return false;
    }

    switch (forest_tile(tx, ty)) {
    case tile_tree:
	return false;
    case tile_ground:
	return true;
    }

    return false;
}

static void draw_player(void)
{
    set_ink_paper(INK_WHITE, INK_BLACK);
    ctrlbuf[0] = AT_CTRL;
    ctrlbuf[1] = player_posx() + 1;
    ctrlbuf[2] = player_posy() + 2;
    ctrlbuf[3] = '@';
    ctrlbuf[4] = '\0';
    puts(ctrlbuf);
}

static void draw_tile(uint8_t x, uint8_t y)
{
    char tile = '?';
    switch (forest_tile(x, y)) {
    case tile_tree:
	set_ink_paper(INK_GREEN, INK_BLACK);
	tile = '*';
	break;
    case tile_ground:
	set_ink_paper(INK_WHITE, INK_BLACK);
	tile = '.';
	break;
    default:
	set_ink_paper(INK_WHITE, INK_BLACK);
	break;
    }
	
    ctrlbuf[0] = AT_CTRL;
    ctrlbuf[1] = x+1;
    ctrlbuf[2] = y+2;
    ctrlbuf[3] = tile;
    ctrlbuf[4] = '\0';

    puts(ctrlbuf);
}

/* EOF */
