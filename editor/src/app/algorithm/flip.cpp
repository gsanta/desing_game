#include "flip.h"

namespace spright
{
namespace editor
{
    void flip_horizontal(TileLayer &layer)
    {
        int layerWidth = layer.getTileBounds().getWidth();
        for (Rect2D *tile : layer.getRenderables())
        {
            Vec2Int tilePos = layer.getTilePos(tile->getPosition2d());
            layer.setTilePos(tile, Vec2Int(layerWidth - 1 - tilePos.x, tilePos.y));
        }
    }

    void flip_horizontal(std::vector<TileLayer> &layers)
    {
        for (TileLayer &layer : layers)
        {
            flip_horizontal(layer);
        }
    }
} // namespace editor
} // namespace spright
