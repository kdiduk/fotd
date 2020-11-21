#include <stdio.h>
#include "display.h"

#define AT_CTRL ('\x16')
#define INK_CTRL ('\x10')
#define PAPER_CTRL ('\x11')

#define CTRLBUF_LEN (6)


static char ctrlbuf[CTRLBUF_LEN];


void display_ink(uint8_t color)
{
    ctrlbuf[0] = INK_CTRL;
    ctrlbuf[1] = 0x30 + color;
    ctrlbuf[2] = '\0';
    puts(ctrlbuf);
}

void display_paper(uint8_t color)
{
    ctrlbuf[0] = PAPER_CTRL;
    ctrlbuf[1] = 0x30 + color;
    ctrlbuf[2] = '\0';
    puts(ctrlbuf);
}

void display_string(uint8_t x, uint8_t y, const char* str)
{
    ctrlbuf[0] = AT_CTRL;
    ctrlbuf[1] = x + 1;
    ctrlbuf[2] = y + 1;
    ctrlbuf[3] = '%';
    ctrlbuf[4] = 's';
    ctrlbuf[5] = '\0';
    printf(ctrlbuf, str);
}

void display_char(uint8_t x, uint8_t y, char c)
{
    ctrlbuf[0] = AT_CTRL;
    ctrlbuf[1] = x + 1;
    ctrlbuf[2] = y + 1;
    ctrlbuf[3] = c;
    ctrlbuf[4] = '\0';
    puts(ctrlbuf);
}
