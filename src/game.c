#include <time.h>
#include "game.h"
#include "abilities/ability.h"

#include "raymath.h"
#include "utils.h"

void StartGame() {
    InitWindow(720, 480, "PWC");
    SetRandomSeed(time(NULL));
    //SetTargetFPS(60);
    RunGame();
}

void RunGame() {
    GameState gameState;
    gameState.textures = LoadTextures();
    gameState.player = CreatePlayer();
    gameState.map = CreateMap();
    gameState.camera.target = gameState.player.position;
    gameState.camera.offset = (Vector2) {GetScreenWidth() / 2, GetScreenHeight() / 2};
    gameState.camera.rotation = 0.0f;
    gameState.camera.zoom = 1;
    gameState.debugState = (DebugState) {0, 0};

    GameLoop(&gameState);
}

void GameLoop(GameState* gameState) {
    while (!WindowShouldClose()) {
        UpdateGame(gameState);
        DrawGame(gameState);
    }
}

void UpdateGame(GameState* gameState) {
    if (IsKeyPressed(KEY_R)) {
        gameState->map = CreateMap();
    }

    UpdatePlayer(&gameState->player, &gameState->map, &gameState->camera);

    for (int i = 0; i < gameState->map.enemyCount; i += 1) {
        UpdateEnemy(&gameState->map.enemies[i], &gameState->map);
    }

    UpdateDebugInterface(gameState);

    if (IsKeyPressed(KEY_N) || IsKeyPressedRepeat(KEY_N)) {
        gameState->camera.zoom -= 0.05;
    }
    if (IsKeyPressed(KEY_M) || IsKeyPressedRepeat(KEY_M)) {
        gameState->camera.zoom += 0.05;
    }
    if (IsKeyPressed(KEY_B) || IsKeyPressedRepeat(KEY_B)) {
        gameState->camera.rotation += 5;
    }
    gameState->camera.target = gameState->player.position;
}

void DrawGame(GameState* gameState) {
    Map map = gameState->map;

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(gameState->camera);

    // Draw map.
    DrawMap(gameState);

    // Draw player.
    DrawPlayer(gameState);

    // Draw enemies.
    for (int i = 0; i < map.enemyCount; i += 1) {
        Enemy* enemy = &map.enemies[i];
        DrawEnemy(enemy);
    }

    // Draw walls.
    for (int i = 0; i < map.wallCount; i += 1) {
        Wall wall = map.walls[i];
        DrawRectangleRec(wall.area, wall.color);
    }

    EndMode2D();

    // Draw abilities.
    int textureY = GetScreenHeight() - 60;
    Texture2D abilityOneIcon = GetAbilityIcon(gameState, gameState->player.abilityOneType);
    Texture2D abilityTwoIcon = GetAbilityIcon(gameState, gameState->player.abilityTwoType);
    DrawTexture(abilityOneIcon, 10, textureY, WHITE);
    DrawTexture(abilityTwoIcon, 70, textureY, WHITE);

    // Draw ability cooldowns.
    if (gameState->player.abilityOne.data.cooldown > 0) {
        float heightRatio = gameState->player.abilityOne.data.cooldown / gameState->player.abilityOne.data.totalCooldown;
        DrawRectangle(10, GetScreenHeight() - 60, 50, heightRatio * 50, (Color) {0, 0, 0, 128});
    }
    if (gameState->player.abilityTwo.data.cooldown > 0) {
        float heightRatio = gameState->player.abilityTwo.data.cooldown / gameState->player.abilityTwo.data.totalCooldown;
        DrawRectangle(70, GetScreenHeight() - 60, 50, heightRatio * 50, (Color) {0, 0, 0, 128});
    }

    // Draw ability level.
    DrawCircle(10, textureY + 50, 5, YELLOW);
    DrawCircle(70, textureY + 50, 5, YELLOW);
    const char* abilityOneLevelText = TextFormat("%i", gameState->player.abilityOne.data.level);
    const char* abilityTwoLevelText = TextFormat("%i", gameState->player.abilityTwo.data.level);
    int widthOne = MeasureText(abilityOneLevelText, 6);
    int widthTwo = MeasureText(abilityTwoLevelText, 6);
    DrawText(abilityOneLevelText, 10 - widthOne/2, textureY + 46, 6, BLACK);
    DrawText(abilityTwoLevelText, 70 - widthTwo/2, textureY + 46, 6, BLACK);

    // Draw area title.
    const char* areaTitle = "Withered Wilderness";
    int areaTitleWidth = MeasureText(areaTitle, 30);
    int centerX = GetScreenWidth() / 2;
    int textPositionX = centerX - areaTitleWidth / 2;
    int textPositionY = 4;
    Color backgroundTextColor = (Color) {65, 80, 100, 255};
    Color textColor = (Color) {160, 190, 235, 255};
    DrawText(areaTitle, textPositionX - 2, textPositionY - 2, 30, backgroundTextColor);
    DrawText(areaTitle, textPositionX + 2, textPositionY - 2, 30, backgroundTextColor);
    DrawText(areaTitle, textPositionX - 2, textPositionY + 2, 30, backgroundTextColor);
    DrawText(areaTitle, textPositionX + 2, textPositionY + 2, 30, backgroundTextColor);
    DrawText(areaTitle, textPositionX, textPositionY - 2, 30, backgroundTextColor);
    DrawText(areaTitle, textPositionX, textPositionY + 2, 30, backgroundTextColor);
    DrawText(areaTitle, textPositionX - 2, textPositionY, 30, backgroundTextColor);
    DrawText(areaTitle, textPositionX + 2, textPositionY, 30, backgroundTextColor);
    DrawText(areaTitle, textPositionX, textPositionY, 30, textColor);

    DrawDebugInterface(gameState);

    EndDrawing();
}