#include "headless_renderer_provider.h"

namespace spright
{
namespace editing
{
    std::unique_ptr<Renderer2D> HeadlessRendererProvider::createRenderer2D() const
    {
        return std::make_unique<HeadlessRenderer2D>();
    }

    HeadlessRendererProvider *HeadlessRendererProvider::clone() const
    {
        return new HeadlessRendererProvider();
    }
} // namespace editing
} // namespace spright
