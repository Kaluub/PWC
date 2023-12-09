#include "minimize_projectile.h"
#include "../map/definitions.h"
#include "raymath.h"
#include "raylib.h"

void UpdateMinimizeProjectile(MinimizeProjectile* minimizeProjectile, Map* map) {
    minimizeProjectile->duration -= GetFrameTime();

    Vector2 velocity = Vector2Scale(minimizeProjectile->direction, minimizeProjectile->speed * GetFrameTime());
    Vector2 intendedPosition = { minimizeProjectile->position.x + velocity.x, minimizeProjectile->position.y + velocity.y };

    // Ensure projectile is in map bounds.
    if (intendedPosition.x - minimizeProjectile->radius < map->area.x) {
        intendedPosition.x = map->area.x + minimizeProjectile->radius;
        velocity.x = intendedPosition.x - minimizeProjectile->position.x;
        minimizeProjectile->direction.x *= -1;
    }
    if (intendedPosition.x + minimizeProjectile->radius > map->area.x + map->area.width) {
        intendedPosition.x = map->area.x + map->area.width - minimizeProjectile->radius;
        velocity.x = intendedPosition.x - minimizeProjectile->position.x;
        minimizeProjectile->direction.x *= -1;
    }

    if (intendedPosition.y - minimizeProjectile->radius < map->area.y) {
        intendedPosition.y = map->area.y + minimizeProjectile->radius;
        velocity.y = intendedPosition.y - minimizeProjectile->position.y;
        minimizeProjectile->direction.y *= -1;
    }
    if (intendedPosition.y + minimizeProjectile->radius > map->area.y + map->area.height) {
        intendedPosition.y = map->area.y + map->area.height - minimizeProjectile->radius;
        velocity.y = intendedPosition.y - minimizeProjectile->position.y;
        minimizeProjectile->direction.y *= -1;
    }

    // Wall entity collisions.
    for (int i = 0; i < map->wallCount; i++) {
        Wall wall = map->walls[i];
        if (wall.targetType != ALL) {
            continue;
        }

        // X-axis collision resolution
        if (intendedPosition.x - minimizeProjectile->radius < wall.area.x + wall.area.width &&
            intendedPosition.x + minimizeProjectile->radius > wall.area.x &&
            minimizeProjectile->position.y - minimizeProjectile->radius < wall.area.y + wall.area.height &&
            minimizeProjectile->position.y + minimizeProjectile->radius > wall.area.y) {

            if (velocity.x > 0) {
                velocity.x = wall.area.x - (minimizeProjectile->position.x + minimizeProjectile->radius);
            } else if (velocity.x < 0) {
                velocity.x = (wall.area.x + wall.area.width) - (minimizeProjectile->position.x - minimizeProjectile->radius);
            }
            intendedPosition.x = minimizeProjectile->position.x + velocity.x;
            minimizeProjectile->direction.x *= -1;
        }

        // Y-axis collision resolution
        if (minimizeProjectile->position.x - minimizeProjectile->radius < wall.area.x + wall.area.width &&
            minimizeProjectile->position.x + minimizeProjectile->radius > wall.area.x &&
            intendedPosition.y - minimizeProjectile->radius < wall.area.y + wall.area.height &&
            intendedPosition.y + minimizeProjectile->radius > wall.area.y) {

            if (velocity.y > 0) {
                velocity.y = wall.area.y - (minimizeProjectile->position.y + minimizeProjectile->radius);
            } else if (velocity.y < 0) {
                velocity.y = (wall.area.y + wall.area.height) - (minimizeProjectile->position.y - minimizeProjectile->radius);
            }
            intendedPosition.y = minimizeProjectile->position.y + velocity.y;
            minimizeProjectile->direction.y *= -1;
        }
    }

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