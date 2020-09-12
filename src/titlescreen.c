#include <arch/zx.h>
#include <input.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "titlescreen.h"

#define FRAMES (*((uint32_t*)0x5C78))

static uint16_t elapsed = 0;


void titlescreen_show(void)
{
    zx_cls(PAPER_BLACK);
    zx_border(PAPER_BLACK);

    puts("\x10\x37\x11\x30");
    puts("\x16\x0A\x01" "+----------+");
    puts("\x16\x0A\x02" "| VAGABOND |");
    puts("\x16\x0A\x03" "+----------+");

    puts("\x16\x02\x0A" "HIT ENTER TO BEGIN NEW JORNEY");

    puts("\x16\x0A\x12" "Version 0.0.1");
    puts("\x16\x03\x14" "Copyright 2020, Kirill Diduk");
    puts("\x16\x0B\x15" "MIT License");
    
    while (!in_key_pressed(IN_KEY_SCANCODE_ENTER)) {
	++elapsed;
    }

    srand(FRAMES + elapsed);
    zx_cls(PAPER_BLACK);
}

/* EOF */
