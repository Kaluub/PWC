#include "debug.h"
#include "config.h"
#include "raylib.h"
#include <string.h>

void UpdateDebugInterface(GameState* gameState) {
    DebugState* debugState = &gameState->debugState;
    if (IsKeyPressed(KEY_F10) || IsKeyPressedRepeat(KEY_F10)) {
        debugState->debugShown = !debugState->debugShown;
    }
    if (IsKeyPressed(KEY_F6) || IsKeyPressedRepeat(KEY_F6)) {
        debugState->showWallBounds = !debugState->showWallBounds;
    }

    if (debugState->debugShown) {
        if (IsKeyPressed(KEY_RIGHT)) {
            debugState->selectedAbilityType += 1;
        }
        if (IsKeyPressed(KEY_LEFT) && debugState->selectedAbilityType > 0) {
            debugState->selectedAbilityType -= 1;
        }
        if (IsKeyPressed(KEY_F1)) {
            gameState->player.abilityOneType = (AbilityType) debugState->selectedAbilityType;
            memset(&gameState->player.abilityOne, 0, sizeof(Ability));
            gameState->player.abilityOne.data.level = 1;
        }
        if (IsKeyPressed(KEY_F2)) {
            gameState->player.abilityTwoType = (AbilityType) debugState->selectedAbilityType;
            memset(&gameState->player.abilityTwo, 0, sizeof(Ability));
            gameState->player.abilityTwo.data.level = 1;
        }
    }
}

void DrawDebugInterface(GameState* gameState) {
    DebugState* debugState = &gameState->debugState;
    if (!debugState->debugShown) {
        return;
    }

    // Draw text information
    int leftVerticalOffset = 0;
    DrawNextLine(TextFormat("FPS: %d", GetFPS()), &leftVerticalOffset);
    DrawNextLine(TextFormat("Selected ability index: %d", debugState->selectedAbilityType), &leftVerticalOffset);
    DrawNextLine("Player stats", &leftVerticalOffset);
    DrawNextLine(TextFormat("  Speed: %.2f", gameState->player.speed), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Position: %.2f, %.2f", gameState->player.position.x, gameState->player.position.y), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Radius: %.2f", gameState->player.radius), &leftVerticalOffset);
    DrawNextLine("Map stats", &leftVerticalOffset);
    DrawNextLine(TextFormat("  Wall count: %d", gameState->map.wallCount), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Tile count: %d", gameState->map.tileCount), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Map position: %.0f, %.0f", gameState->map.area.x, gameState->map.area.y), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Map size: %.0f, %.0f", gameState->map.area.width, gameState->map.area.height), &leftVerticalOffset);
    DrawNextLine("Camera stats", &leftVerticalOffset);
    DrawNextLine(TextFormat("  Zoom level: %.2f", gameState->camera.zoom), &leftVerticalOffset);
    DrawNextLine(TextFormat("  Rotation: %.2f", gameState->camera.rotation), &leftVerticalOffset);
}

void DrawNextLine(const char* text, int* offset) {
    int textWidth = MeasureText(text, DEBUG_TEXT_SIZE);
    int basePosition = DEBUG_TEXT_MARGIN - DEBUG_BACKGROUND_MARGIN;
    int backgroundPadding = 2 * DEBUG_BACKGROUND_MARGIN;
    DrawRectangle(basePosition, basePosition + *offset, textWidth + backgroundPadding, DEBUG_TEXT_SIZE + backgroundPadding, DEBUG_BACKGROUND_COLOR);
    DrawText(text, DEBUG_TEXT_MARGIN, DEBUG_TEXT_MARGIN + *offset, DEBUG_TEXT_SIZE, LIME);
    *offset += DEBUG_TEXT_SIZE + DEBUG_TEXT_SPACING;
}