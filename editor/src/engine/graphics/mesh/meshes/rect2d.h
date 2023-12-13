#pragma once

#include "../../../../maths/vec2.h"
#include "../../mesh/meshes/renderable2d.h"
#include "../../renderer/vertex_data.h"

#include <nlohmann/json.hpp>
#include <string.h>

using namespace std::string_literals;

namespace spright
{
namespace engine
{
    using namespace spright::maths;

    class Rect2D : public Renderable2D
    {
    public:
        static const int NUM_VERTICES = 6;

        Rect2D(float x, float y, float width, float height, unsigned int color);

        ~Rect2D() override = default;

        Rect2D(const Rect2D &);

        bool isEqual(const Renderable2D &obj) const override;

        Vec3 getPosition();

        Vec2 getPosition2d();

        int getTileIndex();

        void setTileIndex(int tileIndex);

        void setSize(Vec2 size);

        Vec2 getSize();

        void setPosition(Vec2 position);

        void setCenterPosition(Vec2 position);

        Vec2 getCenterPosition2d() const;

        const unsigned int getColor() const;

        void setColor(unsigned int color);

        bool contains(Vec2 point);

        void translate(Vec2 vec);

        void setZ(float z);

        nlohmann::json getJson() override;

        virtual Rect2D *clone() const override;

    private:
        void calcPositions();

        void calcColors(unsigned int color);

    private:
        Vec3 m_Position;

        Vec2 m_Size;

        int m_TileIndex = -1;

        unsigned int m_Color;
    };
} // namespace engine
} // namespace spright
