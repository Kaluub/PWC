#pragma once

#include "raylib.h"

typedef struct Fonts {
    Font tahoma;
    Font tahomaBold;
} Fonts;

Fonts LoadFonts();
