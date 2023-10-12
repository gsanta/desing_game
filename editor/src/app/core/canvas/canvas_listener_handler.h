#pragma once

#include "../../../engine/system/window/input_listener.h"
#include "../../tool/context/pointer_info.h"
#include "canvas_listener.h"

#include <algorithm>
#include <vector>

namespace spright
{
namespace editor
{
    using namespace ::spright::engine;

    class CanvasListenerHandler : public InputListener
    {
    private:
        std::vector<CanvasListener *> m_Listeners;
        PointerInfo m_PointerInfo;

    public:
        virtual void onMouseUp(bool buttons[3]) override;
        virtual void onMouseDown(bool buttons[3]) override;
        virtual void onMouseMove(double x, double y) override;


        void addListener(CanvasListener *listener);
        void removeListener(CanvasListener *listener);
    };

} // namespace editor
} // namespace spright
