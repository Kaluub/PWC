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
    UpdateEffects(enemy);
    float speed = enemy->speed * enemy->speedMultiplier;
    float radius = enemy->radius * enemy->radiusMultiplier;

    Vector2 velocity = Vector2Scale(enemy->direction, speed * GetFrameTime());
    Vector2 intendedPosition = { enemy->position.x + velocity.x, enemy->position.y + velocity.y };

    // Ensure enemy is in map bounds.
    if (intendedPosition.x - radius < map->area.x) {
        intendedPosition.x = map->area.x + radius;
        velocity.x = intendedPosition.x - enemy->position.x;
        enemy->direction.x *= -1;
    }
    if (intendedPosition.x + radius > map->area.x + map->area.width) {
        intendedPosition.x = map->area.x + map->area.width - radius;
        velocity.x = intendedPosition.x - enemy->position.x;
        enemy->direction.x *= -1;
    }

    if (intendedPosition.y - radius < map->area.y) {
        intendedPosition.y = map->area.y + radius;
        velocity.y = intendedPosition.y - enemy->position.y;
        enemy->direction.y *= -1;
    }
    if (intendedPosition.y + radius > map->area.y + map->area.height) {
        intendedPosition.y = map->area.y + map->area.height - radius;
        velocity.y = intendedPosition.y - enemy->position.y;
        enemy->direction.y *= -1;
    }

    // Wall entity collisions.
    for (int i = 0; i < map->wallCount; i++) {
        Wall wall = map->walls[i];

        // X-axis collision resolution
        if (intendedPosition.x - radius < wall.area.x + wall.area.width &&
            intendedPosition.x + radius > wall.area.x &&
            enemy->position.y - radius < wall.area.y + wall.area.height &&
            enemy->position.y + radius > wall.area.y) {

            if (velocity.x > 0) {
                velocity.x = wall.area.x - (enemy->position.x + radius);
            } else if (velocity.x < 0) {
                velocity.x = (wall.area.x + wall.area.width) - (enemy->position.x - radius);
            }
            intendedPosition.x = enemy->position.x + velocity.x;
            enemy->direction.x *= -1;
        }

        // Y-axis collision resolution
        if (enemy->position.x - radius < wall.area.x + wall.area.width &&
            enemy->position.x + radius > wall.area.x &&
            intendedPosition.y - radius < wall.area.y + wall.area.height &&
            intendedPosition.y + radius > wall.area.y) {

            if (velocity.y > 0) {
                velocity.y = wall.area.y - (enemy->position.y + radius);
            } else if (velocity.y < 0) {
                velocity.y = (wall.area.y + wall.area.height) - (enemy->position.y - radius);
            }
            intendedPosition.y = enemy->position.y + velocity.y;
            enemy->direction.y *= -1;
        }
    }

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