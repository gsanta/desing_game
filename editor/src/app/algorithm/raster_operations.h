
#pragma once
#include "../../engine/graphics/layer/tileLayer.h"

namespace spright
{
namespace editor
{
    using namespace engine;

    void raster_operation_copy_area(TileLayer &source, TileLayer &dest, Vec2Int srcPos, Vec2Int dstPos, Vec2Int size);
}
}
