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
} // namespace engine
} // namespace spright
