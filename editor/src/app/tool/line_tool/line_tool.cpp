#include "line_tool.h"

namespace spright
{
namespace editor
{
    LineTool::LineTool() : Tool("line")
    {
    }

    void LineTool::pointerDown(const ToolContext &toolContext)
    {
    }

    void LineTool::pointerMove(const ToolContext &context)
    {
        if (!context.pointer.isDown)
        {
            return;
        }

        TileLayer &foregroundLayer = context.doc.activeDrawing->getForegroundLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

        foregroundLayer.clear();

        const Vec2 &down = context.pointer.down;
        const Vec2 &curr = context.pointer.curr;

        Vec2 start = down.x < curr.x ? down : curr;
        Vec2 end = down.x < curr.x ? curr : down;

        float slope = (start.x - end.x) / (start.y - end.y);

        for (float x = start.x; x < end.x; x += activeLayer.getTileSize())
        {
            float y = start.y + (x - start.x) / slope;
            Vec2Int tilePos = activeLayer.getTilePos(Vec2(x, y));

            brush.paint(foregroundLayer, tilePos, context.editorState->color);
        }
    }

    void LineTool::pointerUp(const ToolContext &context)
    {
        TileLayer &foregroundLayer = context.doc.activeDrawing->getForegroundLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

        for (Rect2D *rect : foregroundLayer.getRenderables())
        {
            activeLayer.add(*rect);
        }

        foregroundLayer.clear();
    }
} // namespace editor
} // namespace spright
