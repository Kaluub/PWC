#pragma once

#include "raylib.h"

// Ability type fields. Process abilities in ability.c/ability.h.
typedef enum AbilityType {
    NONE,
    NIGHT,
    DEPART,
    HARDEN,
    MINIMIZE,
} AbilityType;

// Common ability fields.
typedef struct AbilityData {
    int level;
    float cooldown;
    float totalCooldown;
} AbilityData;

typedef struct MinimizeProjectile {
    Vector2 position;
    Vector2 direction;
    float radius;
    int speed;
    float duration;
} MinimizeProjectile;

// This format is a bit weird, but it allows us to have additional ability data and allows for
// unique ability slots such that we store any amount of abilities in a slot.
// The first element must always be an AbilityData struct!

typedef struct Night {
    AbilityData data;
    float duration;
    float nightSpeed;
} Night;

typedef struct Depart {
    AbilityData data;
    float duration;
} Depart;

typedef struct Harden {
    AbilityData data;
} Harden;

typedef struct Minimize {
    AbilityData data;
    MinimizeProjectile* projectiles;
    int projectileCount;
} Minimize;

// Ability union to allow for any abilities to use the same slot.
typedef union Ability {
    AbilityData data; // Allows us to have the AbilityData always visible from <Ability>.data
    Night night;
    Depart depart;
    Harden harden;
    Minimize minimize;
} Ability;