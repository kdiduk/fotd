#include <sys/ioctl.h>
#include <input.h>
#include <stdint.h>
#include "game.h"
#include "hud.h"
#include "level.h"
#include "player.h"
#include "titlescreen.h"


static uint8_t inkey;

void game_init(void)
{
        ioctl(1, IOCTL_OTERM_PAUSE, 0);
        titlescreen_show();
}

void game_run(void)
{
        level_init();
        level_draw();
        hud_update();
        while (1) {
                in_wait_key();
                inkey = in_inkey();
                switch (inkey) {
                case 'y': case 'u':
                case 'h': case 'j': case 'k': case 'l':
                case 'b': case 'n':
                        level_player_move(inkey);
                        break;
                }
                level_draw();
                hud_update();
                in_wait_nokey();
        }
}

/* EOF */
