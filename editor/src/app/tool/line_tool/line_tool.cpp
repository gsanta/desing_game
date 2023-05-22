#include "line_tool.h"

namespace spright
{
namespace editor
{
    LineTool::LineTool(): Tool("line") {

    }

    void LineTool::pointerDown(const ToolContext &toolContext)
    {

    }

    void LineTool::pointerMove(const ToolContext &context)
    {
        if (!context.pointer.isDown) {
            return;
        }

        TileLayer &foregroundLayer = context.doc.activeDrawing->getForegroundLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();
//        m_Rects.clear();

        std::cout << "clears" << std::endl;
        foregroundLayer.clear();

        Vec2 start = context.pointer.down;
        Vec2 end = context.pointer.curr;


//        if ((start - end).length() > 3) {
//            std::cout << start << " " << end << std::endl;
//        }

        for (float x = start.x; x < end.x; x += activeLayer.getTileSize())
        {
            Vec2Int tilePos = activeLayer.getTilePos(Vec2(x, start.y));

            brush.paint(foregroundLayer, tilePos, context.editorState->color);
        }
    }

    void LineTool::pointerUp(const ToolContext &context)
    {
        TileLayer &foregroundLayer = context.doc.activeDrawing->getForegroundLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

        for (Rect2D* rect : foregroundLayer.getRenderables()) {
            activeLayer.add(*rect);
        }

        foregroundLayer.clear();
    }
} // namespace editor
} // namespace spright