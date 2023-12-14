#include "rect2d.h"

namespace spright
{
namespace engine
{
    Rect2D::Rect2D(float x, float y, float width, float height, unsigned int color)
        : Renderable2D(NUM_VERTICES), m_Color(color), m_Position(Vec3(x, y, 0)), m_Size(Vec2(width, height))
    {
        calcPositions();
        calcColors();
        calcBounds();
    }

    Rect2D::Rect2D(const Rect2D &rect2d)
        : Renderable2D(rect2d), m_Position(rect2d.m_Position), m_Size(rect2d.m_Size), m_Color(rect2d.m_Color)
    {
    }

    bool Rect2D::isEqual(const Renderable2D &rhs) const
    {
        Rect2D rect2d = dynamic_cast<const Rect2D &>(rhs);

        return Renderable2D::isEqual(rect2d) && m_Size == rect2d.m_Size && m_Position == rect2d.m_Position;
    }


    int Rect2D::getTileIndex()
    {
        return m_TileIndex;
    }

    void Rect2D::setTileIndex(int index)
    {
        m_TileIndex = index;
    }

    Vec3 Rect2D::getPosition()
    {
        return m_Position;
    }

    Vec2 Rect2D::getPosition2d()
    {
        return Vec2(m_Position.x, m_Position.y);
    }

    void Rect2D::setSize(Vec2 size)
    {
        this->m_Size = size;
        calcPositions();
        calcBounds();
    }

    Vec2 Rect2D::getSize()
    {
        return m_Size;
    }

    void Rect2D::setPosition(Vec2 position)
    {
        this->m_Position = Vec3(position.x, position.y, m_Position.z);
        calcPositions();
        calcBounds();
    }

    void Rect2D::setCenterPosition(Vec2 position)
    {
        this->m_Position = Vec3(position.x - m_Size.x / 2.0f, position.y - m_Size.y / 2.0f, m_Position.z);
        calcPositions();
        calcBounds();
    }

    Vec2 Rect2D::getCenterPosition2d() const
    {
        return Vec2(m_Position.x + m_Size.x / 2.0f, m_Position.y + m_Size.y / 2.0f);
    }

    const unsigned int Rect2D::getColor() const
    {
        return m_Color;
    }

    void Rect2D::setColor(unsigned int color)
    {
        m_Color = color;
        calcColors();
    }

    bool Rect2D::contains(Vec2 point)
    {
        const Bounds &bounds = getBounds();
        return point.x > bounds.minX && point.x < bounds.maxX && point.y > bounds.minY && point.y < bounds.maxY;
    }

    void Rect2D::translate(Vec2 vec)
    {
        this->m_Position.x += vec.x;
        this->m_Position.y += vec.y;
        calcPositions();
        calcBounds();
    }

    void Rect2D::setZ(float z)
    {
        m_Position.z = z;
        calcPositions();
        calcBounds();
    }

    nlohmann::json Rect2D::getJson()
    {
        nlohmann::json json = {
            {"posX", m_Position.x},
            {"posY", m_Position.y},
            {"posZ", m_Position.z},
            {"sizeX", m_Size.x},
            {"sizeY", m_Size.y},
        };

        return json;
    }

    Rect2D *Rect2D::clone() const
    {
        return new Rect2D(*this);
    }

    void Rect2D::calcPositions()
    {
        float x = m_Position.x;
        float y = m_Position.y;
        float z = m_Position.z;
        float width = m_Size.x;
        float height = m_Size.y;

        Vec3 corners[8];
        corners[0] = Vec3(x, y, z);                  // bottom left
        corners[1] = Vec3(x, y + height, z);         // top left
        corners[2] = Vec3(x + width, y + height, z); // top right
        corners[3] = Vec3(x + width, y, z);          // bottom right

        m_Positions[0] = corners[0];
        m_Positions[1] = corners[1];
        m_Positions[2] = corners[2];
        m_Positions[3] = corners[0];
        m_Positions[4] = corners[2];
        m_Positions[5] = corners[3];
    }

    void Rect2D::calcColors()
    {
        for (int i = 0; i < NUM_VERTICES; i++)
        {
            m_Colors[i] = m_Color;
        }
    }
} // namespace engine
} // namespace spright
