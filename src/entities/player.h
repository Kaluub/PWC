#pragma once

#include "raylib.h"
#include "definitions.h"
#include "../map/definitions.h"

Player CreatePlayer();
void UpdatePlayer(Player* player, Map* map);
int AddColorEffect(Player* player, Color color);