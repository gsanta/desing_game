#include "flip_horizontal.h"

namespace spright
{
namespace editor
{
    void flip_horizontal(TileLayer &layer)
    {
        const int layerWidth = layer.getTileBounds().getWidth();
        for (Rect2D *tile : layer.getRenderables())
        {
            const Vec2Int tilePos = layer.getTilePos(tile->getPosition2d());
            layer.setTilePos(tile, Vec2Int(layerWidth - 1 - tilePos.x, tilePos.y));
        }
    }

    void flip_horizontal(TileLayer &layer, const Bounds &bounds)
    {
        RectSelector rectSelector(&layer);
        rectSelector.setSelection(bounds.getBottomLeft(), bounds.getTopRight());

        const vector<Rect2D *> tiles = rectSelector.getSelection();

        for (Rect2D *tile : tiles)
        {
            const Vec2 bottomLeft = tile->getPosition2d();

            const float diffX = bounds.getTopRight().x - (bottomLeft + tile->getSize()).x;

            layer.translateTile(tile, Vec2(2 * diffX + 1, 0));

            const Vec2 newCenter = tile->getCenterPosition2d();
            if (!layer.getBounds().contains(newCenter.x, newCenter.y))
            {
                layer.remove(*tile);
            }
        }
    }

    void flip_horizontal(std::vector<TileLayer> &layers)
    {
        for (TileLayer &layer : layers)
        {
            flip_horizontal(layer);
        }
    }

    void flip_horizontal(std::vector<TileLayer> &layers, const Bounds &bounds)
    {
        for (TileLayer &layer : layers)
        {
            flip_horizontal(layer, bounds);
        }
    }
} // namespace editor
} // namespace spright
