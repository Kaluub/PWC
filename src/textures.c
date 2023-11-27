#include "textures.h"

Textures LoadTextures() {
    Textures textures;
    textures.tile = LoadTexture("assets/tile.png");
    return textures;
}