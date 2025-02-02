#include "./shear_tool.h"

#include "../../tools/select_tool/select_tool.h"

namespace spright
{
namespace editing
{
    ShearTool::ShearTool() : PixelTool("shear")
    {
    }

    void ShearTool::pointerDown(const ToolContext &toolContext)
    {
        TileLayer &activeLayer = toolContext.doc.activeDrawing->getTempLayerOfActiveLayer();
        const SelectionBuffer &selectionBuffer = toolContext.tools->getSelectTool().getSelectionBuffer();

        m_ImpactedArea = getBoundsOfImpactedArea(selectionBuffer.getTileBounds(), activeLayer.getTileBounds());

        m_Undo.reset(new TileUndo(*toolContext.doc.document, toolContext.tools));
        m_Undo->setPrevTiles(m_ImpactedArea, activeLayer);
        m_Undo->setPrevSelection(selectionBuffer.getTileIndexes());
        m_Undo->setNewTiles(m_ImpactedArea, activeLayer);
        m_Undo->setNewSelection(selectionBuffer.getTileIndexes());
    }

    void ShearTool::pointerMove(const ToolContext &toolContext)
    {
        TileLayer &activeLayer = toolContext.doc.activeDrawing->getTempLayerOfActiveLayer();
        const BoundsInt &selectionBounds = toolContext.tools->getSelectTool().getSelectionBuffer().getTileBounds();
        Vec2 center = activeLayer.getCenterPos(selectionBounds.getCenter());

        calcShearDirection(activeLayer, toolContext.pointer.curr, center);
        double angle = calcShearAngle(activeLayer, toolContext.pointer.curr, center);

        if (angle != m_PrevShearAngle)
        {
            m_Undo->undo(*toolContext.doc.document);

            shearSelection(toolContext, angle);

            const SelectionBuffer &selectionBuffer = toolContext.tools->getSelectTool().getSelectionBuffer();
            m_Undo->setNewTiles(m_ImpactedArea, activeLayer);
            m_Undo->setNewSelection(selectionBuffer.getTileIndexes());
            m_PrevShearAngle = angle;
        }
    }

    void ShearTool::pointerUp(ToolContext &context)
    {
        TileLayer &tempLayer = context.doc.activeDrawing->getTempLayerOfActiveLayer();
        TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();

        SelectionBuffer &selectionBuffer = context.tools->getSelectTool().getSelectionBuffer();

        context.doc.document->getHistory()->add(std::make_shared<TileUndo>(*m_Undo.get()));
        m_PrevShearAngle = 0;
    }

    void ShearTool::shearSelection(const ToolContext &toolContext, double angle)
    {
        TileLayer &activeLayer = toolContext.doc.activeDrawing->getTempLayerOfActiveLayer();

        const BoundsInt &selectionBounds = toolContext.tools->getSelectTool().getSelectionBuffer().getTileBounds();

        if (angle != 0)
        {
            m_ShearInRad = angle;
            execute(toolContext);
        }
    }

    void ShearTool::execute(const ToolContext &toolContext)
    {
        SelectTool &selectTool = toolContext.tools->getSelectTool();

        const BoundsInt &selectionBounds = toolContext.tools->getSelectTool().getSelectionBuffer().getTileBounds();

        TileLayer &activeLayer = toolContext.doc.activeDrawing->getTempLayerOfActiveLayer();
        BoundsInt bounds = BoundsInt(selectionBounds.getBottomLeft(), selectionBounds.getTopRight());

        std::vector<int> newIndexes;

        if (m_IsHorizontal)
        {
            newIndexes = shear_horizontal(activeLayer, bounds, m_ShearInRad);
        }
        else
        {
            newIndexes = shear_vertical(activeLayer, bounds, m_ShearInRad);
        }

        selectTool.syncSelection(*toolContext.doc.activeDrawing, newIndexes);
    }

    void ShearTool::setShearInRad(float rad)
    {
        m_ShearInRad = rad;
    }

    void ShearTool::setShearDirectionAsVertical()
    {
        m_IsHorizontal = false;
    }

    void ShearTool::setShearDirectionAsHorizontal()
    {
        m_IsHorizontal = true;
    }

    void ShearTool::calcShearDirection(const TileLayer &layer, const Vec2 &cursorPos, const Vec2 &centerPos)
    {
        Vec2Int cursorTile = layer.getTilePos(cursorPos);
        Vec2Int centerTile = layer.getTilePos(centerPos);
        Vec2Int delta = cursorTile - centerTile;

        double len = cursorTile.distance(centerTile);

        if (std::abs(delta.x) < std::abs(delta.y))
        {
            setShearDirectionAsVertical();
        }
        else
        {
            setShearDirectionAsHorizontal();
        }
    }


    double ShearTool::calcShearAngle(const TileLayer &layer, const Vec2 &cursorPos, const Vec2 &centerPos) const
    {
        Vec2Int cursorTile = layer.getTilePos(cursorPos);
        Vec2Int centerTile = layer.getTilePos(centerPos);
        Vec2Int delta = cursorTile - centerTile;

        double len = cursorTile.distance(centerTile);

        double sign = 1.0f;

        if (m_IsHorizontal)
        {
            if (cursorTile.x < centerTile.x)
            {
                sign = -1.0f;
            }
        }
        else
        {
            if (cursorTile.y < centerTile.y)
            {
                sign = -1.0f;
            }
        }

        //10deg
        double shearIncrement = 0.174533;

        double multiplier = (int)(len / m_TileLenghtFor10DegShear);

        double angle = shearIncrement * multiplier * sign;

        if (angle > m_MaxShear)
        {
            return m_MaxShear;
        }
        else if (angle < -m_MaxShear)
        {
            return -m_MaxShear;
        }
        else
        {
            return angle;
        }
    }

    BoundsInt ShearTool::getBoundsOfImpactedArea(const BoundsInt &selectionBounds, const BoundsInt &maxBounds) const
    {
        Vec2Int center = selectionBounds.getCenter();
        int size = selectionBounds.getWidth();

        int bottomLeftX = center.x - size > maxBounds.minX ? center.x - size : maxBounds.minX;
        int bottomLeftY = center.y - size > maxBounds.minY ? center.y - size : maxBounds.minY;
        int topRightX = center.x + size < maxBounds.maxX ? center.x + size : maxBounds.maxX;
        int topRightY = center.y + size < maxBounds.maxY ? center.y + size : maxBounds.maxY;

        return BoundsInt(bottomLeftX, bottomLeftY, topRightX, topRightY);
    }

    int ShearTool::getTileLenghtFor10DegShear() const
    {
        return m_TileLenghtFor10DegShear;
    }
} // namespace editing
} // namespace spright
