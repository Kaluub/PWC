#include "map.h"
#include "../utils.h"
#include "../entities/enemy.h"
#include <math.h>

int AddWall(Map* map, Wall wall) {
    if (map->wallCount >= MAX_WALL_COUNT) {
        return 0;
    }
    map->walls[map->wallCount] = wall;
    map->wallCount += 1;
    return 1;
}

int AddTile(Map* map, Tile tile) {
    if (map->tileCount >= MAX_TILE_COUNT) {
        return 0;
    }
    map->tiles[map->tileCount] = tile;
    map->tileCount += 1;
    return 1;
}

Map CreateMap() {
    Map map;
    map.area = (Rectangle) {0, 0, 3200, 3200};
    map.color = (Color) {30, 30, 30, 255};
    map.wallCount = 0;
    map.tileCount = 0;
    map.enemyCount = 0;
    AddWall(&map, (Wall) {{64, 64, 32, 96}, {0, 0, 0, 255}});
    AddTile(&map, (Tile) {{128, 64, 32, 96}, SLOWING, {0, 0, 50, 50}});
    AddTile(&map, (Tile) {{192, 64, 32, 96}, ACCELERATING, {50, 0, 0, 50}});
    AddTile(&map, (Tile) {{256, 64, 32, 96}, HORIZONTAL_NULLIFICATION, {50, 0, 50, 50}});
    AddTile(&map, (Tile) {{320, 64, 32, 96}, VERTICAL_NULLIFICATION, {50, 0, 50, 50}});
    AddTile(&map, (Tile) {{384, 64, 32, 96}, REVERSING, {50, 50, 50, 50}});

    
    for (int i = map.wallCount; i < MAX_WALL_COUNT; i += 1) {
        int x = GetRandomValue(0, map.area.width / 32 - 1) * 32;
        int y = GetRandomValue(0, map.area.height / 32 - 1) * 32;
        int width = GetRandomValue(1, min(map.area.width / 32 - x / 32, 10)) * 32;
        int height = GetRandomValue(1, min(map.area.height / 32 - y / 32, 10)) * 32;

        if(!AddWall(&map, (Wall) {{x, y, width, height}, {0, 0, 0, 255}})) {
            break;
        }
    }

    for (int i = map.enemyCount; i < min(256, MAX_ENEMY_COUNT); i += 1) {
        map.enemies[i] = CreateEnemy(&map);
        map.enemyCount += 1;

        if (map.enemyCount >= MAX_ENEMY_COUNT) {
            break;
        }
    }

    return map;
}

Vector2 GetTileModifier(TileType tileType) {
    switch (tileType) {
        case SLOWING:
            return (Vector2) {0.5, 0.5};
        case ACCELERATING:
            return (Vector2) {1.5, 1.5};
        case HORIZONTAL_NULLIFICATION:
            return (Vector2) {0, 1};
        case VERTICAL_NULLIFICATION:
            return (Vector2) {1, 0};
        case REVERSING:
            return (Vector2) {-1, -1};
        default:
            return (Vector2) {1, 1};
    }
}

void DrawMap(GameState *gameState) {
    Map map = gameState->map;
    int right = map.area.x + map.area.width;
    int bottom = map.area.y + map.area.height;

    for (int x = map.area.x; x < right; x += 32) {
        for (int y = map.area.y; y < bottom; y += 32) {
            DrawTexture(gameState->textures.tile, x, y, map.color);
        }
    }
}