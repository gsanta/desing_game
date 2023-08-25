#pragma once

#include "../../engine/graphics/layer/tileLayer.h"
#include "../tool/select_tool/rect_selector.h"

#include <cmath>

namespace spright
{
namespace editor
{
    using namespace engine;

    void shear_vertical(TileLayer &source, TileLayer &dest, const BoundsInt &bounds, float angle);
} // namespace editor
} // namespace spright
