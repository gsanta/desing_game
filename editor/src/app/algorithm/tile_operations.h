
#pragma once
#include "../../engine/graphics/layer/tileLayer.h"

namespace spright
{
namespace editor
{
    using namespace engine;

    void tile_operation_copy_area(const TileLayer &source, TileLayer &dest, const BoundsInt &area, const Vec2Int &dstPos);
} // namespace editor
} // namespace spright
