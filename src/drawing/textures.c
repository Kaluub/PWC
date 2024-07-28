#include "textures.h"

Textures LoadTextures() {
    Textures textures;
    textures.tile = LoadTexture("assets/tile.png");
    textures.night = LoadTexture("assets/abilities/night.png");
    textures.depart = LoadTexture("assets/abilities/depart.png");
    textures.harden = LoadTexture("assets/abilities/harden.png");
    textures.minimize = LoadTexture("assets/abilities/minimize.png");
    textures.flow = LoadTexture("assets/abilities/flow.png");
    textures.defaultAbility = LoadTexture("assets/abilities/default.png");
    return textures;
}