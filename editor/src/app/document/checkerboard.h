#pragma once

#include "../../engine/scene/containers/tile_layer.h"
#include "../../engine/graphics/renderable/rect2d.h"

namespace spright
{
namespace editor
{

    using namespace engine;

    class Checkerboard
    {

    public:
        void create(TileLayer &layer) const;
    };
} // namespace editor
} // namespace spright
