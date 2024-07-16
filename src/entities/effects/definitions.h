#pragma once

#include "raylib.h"

typedef enum EffectType {
    NONE_EFFECT,
    ENEMY_SLOWING_EFFECT,
} EffectType;

// Common effect fields.
typedef struct EffectData {
    EffectType effectType;
    float radius;
    Color color;
} EffectData;

typedef struct EnemySlowingEffect {
    EffectData data;
} EnemySlowingEffect;

typedef union Effect {
    EffectData data;
    EnemySlowingEffect enemySlowingEffect;
} Effect;
