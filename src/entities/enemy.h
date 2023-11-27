#pragma once

#include "raylib.h"
#include "definitions.h"
#include "../map/definitions.h"

Enemy CreateEnemy(Map* map);
void UpdateEnemy(Enemy* enemy, Map* map);