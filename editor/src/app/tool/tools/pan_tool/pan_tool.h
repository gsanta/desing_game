#pragma once

#include "../../../../engine/graphics/camera/camera2d.h"
#include "../../../../engine/graphics/camera/ortho_projection_info.h"
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
