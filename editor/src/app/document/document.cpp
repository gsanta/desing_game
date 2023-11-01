#include "document.h"

namespace spright
{
namespace editor
{
    Document::Document(const Bounds &bounds,
                       const Canvas &canvas,
                       const Camera &camera,
                       std::shared_ptr<DocumentHistory> history)
        : m_Canvas(canvas), m_Camera(camera), m_History(history)
    {
    }

    Document::Document(const Document &other) : m_Camera(other.m_Camera), m_Canvas(other.m_Canvas)
    {
        m_Drawings = other.m_Drawings;
        m_Drawing3ds = other.m_Drawing3ds;
        m_History = other.m_History;

        int activeCanvasIndex = other.getActiveCanvasIndex();

        m_ActiveCanvasIndex = other.m_ActiveCanvasIndex;
        m_ActiveCanvasType = other.m_ActiveCanvasType;

        for (Drawing &drawing : m_Drawings) {
            m_Canvases.push_back(&drawing);
        }

        for (Drawing3d &drawing : m_Drawing3ds)
        {
            m_Canvases.push_back(&drawing);
        }
    }

    Drawing *Document::getActiveDrawing()
    {
        if (m_ActiveCanvasIndex >= 0 && m_ActiveCanvasType == Canvas::Type::Drawing) {
            return &m_Drawings[m_ActiveCanvasIndex];
        }

        return nullptr;
    }

    int Document::getActiveCanvasIndex() const
    {
        return m_ActiveCanvasIndex;
    }

    Drawing &Document::getDrawing(size_t index)
    {
        return m_Drawings[index];
    }

    void Document::addDrawing(const Drawing &drawing)
    {
        m_Drawings.push_back(drawing);
        m_Canvases.push_back(&m_Drawings.back());

        if (m_ActiveCanvasIndex == -1)
        {
            m_ActiveCanvasIndex = 0;
            m_ActiveCanvasType = Canvas::Type::Drawing;
        }
    }

    Drawing &Document::getDrawing(std::string uuid)
    {
        std::vector<Drawing>::iterator it =
            std::find_if(m_Drawings.begin(), m_Drawings.end(), [&uuid](const Drawing &element) {
                return element.getUuid() == uuid;
            });

        if (it == m_Drawings.end())
        {
            throw std::invalid_argument("Drawing with uuid: " + uuid + " not found.");
        }

        return *it;
    }

    void Document::removeCanvas(const Canvas *canvas)
    {
        std::vector<Drawing>::iterator itDrawing =
            std::find_if(m_Drawings.begin(), m_Drawings.end(), [&canvas](const Drawing &element) {
                return &element == canvas;
            });

        if (itDrawing != m_Drawings.end())
        {
            m_Drawings.erase(itDrawing);
        }

        std::vector<Drawing3d>::iterator itDrawing3d =
            std::find_if(m_Drawing3ds.begin(), m_Drawing3ds.end(), [&canvas](const Drawing3d &element) {
                return &element == canvas;
            });

        if (itDrawing3d != m_Drawing3ds.end())
        {
            m_Drawing3ds.erase(itDrawing3d);
        }

        std::vector<Canvas *>::iterator itCanvas = std::find(m_Canvases.begin(), m_Canvases.end(), canvas);

        if (itCanvas != m_Canvases.end())
        {
            m_Canvases.erase(itCanvas);
        }
    }

    std::vector<Drawing> &Document::getDrawings()
    {
        return m_Drawings;
    }

    void Document::addDrawing3d(const Drawing3d &drawing)
    {
        m_Drawing3ds.push_back(drawing);
        m_Canvases.push_back(&m_Drawing3ds.back());
    }

    std::vector<Drawing3d> &Document::getDrawing3ds()
    {
        return m_Drawing3ds;
    }

    void Document::setActiveCanvas(const Canvas *canvas)
    {
        if (int drawingIndex = findDrawing(*canvas) != -1) {
            m_ActiveCanvasIndex = drawingIndex;
            m_ActiveCanvasType = Canvas::Type::Drawing;
        }

        if (int drawingIndex = findDrawing3d(*canvas) != -1)
        {
            m_ActiveCanvasIndex = drawingIndex;
            m_ActiveCanvasType = Canvas::Type::Drawing3d;
        }
    }

    std::vector<Canvas *> &Document::getCanvases()
    {
        return m_Canvases;
    }

    std::shared_ptr<DocumentHistory> Document::getHistory()
    {
        return m_History;
    }

    void Document::empty()
    {
        m_Drawings.clear();
    }

    Canvas &Document::getCanvas()
    {
        return m_Canvas;
    }

    Camera &Document::getCamera()
    {
        return m_Camera;
    }

    void Document::setCamera(const Camera &camera)
    {
        m_Camera = camera;
    }

    int Document::findDrawing(const Canvas &canvas)
    {
        std::vector<Drawing>::iterator it =
            std::find_if(m_Drawings.begin(), m_Drawings.end(), [&canvas](const Drawing &element) {
                return &element == &canvas;
            });

        if (it != m_Drawings.end())
        {
            return it - m_Drawings.begin();
        }

        return -1;
    }

    int Document::findDrawing3d(const Canvas &canvas)
    {
        std::vector<Drawing3d>::iterator it =
            std::find_if(m_Drawing3ds.begin(), m_Drawing3ds.end(), [&canvas](const Drawing3d &element) {
                return &element == &canvas;
            });

        if (it != m_Drawing3ds.end())
        {
            return it - m_Drawing3ds.begin();
        }

        return -1;
    }
} // namespace editor
} // namespace spright
