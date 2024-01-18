#include "text.h"

void DrawOutlinedText(const char* text, int x, int y, int size, Color textColor, Color outlineColor) {
    // Draw text with outline. TODO: font used?
    DrawText(text, x - 2, y - 2, size, outlineColor);
    DrawText(text, x + 2, y - 2, size, outlineColor);
    DrawText(text, x - 2, y + 2, size, outlineColor);
    DrawText(text, x + 2, y + 2, size, outlineColor);
    DrawText(text, x, y - 2, size, outlineColor);
    DrawText(text, x, y + 2, size, outlineColor);
    DrawText(text, x - 2, y, size, outlineColor);
    DrawText(text, x + 2, y, size, outlineColor);
    DrawText(text, x, y, size, textColor);
}