#pragma once

#include "../graphics/layer/group.h"
#include "../graphics/renderable/renderable.h"
#include "canvas.h"

namespace spright
{
namespace engine
{
    class Drawing3d : public Canvas
    {
    public:
        Drawing3d(const std::string &uuid,
                  const Bounds &bounds,
                  const Camera &camera,
                  const Layer &decorationLayer,
                  std::shared_ptr<Renderer2D> renderer);

        Renderable &add(const Renderable &rect);

        Drawing3d *clone() const override;

        void render(const Camera &camera, Canvas::RenderTarget target) override;

    private:
        Group<Renderable> m_Group;
    };
} // namespace engine
} // namespace spright
