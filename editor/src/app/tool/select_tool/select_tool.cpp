#include "select_tool.h"

namespace spright
{
namespace editor
{

    SelectTool::SelectTool(std::shared_ptr<DocumentStore> documentStore)
        : Tool("select"), m_DocumentStore(documentStore), m_SelectionBuffer(std::make_shared<SelectionBuffer>())
    {
        m_BoxSelector = std::make_unique<BoxSelector>(m_SelectionBuffer);
        m_SelectionMover = std::make_unique<SelectionMover>(m_SelectionBuffer);
    }

    void SelectTool::pointerDown(const ToolContext &context)
    {
        if (context.doc.hasActiveDrawing())
        {
            TileLayer &foregroundLayer = context.doc.activeDrawing->getForegroundLayer();
            TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

            int tileIndex = foregroundLayer.getTileIndex(context.pointer.curr);

            m_IsMove = foregroundLayer.getAtTileIndex(tileIndex) != nullptr;
        }
    }

    void SelectTool::pointerMove(const ToolContext &context)
    {
        if (!context.pointer.isLeftButtonDown())
        {
            return;
        }


        if (context.pointer.isLeftButtonDown())
        {
            // std::cout << "pos: " << context.pointer.curr << std::endl;
        }

        TileLayer &tempLayer = context.doc.activeDrawing->getForegroundLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();
        if (m_IsMove)
        {

            m_SelectionMover->move(tempLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);

            m_SelectionMover->move(activeLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);

            m_SelectionBoundsDirty = true;
        }
        else
        {
            if (m_BoxSelector->isSelectionChanged(tempLayer,
                                                  context.pointer.curr,
                                                  context.pointer.prev,
                                                  context.pointer.down))
            {
                tempLayer.clear();
                m_BoxSelector->select(tempLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);
                m_SelectionBoundsDirty = true;
                fillTempLayer(tempLayer);
            }
        }
    }

    void SelectTool::pointerUp(const ToolContext &context)
    {
        if (!context.doc.hasActiveDrawing())
        {
            return;
        }

        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

        recalcTileIndexesAndBounds(activeLayer);

        if (!m_IsMove)
        {
            if (context.pointer.downDelta().length() < m_NoMovementTolerance)
            {
                TileLayer &foregroundLayer = context.doc.activeDrawing->getForegroundLayer();

                m_BoxSelector->clear();
            }
        }

        m_IsMove = false;
    }

    void SelectTool::recalcTileIndexesAndBounds(TileLayer &layer)
    {
        for (int tileIndex : m_SelectionBuffer->getTileIndexes())
        {
            Rect2D *tile = layer.getAtTileIndex(tileIndex);
            if (tile != nullptr)
            {
                layer.updateTileIndex(tile);
            }
        }
    }

    void SelectTool::setSelectedTiles(std::vector<int> indexes, TileLayer &tempLayer)
    {
        m_SelectionBoundsDirty = true;
        m_SelectionBuffer->setTileIndexes(std::move(indexes), tempLayer);
        fillTempLayer(tempLayer);
    }


    std::shared_ptr<SelectionBuffer> SelectTool::getSelectionBuffer()
    {
        return m_SelectionBuffer;
    }

    const Bounds &SelectTool::getSelectionBounds()
    {
        if (m_SelectionBoundsDirty)
        {
            updateBounds();
            m_SelectionBoundsDirty = false;
        }
        return m_SelectionBounds;
    }

    const BoundsInt &SelectTool::getSelectionTileBounds()
    {
        if (m_SelectionBoundsDirty)
        {
            TileLayer &tempLayer = m_DocumentStore->getActiveDocument().getActiveDrawing().getForegroundLayer();

            Bounds bounds = getSelectionBounds();
            Vec2Int bottomLeft = tempLayer.getTilePos(bounds.getBottomLeft());
            Vec2Int topRight = tempLayer.getTilePos(bounds.getTopRight());

            m_SelectionTileBounds = BoundsInt(bottomLeft, topRight);
        }

        return m_SelectionTileBounds;
    }

    void SelectTool::fillTempLayer(TileLayer &tempLayer)
    {
        float tileSize = tempLayer.getTileSize();
        unsigned int color = 0x800099ff;

        BoundsInt bounds = getSelectionTileBounds();

        tempLayer.clear();

        Vec2Int bottomLeft = bounds.getBottomLeft();
        Vec2Int topRight = bounds.getTopRight();

        for (int i = bottomLeft.x; i < topRight.x; i++)
        {
            for (int j = bottomLeft.y; j < topRight.y; j++) {
                Vec2 bottomLeft = tempLayer.getBottomLeftPos(Vec2Int(i, j));
                Rect2D rect(bottomLeft.x, bottomLeft.y, tileSize, tileSize, color);

                tempLayer.add(rect);
            }
        }

        // for (int index : m_SelectionBuffer->getTileIndexes())
        // {
        //     Vec2 bottomLeft = tempLayer.getBottomLeftPos(index);
        //     Rect2D rect(bottomLeft.x, bottomLeft.y, tileSize, tileSize, color);

        //     tempLayer.add(rect);
        // }
    }

    void SelectTool::updateBounds()
    {
        TileLayer &tempLayer = m_DocumentStore->getActiveDocument().getActiveDrawing().getForegroundLayer();

        int minX = std::numeric_limits<int>::max();
        int minY = std::numeric_limits<int>::max();
        int maxX = std::numeric_limits<int>::min();
        int maxY = std::numeric_limits<int>::min();

        for (int tileIndex : m_SelectionBuffer->getTileIndexes())
        {
            Vec2Int tilePos = tempLayer.getTilePos(tileIndex);

            if (tilePos.x < minX)
            {
                minX = tilePos.x;
            }
            else if (tilePos.x > maxX)
            {
                maxX = tilePos.x;
            }

            if (tilePos.y < minY)
            {
                minY = tilePos.y;
            }
            else if (tilePos.y > maxY)
            {
                maxY = tilePos.y;
            }
        }

        m_SelectionBounds = Bounds(tempLayer.getBottomLeftPos(Vec2Int(minX, minY)),
                                   tempLayer.getBottomLeftPos(Vec2Int(maxX, maxY)) + tempLayer.getTileSize());
    }
} // namespace editor
} // namespace spright
