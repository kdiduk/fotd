#include <arch/zx.h>
#include <stdbool.h>
#include "display.h"
#include "forest.h"
#include "level.h"
#include "player.h"


#define LEVEL_WIDTH (32)
#define LEVEL_HEIGHT (20)
#define INVALID_MAX (10)

static uint8_t invalid_x[INVALID_MAX];
static uint8_t invalid_y[INVALID_MAX];
static uint8_t invalid_count = 0;

static bool screen_invalid;
static uint8_t xleft;
static uint8_t ytop;

static void center_screen(void);
static void redraw_level(void);
static bool can_move(int8_t dx, int8_t dy);
static void draw_player(void);
static void draw_tile(uint8_t x, uint8_t y);

void level_init(void)
{
        forest_init();
        player_setpos(forest_spawnx(), forest_spawny());
        center_screen();
}

void level_draw(void)
{
        if (screen_invalid) {
                redraw_level();
                screen_invalid = false;
        }
        else {
                for (int i = 0; i < invalid_count; ++i) {
                        draw_tile(invalid_x[i], invalid_y[i]);
                }
                invalid_count = 0;
        }

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

        if (can_move(dx, dy)) {
                invalid_x[invalid_count] = player_posx();
                invalid_y[invalid_count] = player_posy();
                invalid_count++;

                player_moveby(dx, dy);
                if (player_posx() == xleft
                    || player_posx() == xleft + LEVEL_WIDTH-1
                    || player_posy() == ytop
                    || player_posy() == ytop + LEVEL_HEIGHT-1) {
                        center_screen();
                        invalid_count = 0;
                }
        }
}

static void center_screen(void)
{
        if (player_posx() < LEVEL_WIDTH/2) {
                xleft = 0;
        }
        else if (player_posx() < forest_width() - LEVEL_WIDTH/2) {
                xleft = player_posx() - LEVEL_WIDTH/2;
        }
        else {
                xleft = forest_width() - LEVEL_WIDTH;
        }

        if (player_posy() < LEVEL_HEIGHT/2) {
                ytop = 0;
        }
        else if (player_posy() < forest_height() - LEVEL_HEIGHT/2) {
                ytop = player_posy() - LEVEL_HEIGHT/2;
        }
        else {
                ytop = forest_height() - LEVEL_HEIGHT;
        }

        screen_invalid = true;
}

static void redraw_level(void)
{
        zx_cls(PAPER_BLACK);

        uint8_t y1 = ytop;
        uint8_t y2 = y1 + LEVEL_HEIGHT;
        uint8_t x1 = xleft;
        uint8_t x2 = x1 + LEVEL_WIDTH;

        for (uint8_t y = y1; y < y2; ++y) {
                for (uint8_t x = x1; x < x2; ++x) {
                        draw_tile(x, y);
                }
        }
}

static bool can_move(int8_t dx, int8_t dy)
{
        if (dx < 0 && player_posx() == 0) {
                return false;
        }
        if (dx > 0 && player_posx() == forest_width() - 1) {
                return false;
        }

        if (dy < 0 && player_posy() == 0) {
                return false;
        }
        if (dy > 0 && player_posy() == forest_height() - 1) {
                return false;
        }

        switch (forest_tile(player_posx() + dx, player_posy() + dy)) {
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
        display_char(player_posx()-xleft, player_posy()-ytop+2, '@');
}

static void draw_tile(uint8_t x, uint8_t y)
{
        switch (forest_tile(x, y)) {
        case tile_tree:
                display_ink(INK_GREEN);
                display_char(x-xleft, y-ytop+2, '*');
                break;
        case tile_ground:
                display_ink(INK_WHITE);
                display_char(x-xleft, y-ytop+2, '.');
                break;
        default:
                display_ink(INK_RED);
                display_char(x-xleft, y-ytop+2, '?');
                break;
        }

}

/* EOF */
