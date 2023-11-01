#pragma once

#include "../../engine/graphics/camera/camera.h"
#include "../../engine/graphics/camera/ortho_projection_info.h"
#include "../../engine/graphics/layer/group.h"
#include "../../engine/graphics/layer/tile_layer.h"
#include "../../engine/graphics/renderable/bounds.h"
#include "../../engine/structure/canvas.h"
#include "../../engine/structure/drawing3d.h"
#include "../event/event_emitter.h"
#include "../feature/frame/frame_player.h"
#include "drawing.h"
#include "frame.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace spright
{
namespace editor
{
    class DocumentHistory;

    using namespace ::spright::engine;

    class Document
    {
    public:
        Document(const Bounds &bounds,
                 const Canvas &canvas,
                 const Camera &camera,
                 std::shared_ptr<DocumentHistory> history);

        Document(const Document &other);

        //! Represents the Drawing() over which the pointer resides or over which a drag action started
        //! @return The active Drawing() or nullptr
        Drawing *getActiveDrawing();

        Drawing &getDrawing(size_t index);

        int getActiveCanvasIndex() const;

        void addDrawing(const Drawing &drawing);

        void removeCanvas(const Canvas *canvas);

        Drawing &getDrawing(std::string uuid);

        std::vector<Drawing> &getDrawings();

        void addDrawing3d(const Drawing3d &drawing);

        std::vector<Drawing3d> &getDrawing3ds();

        void setActiveCanvas(const Canvas *canvas);

        std::vector<Canvas *> &getCanvases();

        std::shared_ptr<DocumentHistory> getHistory();

        void empty();

        Canvas &getCanvas();

        Camera &getCamera();

        void setCamera(const Camera &camera);

    private:
        int findDrawing(const Canvas &canvas);

        int findDrawing3d(const Canvas &canvas);

    private:
        std::vector<Drawing> m_Drawings;

        std::vector<Drawing3d> m_Drawing3ds;

        std::vector<Canvas *> m_Canvases;

        int m_ActiveCanvasIndex = -1;

        Canvas::Type m_ActiveCanvasType = Canvas::Type::Drawing;

        Canvas m_Canvas;

        Camera m_Camera;

        std::shared_ptr<DocumentHistory> m_History;
    };
} // namespace editor
} // namespace spright
