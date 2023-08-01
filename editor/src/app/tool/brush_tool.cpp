#include "brush_tool.h"

namespace spright
{
namespace editor
{

    BrushTool::BrushTool(DocumentStore *documentStore) : m_documentStore(documentStore), Tool("brush")
    {
    }

    void BrushTool::setSize(int size)
    {
        m_Size = size;
    }

    void BrushTool::pointerMove(const ToolContext &context)
    {
        paint(context);
    }

    void BrushTool::pointerDown(const ToolContext &context)
    {
        paint(context);
    }

    void BrushTool::paint(const ToolContext &context)
    {
        if (context.pointer.isLeftButtonDown() == false)
        {
            return;
        }

        Camera &camera = m_documentStore->getActiveDocument().getCamera();

        Vec2 center2D = camera.getCenter2D();

        float zoom = camera.getZoom();

        Drawing *drawing = m_documentStore->getActiveDocument().getDrawingAt(context.pointer.curr);

        if (drawing != nullptr)
        {
            TileLayer &layer = drawing->getActiveLayer();

            TileUndo tileUndo = TileUndo::createForActiveTileLayer(*context.doc.document);

            for (int i = 0; i < m_Size; i++)
            {
                for (int j = 0; j < m_Size; j++)
                {
                    Vec2Int tilePos = layer.getTilePos(context.pointer.curr);

                    brush.paint(layer,
                                tilePos,
                                getColor(),
                                [&](std::shared_ptr<Rect2D> prev, std::shared_ptr<Rect2D> next) {
                                    tileUndo.addTile(prev, next);
                                });
                }
            }

            context.doc.document->getHistory()->add(std::make_shared<TileUndo>(tileUndo));
        }
    }
} // namespace editor
} // namespace spright
