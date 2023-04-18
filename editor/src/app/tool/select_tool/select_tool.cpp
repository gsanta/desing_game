#include "select_tool.h"

namespace spright
{
namespace editor
{

    SelectTool::SelectTool(DocumentStore *documentStore) : m_DocumentStore(documentStore), Tool("select")
    {
    }

    void SelectTool::pointerDown(const ToolContext &context)
    {
        if (context.doc.hasActiveDrawing())
        {
            TileLayer &foregroundLayer = context.doc.activeDrawing->getForegroundLayer();
            TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

            if (!m_SelectionBox)
            {
                m_SelectionBox.reset(new SelectionBox(foregroundLayer));
                m_RectSelector.reset(new RectSelector(activeLayer));
            }

            m_IsMove = m_SelectionBox->isInsideSelection(context.pointer.curr);

            if (!m_IsMove)
            {
                m_SelectionBox.reset(new SelectionBox(foregroundLayer));
                m_RectSelector.reset(new RectSelector(activeLayer));
                m_SelectionBox->setSelectionStart(context.pointer.curr);
            }
            else
            {
                m_SelectionBox->setMoveStart(context.pointer.curr);
            }
        }
    }

    void SelectTool::pointerUp(const ToolContext &context)
    {
        if (!context.doc.hasActiveDrawing())
        {
            return;
        }

        if (Vec2::distance(context.pointer.down, context.pointer.curr) < m_NoMovementTolerance)
        {
            makePointSelection(context);
        }
        else
        {
            m_RectSelector->setSelection(context.pointer.down, context.pointer.curr);
        }

        m_IsMove = false;
    }

    void SelectTool::pointerMove(const ToolContext &context)
    {
        if (!context.pointer.isLeftButtonDown())
        {
            return;
        }

        if (m_IsMove)
        {
            Vec2 delta = m_SelectionBox->setMoveEnd(context.pointer.curr);
            m_RectSelector->moveSelectionWith(delta);
        }
        else
        {
            m_SelectionBox->setSelectionEnd(context.pointer.curr);
        }
    }

    void SelectTool::makePointSelection(const ToolContext &context)
    {
        if (!context.doc.activeDrawing)
        {
            return;
        }
        TileLayer &tileLayer = context.doc.activeDrawing->getActiveLayer();
        Camera &camera = m_DocumentStore->getActiveDocument().getCamera();
        Vec2 model = camera.screenToModel(context.pointer.curr);

        Vec2Int tilePos = tileLayer.getTilePos(model);
        int tileIndex = tileLayer.getTileIndex(tilePos.x, tilePos.y);
        Renderable2D *renderable = tileLayer.getAtTileIndex(tileIndex);

        if (renderable != nullptr)
        {
            Rect2D *sprite = static_cast<Rect2D *>(renderable);
            m_Data.push_back(sprite);
            m_OrigPositions.push_back(Vec2(sprite->getPosition().x, sprite->getPosition().y));

            Vec2 spritePos = sprite->getPosition2d();
            float tileSize = tileLayer.getTileSize();
        }
    }
} // namespace editor
} // namespace spright
