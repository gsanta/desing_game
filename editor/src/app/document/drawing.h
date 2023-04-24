#pragma once

#include "../../engine/graphics/camera/camera.h"
#include "../event/event_emitter.h"
#include "../feature/frame/frame_player.h"
#include "frame_store.h"

namespace spright
{
namespace editor
{

    using namespace ::spright::engine;

    class Drawing : public Container
    {
    public:
        Drawing(Bounds bounds, EventEmitter *eventEmitter);

        Drawing(const Drawing &);

        ~Drawing();

        FrameStore &getFrameStore();

        ActiveFrame &getActiveFrame();

        Frame &getFrame(size_t frameIndex);

        TileLayer &getActiveLayer();

        TileLayer &addLayer(const TileLayer &tileLayer);

        TileLayer &getForegroundLayer();

        TileLayer &getBackgroundLayer();

        std::string getJson();

        void render(const Camera &camera);

        FramePlayer &getFramePlayer();

    private:
        FrameStore m_FrameStore;
        FramePlayer *m_FramePlayer;
        EventEmitter *m_EventEmitter;
    };
} // namespace editor
} // namespace spright
