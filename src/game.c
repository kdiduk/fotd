#include <sys/ioctl.h>
#include <input.h>
#include <stdint.h>
#include <stdio.h>
#include "game.h"
#include "hud.h"
#include "level.h"
#include "player.h"
#include "titlescreen.h"

const char plot_str[] = "\x16\x01\x01"
        "    THE FOREST  SURROUNDING YOUR\n"
        "VILLAGE   HAD  ALWAYS   BEEN  AN\n"
        "IMPORTANT  SOURCE  OF  VITAL RE-\n"
        "SOURCES FOR THE VILLAGE\n"
        "\n"
        "BUT  RECENTLY,  THE  FOREST  HAS\n"
        "BECOME  HOSTILE  AND  DANGEROUS\n"
        "\n"
        "PEOPLE  GO MISSING  THERE AND AT\n"
        "NIGHT  TERRIBLE  CREATURES  FROM\n"
        "THE  FOREST  ATTACK  PEOPLE  AND\n"
        "THEIR  HOUSING\n"
        "\n"
        "SINCE THEN PEOPLE OF THE VILLAGE\n"
        "HAVE  GIVEN  THIS FOREST A NAME:\n"
        "\n"
        "   \"FOREST  OF  THE  DAMNED\"  \n"
        "\n"
        "IT'S A MATTER  OF HONOR  FOR YOU\n"
        "TO  SET OFF  TO THAT FOREST  AND\n"
        "TO ERADICATE  THE EVIL  RESIDING\n"
        "THERE  AND  SAVE  YOUR  VILLAGE\n";

static uint8_t inkey;

void game_init(void)
{
        ioctl(1, IOCTL_OTERM_PAUSE, 0);
        titlescreen_show();
}

void game_run(void)
{
        puts(plot_str);
        level_init();
        in_wait_key();
        in_wait_nokey();

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
