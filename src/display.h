/*
 * Contains functions to control the output of the text on the screen.
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>


/*
 * parameter 'color' - one of the constants `INK_*` from <arch/zx.h>
 */
void display_ink(uint8_t color);

/*
 * parameter 'color' - one of the constants `INK_*` from <arch/zx.h>
 */
void display_paper(uint8_t color);

void display_string(uint8_t x, uint8_t y, const char* str);

void display_char(uint8_t x, uint8_t y, char c);

#endif /* DISPLAY_H */
