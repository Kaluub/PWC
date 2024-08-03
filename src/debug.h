#pragma once

#include "states.h"

void UpdateDebugInterface(GameState* gameState);
void DrawDebugInterface(GameState* gameState);
void DrawAbilityDebugState(Ability* ability, AbilityType abilityType, const char* sectionHeader, int* offset);
void DrawNextLine(const char* text, int* offset);