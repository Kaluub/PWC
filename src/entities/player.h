#pragma once

#include "raylib.h"
#include "definitions.h"
#include "../states.h"
#include "../map/definitions.h"

Player CreatePlayer();
void UpdatePlayer(Player* player, Map* map, Camera2D* camera);
int IsInvulnerable(Player* player);
int AddColorEffect(Player* player, Color color);
void DrawPlayer(GameState* gameState);