#include <stdio.h>
#include <string.h>
#include "display.h"
#include "viewport.h"

#define VIEWPORT_WIDTH  (32)
#define VIEWPORT_HEIGHT (20)
#define TILE_SIZE       (3) /* 2 bytes for ink control code, 1 for char */
#define BUFFER_ATTR_SIZE (3)
#define BUFFER_SIZE     ((VIEWPORT_WIDTH) * (VIEWPORT_HEIGHT) * (TILE_SIZE))

#define INVALID_MAX (32)

uint8_t invalid_x[INVALID_MAX];
uint8_t invalid_y[INVALID_MAX];
uint8_t invalid_count;
uint8_t invalid_full;

char display_buffer[BUFFER_ATTR_SIZE + BUFFER_SIZE+1];
char tile_buffer[TILE_SIZE*3 + 1];


static char* tile_at(uint8_t x, uint8_t y);

void viewport_init(void)
{
        invalid_count = 0;
        invalid_full = 1;
        display_buffer[BUFFER_SIZE] = '\0';
        display_buffer[0] = '\x16';
        display_buffer[1] = '\x01';
        display_buffer[2] = '\x03';
}

void viewport_at(uint8_t x, uint8_t y, char ch, uint8_t ink)
{
        char* tile = tile_at(x, y);
        tile[0] = '\x10';
        tile[1] = 0x30 + ink;
        tile[2] = ch;

        viewport_invalidate(x, y);
}

void viewport_invalidate(uint8_t x, uint8_t y)
{
        if (invalid_count < INVALID_MAX && !invalid_full) {
                invalid_x[invalid_count] = x;
                invalid_y[invalid_count] = y;
                invalid_count++;
        }
        else {
                /* too many characters to redraw,
                   so redraw the full screen on next draw call
                */
                invalid_count = 0;
                invalid_full = 1;
        }
}

void viewport_render(void)
{
        if (invalid_full) {
                puts(display_buffer);
                invalid_full = 0;
                invalid_count = 0;
                return;
        }

        for (uint8_t i = 0; i < invalid_count; i++) {
                tile_buffer[0] = '\x16';
                tile_buffer[1] = invalid_x[i] + 1;
                tile_buffer[2] = invalid_y[i] + 3;
                tile_buffer[3] = '\0';
                strncat(tile_buffer, tile_at(invalid_x[i], invalid_y[i]), 3);
                tile_buffer[6] = '\0';
                display_string(invalid_x[i], invalid_y[i]+2, tile_buffer);
        }
        invalid_count = 0;
}

static char* tile_at(uint8_t x, uint8_t y)
{
        return display_buffer + BUFFER_ATTR_SIZE + (y * VIEWPORT_WIDTH + x) * TILE_SIZE;
}

/* EOF */
