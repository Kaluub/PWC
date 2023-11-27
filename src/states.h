#pragma once

#include "raylib.h"
#include "textures.h"
#include "entities/definitions.h"
#include "map/definitions.h"

typedef struct DebugState {
    int cursorSelection;
    // Flags.
    int debugShown : 1;
} DebugState;

typedef struct GameState {
    Textures textures;
    Player player;
    Map map;
    Camera2D camera;
    DebugState debugState;
} GameState;