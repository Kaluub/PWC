#pragma once

#include "raylib.h"
#include "../abilities/definitions.h"

#define MAX_COLOR_EFFECTS 8

typedef enum TargetType {
    ALL,
    ENEMIES,
    PLAYERS,
} TargetType;

typedef struct Player {
    char* name;
    Color color;
    Vector2 position;
    float radius;
    float speed;
    float deathTimer;
    float inputAngle;
    int alpha;
    float speedBoost;
    float speedMultiplier;
    Color colorEffects[MAX_COLOR_EFFECTS];
    int colorEffectCount;
    // Abilities.
    AbilityType abilityOneType;
    Ability abilityOne;
    AbilityType abilityTwoType;
    Ability abilityTwo;
    // Flags.
    int ignoreCollisions : 1;
    int adminMode : 1;
    int isHard : 1;
    int isDeparted : 1;
} Player;

typedef struct Enemy {
    Color color;
    Vector2 position;
    Vector2 direction;
    float radius;
    float radiusMultiplier;
    float speed;
    float speedMultiplier;
    float minimizeTime;
} Enemy;