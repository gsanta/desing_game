#include "eraser_tool.h"

namespace spright
{
namespace editor
{

    EraserTool::EraserTool(DocumentStore *documentStore, int eraserSize)
        : m_documentStore(documentStore), m_Size(eraserSize), Tool("erase")
    {
        m_EraserStroke = EraserStroke(m_Size);
    }

    void EraserTool::pointerDown(PointerInfo &pointerInfo, DocumentInfo &documentInfo)
    {
        if (!documentInfo.hasActiveDrawing())
        {
            return;
        }

        TileLayer &activeLayer = documentInfo.activeDrawing->getActiveLayer();
        m_Eraser.erase(activeLayer, activeLayer.getTilePos(pointerInfo.curr), m_Size);
    }

    void EraserTool::pointerMove(PointerInfo &pointerInfo, DocumentInfo &documentInfo)
    {
        if (documentInfo.isLeavingDrawing && documentInfo.hasPrevDrawing())
        {
            m_EraserStroke.clear(documentInfo.prevDrawing->getForegroundLayer());
        }

        if (!documentInfo.hasActiveDrawing())
        {
            return;
        }

        TileLayer &activeLayer = documentInfo.activeDrawing->getActiveLayer();
        TileLayer &drawLayer = documentInfo.activeDrawing->getForegroundLayer();

        m_EraserStroke.draw(activeLayer, drawLayer, pointerInfo.curr);

        if (pointerInfo.isDown)
        {
            m_Eraser.erase(activeLayer, activeLayer.getTilePos(pointerInfo.curr), m_Size);
        }
    }

    void EraserTool::deactivate(DocumentInfo &documentInfo)
    {
        if (documentInfo.hasActiveDrawing())
        {
            m_EraserStroke.clear(documentInfo.activeDrawing->getForegroundLayer());
        }
    }
    void EraserTool::setOptions(std::string json)
    {
        nlohmann::json parsedJson = nlohmann::json::parse(json);

        m_Size = parsedJson["size"];
    }

    std::string EraserTool::getOptions()
    {
        nlohmann::json json;

        json["size"] = m_Size;

        return json.dump();
    }
} // namespace editor
} // namespace spright
