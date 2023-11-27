#include "debug.h"
#include "raylib.h"

void UpdateDebugInterface(GameState* gameState) {
    if (IsKeyPressed(KEY_F10) || IsKeyPressedRepeat(KEY_F10)) {
        gameState->debugState.debugShown = !gameState->debugState.debugShown;
    }
}

void DrawDebugInterface(GameState* gameState) {
    if (!gameState->debugState.debugShown) {
        return;
    }

    int leftVerticalOffset = 0;
    DrawNextLine(TextFormat("FPS: %d", GetFPS()), &leftVerticalOffset);
    DrawNextLine("Player stats", &leftVerticalOffset);
    DrawNextLine(TextFormat("  Speed: %d", gameState->player.speed), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Position: %f, %f", gameState->player.position.x, gameState->player.position.y), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Radius: %f", gameState->player.radius), &leftVerticalOffset);
    DrawNextLine("Map stats", &leftVerticalOffset);
    DrawNextLine(TextFormat("  Wall count: %d", gameState->map.wallCount), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Tile count: %d", gameState->map.tileCount), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Map position: %f, %f", gameState->map.area.x, gameState->map.area.y), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Map size: %f, %f", gameState->map.area.width, gameState->map.area.height), &leftVerticalOffset);
    DrawNextLine("Camera stats", &leftVerticalOffset);
    DrawNextLine(TextFormat("  Zoom level: %f", gameState->camera.zoom), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Rotation: %f", gameState->camera.rotation), &leftVerticalOffset);
}

void DrawNextLine(const char* text, int* offset) {
    DrawText(text, 10, 10 + *offset, 10, LIME);
    *offset += 14;
}