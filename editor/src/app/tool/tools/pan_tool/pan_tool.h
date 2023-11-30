#pragma once

#include "../../../../engine/scene/cameras/camera2d.h"
#include "../../../../engine/scene/cameras/ortho_projection_info.h"
#include "../../context/tool_context.h"
#include "../../tool.h"

namespace spright
{
namespace editor
{
    using namespace ::spright::engine;

    class PanTool : public Tool
    {
    public:
        PanTool();

    private:
        void pointerMove(const ToolContext &) override;
    };
} // namespace editor
} // namespace spright
