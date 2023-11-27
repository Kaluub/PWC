#pragma once

#include "raylib.h"
#include "definitions.h"
#include "../entities/definitions.h"
#include "../states.h"

int AddWall(Map* map, Wall wall);
int AddTile(Map* map, Tile tile);
Map CreateMap();
Vector2 GetTileModifier(TileType tileType);
void DrawMap(GameState *gameState);