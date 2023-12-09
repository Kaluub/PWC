#include <math.h>
#include <string.h>
#include "player.h"
#include "raymath.h"
#include "../abilities/ability.h"
#include "../map/map.h"
#include "../utils.h"

Player CreatePlayer() {
    Player player;
    player.name = "Lime";
    player.color = (Color) {255, 0, 0, 255};
    player.position = (Vector2) {32, 32};
    player.radius = 13;
    player.speed = 170;
    player.deathTimer = -1;
    player.inputAngle = 0;
    player.colorEffectCount = 0;
    player.ignoreCollisions = 0;
    player.adminMode = 0;
    player.isHard = 0;

    memset(&player.abilityOne, 0, sizeof(Ability));
    player.abilityOneType = MINIMIZE;
    player.abilityOne.data.level = 1;

    memset(&player.abilityTwo, 0, sizeof(Ability));
    player.abilityTwoType = DEPART;
    player.abilityTwo.data.level = 1;
    
    return player;
}

void UpdatePlayer(Player* player, Map* map, Camera2D* camera) {
    Vector2 velocity = {0, 0};

    // Gameplay controls.
    if (IsKeyPressed(KEY_L)) {
        player->ignoreCollisions = !player->ignoreCollisions;
    }
    if (IsKeyPressed(KEY_O)) {
        player->speed -= 10;
    }
    if (IsKeyPressed(KEY_P)) {
        player->speed += 10;
    }
    if (IsKeyPressed(KEY_E)) {
        // Revive player.
        player->deathTimer = -1;
    }

    if (IsKeyPressed(KEY_ONE) && player->abilityOne.data.level < 5) {
        // Upgrade ability 1.
        player->abilityOne.data.level += 1;
    }
    if (IsKeyPressed(KEY_TWO) && player->abilityTwo.data.level < 5) {
        // Upgrade ability 2.
        player->abilityTwo.data.level += 1;
    }

    // Reset modifiers.
    player->alpha = 255;
    player->speedBoost = 0;
    player->speedMultiplier = 1;
    player->colorEffectCount = 0;

    // Apply abilities.
    if (player->deathTimer <= -1) {
        if (IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_J)) {
            ActivateAbility(player, map, &player->abilityOne, player->abilityOneType);
        }
        if (IsKeyPressed(KEY_X) || IsKeyPressed(KEY_K)) {
            ActivateAbility(player, map, &player->abilityTwo, player->abilityTwoType);
        }
    }

    UpdateAbility(player, map, &player->abilityOne, player->abilityOneType);
    UpdateAbility(player, map, &player->abilityTwo, player->abilityTwoType);

    float currentSpeed = player->speedMultiplier * (player->speed + player->speedBoost);

    if (player->deathTimer > 0) {
        player->deathTimer -= GetFrameTime();
        player->alpha *= 0.5;
        currentSpeed *= 0;
    }

    // Movement controls.
    if (IsKeyDown(KEY_A)) {
        velocity.x -= currentSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_D)) {
        velocity.x += currentSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_W)) {
        velocity.y -= currentSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
        velocity.y += currentSpeed * GetFrameTime();
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        float minSize = min(GetScreenWidth(), GetScreenHeight());
        minSize *= 0.75; // Margin.
        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
        mousePosition = Vector2Subtract(mousePosition, player->position);
        mousePosition = Vector2ClampValue(mousePosition, -minSize, minSize);
        mousePosition = Vector2Scale(mousePosition, 1.0/minSize);
        float mouseAngle = atan2f(mousePosition.y, mousePosition.x);
        float distance = Vector2Length(mousePosition);

        velocity.x = cosf(mouseAngle) * distance * currentSpeed * GetFrameTime();
        velocity.y = sinf(mouseAngle) * distance * currentSpeed * GetFrameTime();
    }

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        velocity.x *= 0.5;
        velocity.y *= 0.5;
    }

    if (velocity.x != 0 || velocity.y != 0) {
        player->inputAngle = atan2f(velocity.y, velocity.x);
    }

    if (!player->ignoreCollisions) {
        // Tile interactions.
        for (int i = 0; i < map->tileCount; i++) {
            Tile tile = map->tiles[i];
            if (CheckCollisionCircleRec(player->position, player->radius, tile.area)) {
                Vector2 tileModifier = GetTileModifier(tile.tileType);
                velocity.x *= tileModifier.x;
                velocity.y *= tileModifier.y;
            }
        }
    }

    Vector2 intendedPosition = { player->position.x + velocity.x, player->position.y + velocity.y };

    if (!player->ignoreCollisions) {
        // Ensure player is in map bounds.
        if (intendedPosition.x - player->radius < map->area.x) {
            intendedPosition.x = map->area.x + player->radius;
            velocity.x = intendedPosition.x - player->position.x;
        }
        if (intendedPosition.x + player->radius > map->area.x + map->area.width) {
            intendedPosition.x = map->area.x + map->area.width - player->radius;
            velocity.x = intendedPosition.x - player->position.x;
        }

        if (intendedPosition.y - player->radius < map->area.y) {
            intendedPosition.y = map->area.y + player->radius;
            velocity.y = intendedPosition.y - player->position.y;
        }
        if (intendedPosition.y + player->radius > map->area.y + map->area.height) {
            intendedPosition.y = map->area.y + map->area.height - player->radius;
            velocity.y = intendedPosition.y - player->position.y;
        }

        // Wall entity collisions.
        for (int i = 0; i < map->wallCount; i++) {
            Wall wall = map->walls[i];
            if (wall.targetType != ALL && wall.targetType != PLAYERS) {
                continue;
            }

            // X-axis collision resolution
            if (intendedPosition.x - player->radius < wall.area.x + wall.area.width &&
                intendedPosition.x + player->radius > wall.area.x &&
                player->position.y - player->radius < wall.area.y + wall.area.height &&
                player->position.y + player->radius > wall.area.y) {

                if (velocity.x > 0) {
                    velocity.x = wall.area.x - (player->position.x + player->radius);
                } else if (velocity.x < 0) {
                    velocity.x = (wall.area.x + wall.area.width) - (player->position.x - player->radius);
                }
                intendedPosition.x = player->position.x + velocity.x;
            }

            // Y-axis collision resolution
            if (player->position.x - player->radius < wall.area.x + wall.area.width &&
                player->position.x + player->radius > wall.area.x &&
                intendedPosition.y - player->radius < wall.area.y + wall.area.height &&
                intendedPosition.y + player->radius > wall.area.y) {

                if (velocity.y > 0) {
                    velocity.y = wall.area.y - (player->position.y + player->radius);
                } else if (velocity.y < 0) {
                    velocity.y = (wall.area.y + wall.area.height) - (player->position.y - player->radius);
                }
                intendedPosition.y = player->position.y + velocity.y;
            }
        }
    }

    player->position = intendedPosition;

    if (!IsInvulnerable(player)) {
        for (int i = 0; i < map->enemyCount; i += 1) {
            Enemy enemy = map->enemies[i];
            if (CheckCollisionCircles(player->position, player->radius, enemy.position, enemy.radius * enemy.radiusMultiplier)) {
                // Player should be downed.
                player->deathTimer = 60;
            }
        }
    }

    player->color.a = player->alpha;
}

