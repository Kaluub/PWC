#pragma once

#include "raylib.h"

typedef struct Textures {
    Texture2D tile;
    Texture2D night;
    Texture2D depart;
    Texture2D harden;
    Texture2D minimize;
    Texture2D flow;
    Texture2D defaultAbility;
} Textures;

Textures LoadTextures();