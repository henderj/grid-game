#pragma once

#include "vector2.h"
#include "sprites.h"

namespace game
{
    struct SpriteRenderData
    {
        Vector2 pos;
        SpriteTypes type;

        SpriteRenderData(Vector2 pos, SpriteTypes type) : pos(pos), type(type) {}
    };

} // namespace game
