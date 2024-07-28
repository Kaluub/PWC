#include <malloc.h>
#include "fonts.h"

Fonts LoadFonts() {
    Fonts fonts;
    fonts.tahoma = LoadFontEx("assets/font/Tahoma.ttf", 70, NULL, 0);
    fonts.tahomaBold = LoadFontEx("assets/font/TahomaBold.ttf", 96, NULL, 0);
    return fonts;
}