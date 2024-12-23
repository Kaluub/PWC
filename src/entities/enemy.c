#include <malloc.h>
#include "enemy.h"
#include "../utils.h"
#include "../math/collisions.h"
#include "raymath.h"

Enemy CreateEnemy(Map* map) {
    Enemy enemy;
    enemy.color = (Color) {180, 180, 180, 255};
    enemy.radius = GetRandomValue(5, 40);
    for (int i = 0; i < 20; i += 1) {
        // 20 attempts to get a good spot
        enemy.position = GetPointInMap(map);
        int isValidSpawn = 1;
        for (int j = 0; j < map->wallCount; j += 1) {
            Wall wall = map->walls[j];
            if (IsCircleInRect(enemy.position, enemy.radius, wall.area)) {
                isValidSpawn = 0;
                break;
            }
        }
        if (isValidSpawn) {
            break;
        }
    }
    enemy.speed = GetRandomValue(20, 100 - 1.5 * enemy.radius);
    if (GetRandomValue(1, 30) == 1) {
        enemy.radius *= 3;
    }

    int angle = GetRandomValue(0, 360);
    enemy.direction = Vector2Normalize((Vector2) {cos(angle), sin(angle)});
    enemy.speedMultiplier = 1;
    enemy.radiusMultiplier = 1;
    enemy.effectCount = 0;
    enemy.minimizeTime = 0;
    enemy.texture.id = 0;
    enemy.textureRadius = 0;
    return enemy;
}

void UpdateEnemy(Enemy* enemy, Map* map) {
    UpdateEffects(enemy);
    float speed = enemy->speed * enemy->speedMultiplier;
    float radius = enemy->radius * enemy->radiusMultiplier;

    Vector2 velocity = Vector2Scale(enemy->direction, speed * GetFrameTime());
    Vector2 intendedPosition = { enemy->position.x + velocity.x, enemy->position.y + velocity.y };

    // Wall collisions.
    int wallsToCheck = 0;
    for (int i = 0; i < map->wallCount; i++) {
        Wall wall = map->walls[i];
        if (wall.targetType != ALL && wall.targetType != ENEMIES) {
            continue;
        }
        wallsToCheck += 1;
    }
    Rectangle* rects = (Rectangle*) MemAlloc(sizeof(Rectangle) * wallsToCheck);
    int storedRects = 0;
    for (int i = 0; i < map->wallCount; i++) {
        Wall wall = map->walls[i];
        if (wall.targetType != ALL && wall.targetType != ENEMIES) {
            continue;
        }
        rects[storedRects] = wall.area;
        storedRects += 1;
    }
    Vector2 mtv = GetMTVCircleRects((CircleCollider) {intendedPosition, radius}, rects, wallsToCheck);
    intendedPosition = Vector2Add(intendedPosition, mtv);
    if (mtv.x != 0) {
        enemy->direction.x *= -1;
    }
    if (mtv.y != 0) {
        enemy->direction.y *= -1;
    }
    MemFree(rects);
    rects = NULL;

    enemy->position = intendedPosition;
}

void UpdateEffects(Enemy* enemy) {
    enemy->radiusMultiplier = 1;
    enemy->speedMultiplier = 1;

    if (enemy->minimizeTime > 0) {
        enemy->minimizeTime -= GetFrameTime();
        enemy->radiusMultiplier *= 0.5;
        enemy->speedMultiplier *= 0.6;
    }
}

void DrawEnemy(Enemy* enemy) {
    float radius = enemy->radius * enemy->radiusMultiplier;
    if (enemy->texture.id == 0 || radius != enemy->textureRadius) {
        TraceLog(LOG_INFO, TextFormat("Loading new enemy texture: old id %d; radius diff %f/%f", enemy->texture.id, radius, enemy->textureRadius));
        if (enemy->texture.id != 0) {
            UnloadTexture(enemy->texture);
        }
        Image newImage = GenImageColor(radius + 2, radius + 2, (Color) {0, 0, 0, 0});
        ImageDrawCircle(&newImage, radius + 1, radius + 1, radius, enemy->color);
        enemy->texture = LoadTextureFromImage(newImage);
        enemy->textureRadius = radius;
        UnloadImage(newImage);
    }
    DrawTextureV(enemy->texture, enemy->position, WHITE);
    // DrawCircleV(enemy->position, radius, enemy->color);
    // DrawRing(enemy->position, radius - 1, radius + 1, 0, 360, 36, BLACK);
}