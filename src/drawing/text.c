#include "text.h"

void DrawOutlinedText(Font font, const char* text, int x, int y, int size, Color textColor, Color outlineColor) {
    // Draw text with outline.
    DrawTextEx(font, text, (Vector2) {x - 3, y - 3}, size, 0, outlineColor);
    DrawTextEx(font, text, (Vector2) {x + 3, y - 3}, size, 0, outlineColor);
    DrawTextEx(font, text, (Vector2) {x - 3, y + 3}, size, 0, outlineColor);
    DrawTextEx(font, text, (Vector2) {x + 3, y + 3}, size, 0, outlineColor);
    DrawTextEx(font, text, (Vector2) {x, y - 3}, size, 0, outlineColor);
    DrawTextEx(font, text, (Vector2) {x, y + 3}, size, 0, outlineColor);
    DrawTextEx(font, text, (Vector2) {x - 3, y}, size, 0, outlineColor);
    DrawTextEx(font, text, (Vector2) {x + 3, y}, size, 0, outlineColor);
    DrawTextEx(font, text, (Vector2) {x, y}, size, 0, textColor);
}