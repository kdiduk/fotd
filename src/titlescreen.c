#include <arch/zx.h>
#include <input.h>
#include <stdint.h>
#include <stdlib.h>
#include "display.h"
#include "titlescreen.h"

#define FRAMES (*((uint32_t*)0x5C78))

static uint16_t elapsed = 0;


void titlescreen_show(void)
{
        zx_cls(PAPER_BLACK);
        zx_border(PAPER_BLACK);

        display_ink(INK_WHITE);
        display_paper(INK_BLACK);

        display_string(4, 1, "+----------------------+");
        display_string(4, 2, "|                      |");
        display_string(4, 3, "| FOREST OF THE DAMNED |");
        display_string(4, 4, "|                      |");
        display_string(4, 5, "+----------------------+");

        display_string(7, 10, "HIT ENTER TO BEGIN");

        display_string(9, 17, "Version 0.0.1");
        display_string(2, 19, "Copyright 2020, Kirill Diduk");
        display_string(10, 20, "MIT License");

        while (!in_key_pressed(IN_KEY_SCANCODE_ENTER)) {
                ++elapsed;
        }

        srand(FRAMES + elapsed);
        zx_cls(PAPER_BLACK);
}

/* EOF */
