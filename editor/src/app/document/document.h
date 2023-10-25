#pragma once

#include "../../engine/graphics/camera/camera.h"
#include "../../engine/graphics/camera/ortho_projection_info.h"
#include "../../engine/graphics/layer/group.h"
#include "../../engine/graphics/layer/tile_layer.h"
#include "../../engine/graphics/renderable/bounds.h"
#include "../../engine/structure/canvas/canvas.h"
#include "../../engine/structure/canvas/background_canvas.h"
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

    class Document : public Canvas
    {
    public:
        Document(Bounds bounds, Camera m_Camera, std::shared_ptr<DocumentHistory> history);

        Document(const Document &other);

        //! Represents the Drawing() over which the pointer resides or over which a drag action started
        //! @return The active Drawing() or nullptr
        Drawing *getActiveDrawing();

        Drawing &getDrawing(size_t index);

        size_t getActiveDrawingIndex() const;

        void addDrawing(std::shared_ptr<Drawing> drawing);

        void removeActiveDrawing();

        Drawing &getDrawing(int id);

        std::vector<std::shared_ptr<Drawing>> &getDrawings();

        std::shared_ptr<DocumentHistory> getHistory();

        void empty();

        BackgroundCanvas &getCanvas();

        Camera &getCamera();

        void setCamera(const Camera &camera);

    private:
        std::vector<std::shared_ptr<Drawing>> m_Drawings;

        std::unique_ptr<BackgroundCanvas> m_Canvas;

        size_t m_ActiveDrawing;

        Camera m_Camera;

        std::shared_ptr<DocumentHistory> m_History;
    };
} // namespace editor
} // namespace spright
