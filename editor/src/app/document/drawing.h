#pragma once

#include "../../engine/graphics/camera/camera.h"
#include "../feature/frame/frame_player.h"
#include "drawing_state.h"
#include "frame_store.h"

namespace spright
{
namespace editor
{
    using namespace ::spright::engine;

    class Drawing : public Container
    {
    public:
        Drawing(Bounds bounds);

        Drawing(const Drawing &);

        Drawing &operator=(const Drawing &);

        FrameStore &getFrameStore();

        std::vector<FrameImpl> &getFrames();

        Frame &getActiveFrame();

        void setActiveFrame(size_t index);

        Frame &addFrame(const Frame &frame);

        void removeFrame(size_t index);

        Frame &getFrame(size_t frameIndex);

        TileLayer &getActiveLayer();

        TileLayer &addLayer(const TileLayer &tileLayer);

        TileLayer &getForegroundLayer();

        TileLayer &getBackgroundLayer();

        void addBackgroundLayer(const TileLayer &tileLayer);

        void addForegroundLayer(const TileLayer &tileLayer);

        std::string getJson();

        void render(const Camera &camera);

        DrawingState &getState();

        void resize(Bounds newBounds);

    private:
        std::vector<TileLayer> m_BackgroundLayers;

        std::vector<TileLayer> m_ForegroundLayers;

        std::vector<FrameImpl> m_Frames;

        size_t m_ActiveFrameIndex;

        size_t m_ActiveLayerIndex;

        DrawingState m_DrawingState;
    };
} // namespace editor
} // namespace spright
