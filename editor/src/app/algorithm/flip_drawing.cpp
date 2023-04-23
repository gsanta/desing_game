#include "flip_drawing.h"

namespace spright
{
namespace editor
{
    void flip_drawing(Drawing &drawing) {
        TileLayer& layer = drawing.getActiveLayer();
        int layerWidth = layer.getTileBounds().getWidth();
        for (Rect2D* tile : layer.getRenderables()) {
            Vec2Int tilePos = layer.getTilePos(tile->getPosition2d());
            layer.setTilePos(tile, Vec2Int(layerWidth - 1 - tilePos.x, tilePos.y));
        }
    }
}
}
