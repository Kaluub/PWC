#pragma once

#include "raylib.h"
#include "states.h"
#include "debug.h"
#include "map/map.h"
#include "entities/player.h"
#include "entities/enemy.h"

void StartGame();
void RunGame();
void GameLoop(GameState* gameState);
#if defined(PLATFORM_WEB)
void EmscriptenTick(void* gameState);
#endif
void GameTick(GameState* gameState);
void UpdateGame(GameState* gameState);
void DrawGame(GameState* gameState);
void DrawAbilityLevelIndicator(AbilityData data, Vector2 position);