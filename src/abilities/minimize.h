#pragma once

#include "definitions.h"
#include "../map/definitions.h"
#include "../entities/definitions.h"

void ActivateMinimize(Player *player, Minimize *minimize);
void UpdateMinimize(Player *player, Map *map, Minimize *minimize);
void DrawMinimizeProjectiles(Minimize *minimize);