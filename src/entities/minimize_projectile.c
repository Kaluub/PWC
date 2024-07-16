#include <malloc.h>
#include "minimize_projectile.h"
#include "../map/definitions.h"
#include "../math/collisions.h"
#include "raymath.h"
#include "raylib.h"

void UpdateMinimizeProjectile(MinimizeProjectile* minimizeProjectile, Map* map) {
    minimizeProjectile->duration -= GetFrameTime();

    Vector2 velocity = Vector2Scale(minimizeProjectile->direction, minimizeProjectile->speed * GetFrameTime());
    Vector2 intendedPosition = { minimizeProjectile->position.x + velocity.x, minimizeProjectile->position.y + velocity.y };

    // Wall collisions.
    int wallsToCheck = 0;
    for (int i = 0; i < map->wallCount; i++) {
        Wall wall = map->walls[i];
        if (wall.targetType != ALL) {
            continue;
        }
        wallsToCheck += 1;
    }
    Rectangle* rects = (Rectangle*) MemAlloc(sizeof(Rectangle) * wallsToCheck);
    int storedRects = 0;
    for (int i = 0; i < map->wallCount; i++) {
        Wall wall = map->walls[i];
        if (wall.targetType != ALL) {
            continue;
        }
        rects[storedRects] = wall.area;
        storedRects += 1;
    }
    Vector2 mtv = GetMTVCircleRects((CircleCollider) {intendedPosition, minimizeProjectile->radius}, rects, wallsToCheck);
    intendedPosition = Vector2Add(intendedPosition, mtv);
    if (mtv.x != 0) {
        minimizeProjectile->direction.x *= -1;
    }
    if (mtv.y != 0) {
        minimizeProjectile->direction.y *= -1;
    }
    MemFree(rects);
    rects = NULL;

    minimizeProjectile->position = intendedPosition;

    for (int i = 0; i < map->enemyCount; i += 1) {
        Enemy* enemy = &map->enemies[i];
        if (CheckCollisionCircles(minimizeProjectile->position, minimizeProjectile->radius, enemy->position, enemy->radius * enemy->radiusMultiplier)) {
            // Enemy should be minimized.
            enemy->minimizeTime = 2;
        }
    }
}

void DrawMinimizeProjectile(MinimizeProjectile minimizeProjectile) {
    DrawCircleV(minimizeProjectile.position, minimizeProjectile.radius, (Color) {255, 0, 0, 255});
}