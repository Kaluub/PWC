#include <malloc.h>
#include "fonts.h"

Fonts LoadFonts() {
    Fonts fonts;
    fonts.tahoma = LoadFont("assets/font/Tahoma.ttf");
    fonts.tahomaBold = LoadFontEx("assets/font/TahomaBold.ttf", 48, NULL, 0);
    return fonts;
}