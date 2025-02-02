#pragma once

#include "../../../../engine/scene/cameras/camera2d.h"
#include "../../../../engine/scene/cameras/ortho_projection_info.h"
#include "../../context/tool_context.h"
#include "../../pixel_tool.h"

namespace spright
{
namespace editing
{
    using namespace ::spright::engine;

    class PanTool : public PixelTool
    {
    public:
        PanTool();

    private:
        void pointerMove(const ToolContext &) override;
    };
} // namespace editing
} // namespace spright
