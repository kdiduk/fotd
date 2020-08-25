#include <arch/zx.h>
#include <input.h>
#include "game.h"
#include "player.h"


unsigned char inkey;

void game_init()
{
    zx_cls(PAPER_BLACK);
}

void game_run()
{
    player_draw();
    while (1) {
	in_wait_key();
	inkey = in_inkey();
	in_wait_nokey();
	switch (inkey) {
	case 'h':
	    if (player_posx() > 0) {
		player_move(west);
	    }
	    break;
	case 'j':
	    if (player_posy() < 21) {
		player_move(south);
	    }
	    break;
	case 'k':
	    if (player_posy() > 0) {
		player_move(north);
	    }
	    break;
	case 'l':
	    if (player_posx() < 31) {
		player_move(east);
	    }
	    break;
	}
	zx_cls(PAPER_BLACK);
	player_draw();
    }
}

