#include <stdbool.h>
#include <stdio.h>
#include "level.h"
#include "player.h"


#define AT_CTRL ('\x16')
#define INK_PAPER_CTRLSTR "\x10\x07" "\x11\x30"
#define LEVEL_ROWS (20)
#define INVALID_MAX (10)
#define CTRLBUF_LEN (6)

char* data[LEVEL_ROWS] = {
    "  --------------                ",
    "  |............|                ",
    "  |.<..........|   ########     ",
    "  |............|  ##      #     ",
    "  |............|  #  -----+---- ",
    "  |............+###  |........| ",
    "  |............|     |........| ",
    "  --+-----------     |........| ",
    "    #            -----........| ",
    "  ### --------   |............| ",
    "  #   |......| ##+............| ",
    "--+----......+## |............| ",
    "|............|   --+----------- ",
    "|............|     ###          ",
    "-------+------       ###        ",
    "       #          -----+------- ",
    "  -----+-------   |...........| ",
    "  |...........| ##+........>..| ",
    "  |...........+## |...........| ",
    "  -------------   ------------- "
};

static uint8_t invalid_x[INVALID_MAX];
static uint8_t invalid_y[INVALID_MAX];
static uint8_t invalid_count = 0;
static char ctrlbuf[CTRLBUF_LEN];


static bool can_move(int8_t tx, int8_t ty);

void level_init(void)
{
    puts(INK_PAPER_CTRLSTR);
    puts("\x16\x01\x01");
    for (uint8_t i = 0; i < LEVEL_ROWS; ++i) {
	printf(data[i]);
    }

    player_setpos(3, 3);
    ctrlbuf[0] = AT_CTRL;
    ctrlbuf[1] = player_posx() + 1;
    ctrlbuf[2] = player_posy() + 1;
    ctrlbuf[3] = '@';
    ctrlbuf[4] = '\0';
    puts(ctrlbuf);
}

void level_draw(void)
{
    puts(INK_PAPER_CTRLSTR);
    ctrlbuf[0] = AT_CTRL;
    ctrlbuf[4] = '\0';
    for (int i = 0; i < invalid_count; ++i) {
	ctrlbuf[1] = invalid_x[i] + 1;
	ctrlbuf[2] = invalid_y[i] + 1;
	ctrlbuf[3] = data[invalid_y[i]-1][invalid_x[i]];
	puts(ctrlbuf);
    }
    invalid_count = 0;

    ctrlbuf[1] = player_posx() + 1;
    ctrlbuf[2] = player_posy() + 1;
    ctrlbuf[3] = '@';
    ctrlbuf[4] = '\0';
    puts(ctrlbuf);
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

    switch (data[ty-1][tx]) {
    case '.':
    case '#':
    case '+':
    case '<':
    case '>':
	return true;
    }

    return false;
}

/* EOF */
