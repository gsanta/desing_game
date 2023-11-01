#pragma once
#include "../graphics/layer/layer.h"
#include "../graphics/renderable/bounds.h"

namespace spright
{
namespace engine
{
    class Canvas
    {
    public:
        enum Type {
            Drawing,
            Drawing3d
        };

        Canvas(const std::string &uuid, const Bounds &bounds, const Layer &decorationLayer);

        virtual const Bounds &getBounds() const;

        const std::string getUuid() const;

        Layer &getDecorationLayer();

    private:
        Bounds m_Bounds;

        Layer m_DecorationLayer;

        std::string m_Uuid;
    };
} // namespace engine
} // namespace spright
