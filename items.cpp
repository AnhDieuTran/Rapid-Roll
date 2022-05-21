#include"items.h"

items::items()
{
    itemsRect.x = 0;
    itemsRect.y = 810;
    itemsRect.w = 18;
    itemsRect.h = 18;
}

void items:: updatePos()
{
   itemsRect.x += 0;
   itemsRect.y -= step/2;
}