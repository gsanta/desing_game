#include "./canvas.h"

namespace spright
{
namespace engine
{
    Canvas::Canvas(const std::string &uuid, const Bounds &bounds, const Layer &decorationLayer)
        : m_Uuid(uuid), m_Bounds(bounds), m_DecorationLayer(decorationLayer)
    {
    }

    const Bounds &Canvas::getBounds() const
    {
        return m_Bounds;
    }

    const std::string Canvas::getUuid() const {
        return m_Uuid;
    }

    Layer &Canvas::getDecorationLayer()
    {
        return m_DecorationLayer;
    }
} // namespace engine
} // namespace spright
