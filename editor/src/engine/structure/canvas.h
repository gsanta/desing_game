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
        enum RenderTarget
        {
            Screen,
            Image
        };

        Canvas(const std::string &uuid,
               const Bounds &bounds,
               const Camera &camera,
               std::shared_ptr<Renderer2D> renderer,
               const Layer &decorationLayer);

        const Bounds &getBounds() const;

        const std::string getUuid() const;

        virtual Canvas *clone() const;

        virtual void render(const Camera &camera, Canvas::RenderTarget target);

        Renderer2D &getRenderer();

        Layer &getDecorationLayer();

    private:
        Camera m_Camera;

        Bounds m_Bounds;

        Layer m_DecorationLayer;

        std::string m_Uuid;

        std::shared_ptr<Renderer2D> m_Renderer;
    };
} // namespace engine
} // namespace spright
