#include "document.h"

namespace spright
{
namespace editor
{
    Document::Document(Bounds bounds, Camera camera, std::shared_ptr<DocumentHistory> history)
        : Canvas(bounds), m_Camera(camera), m_History(history), m_ActiveDrawing(0)
    {
    }

    Document::Document(const Document &other) : Canvas(other.getBounds()), m_Camera(other.m_Camera)
    {
        m_Drawings = other.m_Drawings;
        if (other.m_Canvas)
        {
            m_Canvas = std::unique_ptr<BackgroundCanvas>(new BackgroundCanvas(*other.m_Canvas));
        }
        m_ActiveDrawing = other.m_ActiveDrawing;
        m_History = other.m_History;
    }

    Drawing *Document::getActiveDrawing()
    {
        return m_Drawings[m_ActiveDrawing].get();
    }

    size_t Document::getActiveDrawingIndex() const
    {
        return m_ActiveDrawing;
    }

    Drawing &Document::getDrawing(size_t index)
    {
        return *m_Drawings[index];
    }

    void Document::addDrawing(std::shared_ptr<Drawing> drawing)
    {
        m_Drawings.push_back(drawing);
    }

    Drawing &Document::getDrawing(int id)
    {
        return *m_Drawings[id];
    }

    void Document::removeActiveDrawing()
    {
        m_Drawings.erase(m_Drawings.begin() + m_ActiveDrawing);
    }

    std::vector<std::shared_ptr<Drawing>> &Document::getDrawings()
    {
        return m_Drawings;
    }

    std::shared_ptr<DocumentHistory> Document::getHistory()
    {
        return m_History;
    }

    void Document::empty()
    {
        m_Drawings.clear();
    }

    BackgroundCanvas &Document::getCanvas()
    {
        return *m_Canvas;
    }

    Camera &Document::getCamera()
    {
        return m_Camera;
    }

    void Document::setCamera(const Camera &camera)
    {
        m_Camera = camera;
    }
} // namespace editor
} // namespace spright
