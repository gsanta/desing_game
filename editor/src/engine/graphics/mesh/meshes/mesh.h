#pragma once

#include "../../../../maths/vec3.h"
#include "../../colors.h"
#include "../../renderer/renderer2d.h"

#include <algorithm>

namespace spright
{
namespace engine
{
    using namespace maths;

    class Mesh
    {
    public:
        Mesh(const Vec3 &pos, unsigned int color);

        Mesh(int positionCount, unsigned int color);

        Mesh(const Vec3 *positions, int positionCount);

        Mesh(const Mesh &other);

        virtual Mesh &operator=(const Mesh &other);

        virtual ~Mesh();

        const Vec3 *getPositions() const;

        const Vec3 &getPosition() const;

        virtual void setPosition(const Vec3 &pos);

        virtual void submit(Renderer2D &renderer) const;

        virtual inline bool isEqual(const Mesh &obj) const
        {
            return false;
        }

        virtual bool operator==(const Mesh &rhs);

        virtual bool operator!=(const Mesh &rhs);

        virtual Mesh *clone() const;

    protected:
        Vec3 m_Position;

        Vec3 *m_Positions = nullptr;

        int m_PositionsCount = 0;

        unsigned int m_Color;
    };
} // namespace engine
} // namespace spright
