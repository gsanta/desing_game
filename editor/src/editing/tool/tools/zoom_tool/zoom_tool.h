#pragma once

#include "../../../../engine/scene/cameras/camera.h"
#include "../../../../engine/scene/cameras/ortho_projection_info.h"
#include "../../../document/document_store.h"
#include "../../context/tool_context.h"
#include "../../pixel_tool.h"

namespace spright
{
namespace editing
{
    using namespace ::spright::engine;

    class ZoomTool : public PixelTool
    {
    public:
        ZoomTool();

        void scroll(const ToolContext &toolContext) override;

    private:
        float m_ZoomFactor = 0.01f;
    };
} // namespace editing
} // namespace spright
