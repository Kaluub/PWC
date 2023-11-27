#pragma once

#include "states.h"

void UpdateDebugInterface(GameState* gameState);
void DrawDebugInterface(GameState* gameState);
void DrawNextLine(const char* text, int* offset);