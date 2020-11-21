#include <arch/zx.h>
#include <stdbool.h>
#include "display.h"
#include "forest.h"
#include "level.h"
#include "player.h"


#define LEVEL_ROWS (20)
#define INVALID_MAX (10)

static uint8_t invalid_x[INVALID_MAX];
static uint8_t invalid_y[INVALID_MAX];
static uint8_t invalid_count = 0;


static bool can_move(int8_t tx, int8_t ty);
static void draw_player(void);
static void draw_tile(uint8_t x, uint8_t y);

void level_init(void)
{
    forest_init();
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
    display_ink(INK_WHITE);
    display_char(player_posx(), player_posy(), '@');
}

static void draw_tile(uint8_t x, uint8_t y)
{
    switch (forest_tile(x, y)) {
    case tile_tree:
	display_ink(INK_GREEN);
        display_char(x, y, '*');
	break;
    case tile_ground:
	display_ink(INK_WHITE);
	display_char(x, y, '.');
	break;
    default:
        display_ink(INK_RED);
        display_char(x, y, '?');
	break;
    }
	
}

/* EOF */
