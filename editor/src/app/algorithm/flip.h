#pragma once

#include "../../engine/graphics/layer/tileLayer.h"
#include "../document/drawing.h"

namespace spright
{
namespace editor
{
    void flip_horizontal(TileLayer &layer);

    void flip_horizontal(std::vector<TileLayer> &layers);
} // namespace editor
} // namespace spright