int IsInvulnerable(Player *player) {
    // Conditions for which the player is invulnerable to enemies.
    return player->deathTimer > 0
        || player->adminMode
        || player->isHard
        || player->isDeparted;
}

int AddColorEffect(Player *player, Color color) {
    if (player->colorEffectCount >= MAX_COLOR_EFFECTS) {
        return 0;
    }

    player->colorEffects[player->colorEffectCount] = color;
    player->colorEffectCount += 1;

    return 1;
}

void DrawPlayer(GameState *gameState) {
    Player player = gameState->player;

    // Draw ability impacts
    DrawAbility(&player.abilityOne, player.abilityOneType);
    DrawAbility(&player.abilityTwo, player.abilityTwoType);
    
    DrawCircleSector(player.position, player.radius, 0, 360, player.radius * PI * gameState->camera.zoom, player.color);
    for (int i = 0; i < player.colorEffectCount; i += 1) {
        DrawCircleV(player.position, player.radius, player.colorEffects[i]);
    }
    if (player.deathTimer > 0) {
        const char* deathTimer = TextFormat("%.0f", player.deathTimer);
        DrawTextEx(GetFontDefault(), deathTimer, (Vector2) {player.position.x - MeasureText(deathTimer, player.radius - 1)/2, player.position.y - player.radius / 2}, player.radius - 1, 1, RED);
    }
    DrawTextEx(GetFontDefault(), player.name, (Vector2) {player.position.x - MeasureText(player.name, 10)/2, player.position.y - player.radius - 10}, 10, 1, WHITE);
}