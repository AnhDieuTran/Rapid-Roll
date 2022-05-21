#include "bar.h"

bar::bar()
{
    barRect.h = 5;
    barRect.w = 45;
    barRect.x = rand() % 375;
    barRect.y = 595;
}

void bar:: updatePos()
{
   barRect.x += 0;
   barRect.y -= step/2;
}