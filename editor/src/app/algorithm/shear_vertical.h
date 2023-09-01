#pragma once

#include "../../engine/graphics/layer/tile_view.h"
#include "../tool/select_tool/rect_selector.h"
#include "./tile_operations.h"

#include <cmath>

namespace spright
{
namespace editor
{
    using namespace engine;

    void shear_vertical(TileView &source, const BoundsInt &bounds, float angle);

    void shear_horizontal(TileLayer &source, TileLayer &dest, const BoundsInt &bounds, float angle);
} // namespace editor
} // namespace spright