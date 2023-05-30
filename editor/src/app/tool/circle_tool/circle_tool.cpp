#include "./circle_tool.h"

namespace spright
{
namespace editor
{
    CircleTool::CircleTool() : Tool("circle")
    {
    }

    void CircleTool::pointerUp(const ToolContext &context)
    {
        TileLayer &tileLayer = context.doc.activeDrawing->getActiveLayer();

        Vec2 down = context.pointer.down;
        Vec2 curr = context.pointer.curr;

        Bounds bounds = Bounds::createWithPositions(down.x, curr.x, down.y, curr.y);
        Vec2Int bottomLeftTile = tileLayer.getTilePos(bounds.getBottomLeft());
        Vec2Int topRightTile = tileLayer.getTilePos(bounds.getTopRight());
        BoundsInt boundsInt(bottomLeftTile.x, topRightTile.x, bottomLeftTile.y, topRightTile.y);

        std::vector<Rect2D> tiles;


        int centerX = std::round((boundsInt.minX + boundsInt.maxX) / 2);
        int centerY = std::round((boundsInt.minY + boundsInt.maxY) / 2);

        bool evenX = (boundsInt.minX + boundsInt.maxX) % 2;
        bool evenY = (boundsInt.minY + boundsInt.maxY) % 2;

        float radiusX = boundsInt.maxX - centerX;
        float radiusY = boundsInt.maxY - centerY;

        Brush brush;

        for (int x = boundsInt.minX; x <= centerX; x++)
        {
            float angle = std::acos((x - centerX) / radiusX);
            int y = std::round(radiusY * std::sin(angle) + centerY);
            float halfTileSize = tileLayer.getTileSize() / 2;

            brush.paint(tileLayer, Vec2Int(x - evenX, y), context.editorState->color);
            brush.paint(tileLayer, Vec2Int(x - evenX, 2 * centerY - y - evenY), context.editorState->color);
            brush.paint(tileLayer, Vec2Int(2 * centerX - x, y), context.editorState->color);
            brush.paint(tileLayer, Vec2Int(2 * centerX - x, 2 * centerY - y - evenY), context.editorState->color);
        }

        for (int y = boundsInt.minY; y <= centerY; y++)
        {
            float angle = std::asin((y - centerY) / radiusY);
            int x = std::round(radiusX * std::cos(angle) + centerX);
            float halfTileSize = tileLayer.getTileSize() / 2;
            brush.paint(tileLayer, Vec2Int(x, y - evenY), context.editorState->color);
            brush.paint(tileLayer, Vec2Int(2 * centerX - x - evenX, y - evenY), context.editorState->color);
            brush.paint(tileLayer, Vec2Int(x, 2 * centerY - y), context.editorState->color);
            brush.paint(tileLayer, Vec2Int(2 * centerX - x - evenX, 2 * centerY - y), context.editorState->color);
        }
    }
} // namespace editor
} // namespace spright
