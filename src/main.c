#include <arch/zx.h>
#include "player.h"

int main()
{
    zx_cls(PAPER_BLACK);
    player_draw();
    return 0;
}
