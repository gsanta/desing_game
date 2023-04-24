#include "flip_drawing.h"

namespace spright
{
namespace editor
{
    void flip_layer(TileLayer &layer)
    {
        int layerWidth = layer.getTileBounds().getWidth();
        for (Rect2D *tile : layer.getRenderables())
        {
            Vec2Int tilePos = layer.getTilePos(tile->getPosition2d());
            layer.setTilePos(tile, Vec2Int(layerWidth - 1 - tilePos.x, tilePos.y));
        }
    }

    void flip_drawing(Drawing &drawing, size_t frameIndex)
    {

        Frame &frame = drawing.getFrame(frameIndex);

        for (TileLayer &layer : frame.getLayers())
        {
            flip_layer(layer);
        }
    }
} // namespace editor
} // namespace spright
