#pragma once

#define IN_BOUNDS(xcoord, ycoord, rect) xcoord > rect.x && xcoord < rect.w && ycoord > rect.y && ycoord < rect.h