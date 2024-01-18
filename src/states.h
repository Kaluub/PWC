#pragma once

#include "raylib.h"
#include "drawing/textures.h"
#include "entities/definitions.h"
#include "map/definitions.h"

typedef struct DebugState {
    int selectedAbilityType;
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