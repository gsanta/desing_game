#include "./canvas.h"

namespace spright
{
namespace engine
{
    Canvas::Canvas(const Bounds &bounds) : m_Bounds(bounds)
    {
    }

    const Bounds &Canvas::getBounds() const
    {
        return m_Bounds;
    }

    // Layer &Canvas::getDecorationLayer()
    // {
    //     return m_DecorationLayer;
    // }
} // namespace engine
} // namespace spright
