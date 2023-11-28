#include <time.h>
#include "game.h"

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

    UpdatePlayer(&gameState->player, &gameState->map);

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
    Player player = gameState->player;
    Map map = gameState->map;

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(gameState->camera);

    // Draw map.
    DrawMap(gameState);

    // Draw player.
    DrawCircleV(player.position, player.radius, player.color);
    for (int i = 0; i < player.colorEffectCount; i += 1) {
        DrawCircleV(player.position, player.radius, player.colorEffects[i]);
    }
    DrawTextEx(GetFontDefault(), player.name, (Vector2) {player.position.x - MeasureText(player.name, 10)/2, player.position.y - player.radius - 10}, 10, 1, WHITE);

    // Draw enemies.
    for (int i = 0; i < map.enemyCount; i += 1) {
        Enemy enemy = map.enemies[i];
        DrawCircleV(enemy.position, enemy.radius, enemy.color);
    }

    // Draw walls.
    for (int i = 0; i < map.wallCount; i += 1) {
        Wall wall = map.walls[i];
        DrawRectangleRec(wall.area, wall.color);
    }

    EndMode2D();

    // Draw GUI elements.
    DrawDebugInterface(gameState);

    EndDrawing();
}