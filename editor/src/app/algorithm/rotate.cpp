#include "./rotate.h"

namespace spright
{
namespace editor
{
    std::vector<int> rotate(TileLayer &source, const BoundsInt &bounds, float angle)
    {
        float sina = sin(angle);
        float cosa = cos(angle);

        TileView dest(source.getBounds(), source.getTileSize());

        int minX = bounds.minX;// - (int)(bounds.getWidth()) < 0 ? 0 : bounds.minX - (int)(bounds.getWidth());
        int minY = bounds.minY;// - (int)(bounds.getHeight()) < 0 ? 0 : bounds.minY - (int)(bounds.getHeight());
        int maxX = bounds.maxX;// + (int)(bounds.getWidth());
        int maxY = bounds.maxY;// + (int)(bounds.getHeight());

        int width = source.getTileBounds().getWidth();
        int height = source.getTileBounds().getHeight();
        int widthMinus1 = width - 1;
        int heightMinus1 = height - 1;

        Vec2Int center = bounds.getCenter();

        for (int i = minX; i < maxX; i++)
        {
            int xDiff = center.x - i;
            for (int j = minY; j < maxY; j++)
            {
                int yDiff = center.y - j;
                int x = center.x + (int)std::round(-xDiff * cosa - yDiff * sina);
                // if (x < 0 || x > widthMinus1)
                //     continue;
                int y = center.y + (int)std::round(-yDiff * cosa + xDiff * sina);
                // if (y < 0 || y > heightMinus1)
                //     continue;

                Rect2D *tile = source.getAtTilePos(i, j);

                if (tile != nullptr)
                {
                    Vec2Int newDestPos = Vec2Int(x, y);
                    Rect2D newTile(*tile);
                    newTile.setCenterPosition(source.getCenterPos(newDestPos));
                    dest.add(newTile, newDestPos);
                }
            }
        }

        tile_operation_remove_area(source, bounds);
        tile_operation_copy_all(dest, source);

        std::vector<int> newIndexes;

        for (const Rect2D *tile : dest.getTiles())
        {
            newIndexes.push_back(dest.getTileIndex(tile->getCenterPosition2d()));
        }

        return newIndexes;
    }
} // namespace editor
} // namespace spright
