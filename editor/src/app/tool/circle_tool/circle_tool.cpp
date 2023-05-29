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
        // why not maxX - minX?
        bool evenX = (boundsInt.minX + boundsInt.maxX) % 2;
        bool evenY = (boundsInt.minY + boundsInt.maxY) % 2;

        int radiusX = boundsInt.maxX - centerX;
        int radiusY = boundsInt.maxY - centerY;

        for (int x = boundsInt.minX; x <= centerX; x++)
        {
            float angle = std::acos((x - centerX) / radiusX);
            int y = std::round(radiusY * std::sin(angle) + centerY);
            float halfTileSize = tileLayer.getTileSize() / 2;
            Rect2D rect1 = Rect2D(tileLayer.getWorldPos(Vec2Int(x - evenX, y)).x,
                                  tileLayer.getWorldPos(Vec2Int(x - evenX, y)).y,
                                  tileLayer.getTileSize(),
                                  tileLayer.getTileSize(),
                                  context.editorState->color);
            tileLayer.add(rect1);
            Rect2D rect2 = Rect2D(tileLayer.getWorldPos(Vec2Int(x - evenX, 2 * centerY - y - evenY)).x,
                                  tileLayer.getWorldPos(Vec2Int(x - evenX, 2 * centerY - y - evenY)).y,
                                  tileLayer.getTileSize(),
                                  tileLayer.getTileSize(),
                                  context.editorState->color);
            tileLayer.add(rect2);
            Rect2D rect3 = Rect2D(tileLayer.getWorldPos(Vec2Int(2 * centerX - x, y)).x,
                                  tileLayer.getWorldPos(Vec2Int(2 * centerX - x, y)).y,
                                  tileLayer.getTileSize(),
                                  tileLayer.getTileSize(),
                                  context.editorState->color);
            tileLayer.add(rect3);
            Rect2D rect4 = Rect2D(tileLayer.getWorldPos(Vec2Int(2 * centerX - x, 2 * centerY - y - evenY)).x,
                                  tileLayer.getWorldPos(Vec2Int(2 * centerX - x, 2 * centerY - y - evenY)).y,
                                  tileLayer.getTileSize(),
                                  tileLayer.getTileSize(),
                                  context.editorState->color);
            tileLayer.add(rect4);
            // pixels.push([ x - evenX, y ]);
            // pixels.push([ x - evenX, 2 * yC - y - evenY ]);
            // pixels.push([ 2 * xC - x, y ]);
            // pixels.push([ 2 * xC - x, 2 * yC - y - evenY ]);
        }

        for (int y = boundsInt.minY; y <= centerY; y++)
        {
            float angle = std::asin((y - centerY) / radiusY);
            int x = std::round(radiusX * std::cos(angle) + centerX);
            float halfTileSize = tileLayer.getTileSize() / 2;
            Rect2D rect1 = Rect2D(tileLayer.getWorldPos(Vec2Int(x, y - evenY)).x,
                                  tileLayer.getWorldPos(Vec2Int(x, y - evenY)).y,
                                  tileLayer.getTileSize(),
                                  tileLayer.getTileSize(),
                                  context.editorState->color);
            tileLayer.add(rect1);
            Rect2D rect2 = Rect2D(tileLayer.getWorldPos(Vec2Int(2 * centerX - x - evenX, y - evenY)).x,
                                  tileLayer.getWorldPos(Vec2Int(2 * centerX - x - evenX, y - evenY)).y,
                                  tileLayer.getTileSize(),
                                  tileLayer.getTileSize(),
                                  context.editorState->color);
            tileLayer.add(rect2);
            Rect2D rect3 = Rect2D(tileLayer.getWorldPos(Vec2Int(x, 2 * centerY - y)).x,
                                  tileLayer.getWorldPos(Vec2Int(x, 2 * centerY - y)).y,
                                  tileLayer.getTileSize(),
                                  tileLayer.getTileSize(),
                                  context.editorState->color);
            tileLayer.add(rect3);
            Rect2D rect4 = Rect2D(tileLayer.getWorldPos(Vec2Int(2 * centerX - x - evenX, 2 * centerY - y)).x,
                                  tileLayer.getWorldPos(Vec2Int(2 * centerX - x - evenX, 2 * centerY - y)).y,
                                  tileLayer.getTileSize(),
                                  tileLayer.getTileSize(),
                                  context.editorState->color);
            tileLayer.add(rect4);
        }
    }
} // namespace editor
} // namespace spright
