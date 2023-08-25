#include "./tile_operations.h"

namespace spright
{
namespace editor
{
    void tile_operation_copy_area(TileLayer &source, TileLayer &dest, Vec2Int srcPos, Vec2Int dstPos, Vec2Int size) {
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                Rect2D *tile = source.getAtTilePos(srcPos.x + i, srcPos.y + j);

                Rect2D newTile(*tile);
                newTile.setCenterPosition(source.getWorldPos(Vec2Int(dstPos.x + i, dstPos.y + j)));

                dest.add(newTile);
            }
        }
    }
}
}
