#pragma once

#include "../../../../maths/vec3.h"
#include "../../colors.h"
#include <memory>

namespace spright
{
namespace engine
{
    class MeshBuilder
    {
    public:
        void setColor(int color);

        void setPos(const Vec3 &pos);
    protected:
        int m_Color = COLOR_WHITE;

        Vec3 m_Pos;
    };
} // namespace editor
} // namespace spright
