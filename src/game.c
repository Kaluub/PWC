#include <time.h>
#include <malloc.h>
#include "config.h"
#include "game.h"
#include "abilities/ability.h"
#include "drawing/text.h"
#include "raymath.h"
#include "utils.h"

void StartGame() {
    #if defined(PLATFORM_WEB)
    TraceLog(LOG_INFO, "Web version!");
    #endif
    InitWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, NAME);
    SetRandomSeed(time(NULL));
    // SetTargetFPS(60);
    RunGame();
}

void RunGame() {
    GameState gameState;
    gameState.textures = LoadTextures();
    gameState.fonts = LoadFonts();
    gameState.player = CreatePlayer();
    gameState.map = CreateMap();
    gameState.camera.target = gameState.player.position;
    gameState.camera.offset = (Vector2) {GetScreenWidth() / 2, GetScreenHeight() / 2};
    gameState.camera.rotation = 0.0f;
    gameState.camera.zoom = 1;
    gameState.debugState = (DebugState) {0};

    #if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
    emscripten_set_main_loop_arg(EmscriptenTick, &gameState, 0, 1);
    #else
    GameLoop(&gameState);
    #endif
}

void GameLoop(GameState* gameState) {
    while (!WindowShouldClose()) {
        GameTick(gameState);
    }
}

#if defined(PLATFORM_WEB)
void EmscriptenTick(void* gameState) {
    GameTick((GameState*) gameState);
}
#endif

void GameTick(GameState* gameState) {
    UpdateGame(gameState);
    if (IsKeyDown(KEY_V)) {
        // Frame skip.
        for (int i = 0; i < FRAME_SKIP; i += 1) {
            UpdateGame(gameState);
        }
    }
    DrawGame(gameState);
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

    Vector2 scrollChange = GetMouseWheelMoveV();
    if (scrollChange.y != 0) {
        float zoomChange = 0.05 * scrollChange.y;
        if (fabs(scrollChange.y) > 10) {
            // Fix for web version.
            zoomChange = 0.05 * (scrollChange.y > 0 ? -1 : 1);
        }
        gameState->camera.zoom += zoomChange;
        if (gameState->camera.zoom <= MIN_ZOOM) {
            gameState->camera.zoom = MIN_ZOOM;
        }
        if (gameState->camera.zoom >= MAX_ZOOM) {
            gameState->camera.zoom = MAX_ZOOM;
        }
    }

    if (IsKeyPressed(KEY_N) || IsKeyPressedRepeat(KEY_N)) {
        gameState->camera.zoom -= 0.05;
        if (gameState->camera.zoom <= MIN_ZOOM) {
            gameState->camera.zoom = MIN_ZOOM;
        }
    }

    if (IsKeyPressed(KEY_M) || IsKeyPressedRepeat(KEY_M)) {
        gameState->camera.zoom += 0.05;
        if (gameState->camera.zoom >= MAX_ZOOM) {
            gameState->camera.zoom = MAX_ZOOM;
        }
    }

    if (IsKeyPressed(KEY_B) || IsKeyPressedRepeat(KEY_B)) {
        gameState->camera.rotation += 5;
    }

    gameState->camera.target = gameState->player.position;
}

void DrawGame(GameState* gameState) {
    Map map = gameState->map;

    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
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
        DrawRectangle(10, textureY, 50, heightRatio * 50, (Color) {0, 0, 0, 128});
    }
    if (gameState->player.abilityTwo.data.cooldown > 0) {
        float heightRatio = gameState->player.abilityTwo.data.cooldown / gameState->player.abilityTwo.data.totalCooldown;
        DrawRectangle(70, textureY, 50, heightRatio * 50, (Color) {0, 0, 0, 128});
    }

    // Draw ability level.
    DrawAbilityLevelIndicator(gameState->player.abilityOne.data, (Vector2) {35, textureY + 25});
    DrawAbilityLevelIndicator(gameState->player.abilityTwo.data, (Vector2) {95, textureY + 25});

    // Draw area title.
    Vector2 areaTitleSize = MeasureTextEx(gameState->fonts.tahomaBold, map.name, 48, 0);
    int centerX = GetScreenWidth() / 2;
    int textX = centerX - areaTitleSize.x / 2;
    int textY = 4;
    Color textColor = (Color) {160, 190, 235, 255};
    Color outlineColor = (Color) {65, 80, 100, 255};
    DrawOutlinedText(gameState->fonts.tahomaBold, map.name, textX, textY, 48, textColor, outlineColor);

    DrawDebugInterface(gameState);

    EndDrawing();
}

void DrawAbilityLevelIndicator(AbilityData data, Vector2 position) {
    CirclePoint* points = GetPointsOnCircle(data.level, DEG2RAD*(25 + min(5*data.level, 65)), DEG2RAD*90, position, 32);
    if (points == NULL) {
        return;
    }

    for (int i = 0; i < data.level; i += 1) {
        CirclePoint point = points[i];
        DrawCircleV(point.position, 2, YELLOW);
    }

    free(points);
}