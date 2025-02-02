#include "line_tool.h"

#include "../color_picker_tool/color_picker_tool.h"

namespace spright
{
namespace editing
{
    LineTool::LineTool() : PixelTool("line", std::make_shared<RectangleCursor>(1, true))
    {
    }

    void LineTool::pointerMove(const ToolContext &context)
    {
        if (!context.pointer.isDown)
        {
            return;
        }

        TileLayer &foregroundLayer = context.doc.activeDrawing->getToolLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

        foregroundLayer.clear();

        drawLine(context.pointer.down,
                 context.pointer.curr,
                 context.tools->getColorPickerTool().getColor(),
                 activeLayer,
                 foregroundLayer);
    }

    void LineTool::pointerUp(ToolContext &context)
    {
        TileLayer &foregroundLayer = context.doc.activeDrawing->getToolLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

        foregroundLayer.clear();

        TileUndo tileUndo = TileUndo::createForActiveTileLayer(*context.doc.document, context.tools);

        drawLine(context.pointer.down,
                 context.pointer.curr,
                 context.tools->getColorPickerTool().getColor(),
                 activeLayer,
                 activeLayer,
                 &tileUndo);

        context.doc.document->getHistory()->add(std::make_shared<TileUndo>(tileUndo));
    }

    void LineTool::drawLine(Vec2 start,
                            Vec2 end,
                            int color,
                            TileLayer &tileLayer,
                            TileLayer &drawLayer,
                            TileUndo *tileUndo)
    {

        onRect2DCreate handleOnRect2DCreate = defaultRect2DCreate;

        if (tileUndo)
        {
            handleOnRect2DCreate = [&](std::shared_ptr<Rect2D> prev, std::shared_ptr<Rect2D> next) {
                tileUndo->addTile(prev, next);
            };
        }

        bool isHorizontalDir = std::abs(end.x - start.x) > std::abs(end.y - start.y);
        float xDelta = start.x - end.x == 0 ? 0.01 : start.x - end.x;
        float yDelta = start.y - end.y == 0 ? 0.01 : start.y - end.y;
        float tileSize = tileLayer.getTileSize();

        if (isHorizontalDir)
        {
            float slope = xDelta / yDelta;
            int len = std::round(std::abs(start.x - end.x) / tileSize);
            int neg = start.x < end.x ? 1 : -1;

            for (int i = 0; i < len; i++)
            {
                float x = start.x + i * tileSize * neg;
                float y = start.y + (x - start.x) / slope;
                Vec2Int tilePos = tileLayer.getTilePos(Vec2(x, y));

                m_Brush.paint(drawLayer, tilePos, color, handleOnRect2DCreate);
            }
        }
        else
        {
            float slope = yDelta / xDelta;
            int len = std::round(std::abs(start.y - end.y) / tileSize);
            int neg = start.y < end.y ? 1 : -1;

            for (int i = 0; i < len; i++)
            {
                float y = start.y + i * tileSize * neg;
                float x = start.x + (y - start.y) / slope;
                Vec2Int tilePos = tileLayer.getTilePos(Vec2(x, y));

                m_Brush.paint(drawLayer, tilePos, color, handleOnRect2DCreate);
            }
        }
    }

} // namespace editing
} // namespace spright
