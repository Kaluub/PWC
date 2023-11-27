#include "enemy.h"
#include "../utils.h"
#include "raymath.h"

Enemy CreateEnemy(Map* map) {
    Enemy enemy;
    enemy.color = (Color) {180, 180, 180, 255};
    enemy.position = GetPointInMap(map);
    enemy.radius = GetRandomValue(5, 30);
    enemy.speed = GetRandomValue(20, 100 - enemy.radius);

    int directionFactor = GetRandomValue(0, 360);
    enemy.direction = (Vector2) {cos(directionFactor), sin(directionFactor)};
    return enemy;
}

void UpdateEnemy(Enemy* enemy, Map* map) {
    Vector2 velocity = Vector2Scale(enemy->direction, enemy->speed * GetFrameTime());
    Vector2 intendedPosition = { enemy->position.x + velocity.x, enemy->position.y + velocity.y };

    // Ensure enemy is in map bounds.
    if (intendedPosition.x - enemy->radius < map->area.x) {
        intendedPosition.x = map->area.x + enemy->radius;
        velocity.x = intendedPosition.x - enemy->position.x;
        enemy->direction.x *= -1;
    }
    if (intendedPosition.x + enemy->radius > map->area.x + map->area.width) {
        intendedPosition.x = map->area.x + map->area.width - enemy->radius;
        velocity.x = intendedPosition.x - enemy->position.x;
        enemy->direction.x *= -1;
    }

    if (intendedPosition.y - enemy->radius < map->area.y) {
        intendedPosition.y = map->area.y + enemy->radius;
        velocity.y = intendedPosition.y - enemy->position.y;
        enemy->direction.y *= -1;
    }
    if (intendedPosition.y + enemy->radius > map->area.y + map->area.height) {
        intendedPosition.y = map->area.y + map->area.height - enemy->radius;
        velocity.y = intendedPosition.y - enemy->position.y;
        enemy->direction.y *= -1;
    }

    // Wall entity collisions.
    for (int i = 0; i < map->wallCount; i++) {
        Wall wall = map->walls[i];

        // X-axis collision resolution
        if (intendedPosition.x - enemy->radius < wall.area.x + wall.area.width &&
            intendedPosition.x + enemy->radius > wall.area.x &&
            enemy->position.y - enemy->radius < wall.area.y + wall.area.height &&
            enemy->position.y + enemy->radius > wall.area.y) {

            if (velocity.x > 0) {
                velocity.x = wall.area.x - (enemy->position.x + enemy->radius);
            } else if (velocity.x < 0) {
                velocity.x = (wall.area.x + wall.area.width) - (enemy->position.x - enemy->radius);
            }
            intendedPosition.x = enemy->position.x + velocity.x;
            enemy->direction.x *= -1;
        }

        // Y-axis collision resolution
        if (enemy->position.x - enemy->radius < wall.area.x + wall.area.width &&
            enemy->position.x + enemy->radius > wall.area.x &&
            intendedPosition.y - enemy->radius < wall.area.y + wall.area.height &&
            intendedPosition.y + enemy->radius > wall.area.y) {

            if (velocity.y > 0) {
                velocity.y = wall.area.y - (enemy->position.y + enemy->radius);
            } else if (velocity.y < 0) {
                velocity.y = (wall.area.y + wall.area.height) - (enemy->position.y - enemy->radius);
            }
            intendedPosition.y = enemy->position.y + velocity.y;
            enemy->direction.y *= -1;
        }
    }

    enemy->position = intendedPosition;
}