#include <stdio.h>
#include "hud.h"

void hud_update(void)
{
        printf("\x10\x37\x16\x01\x18" "YOU ENTER THE FOREST");
        printf("\x16\x01\x01" "HP:10/10          XP:2/10");
}

/* EOF */
