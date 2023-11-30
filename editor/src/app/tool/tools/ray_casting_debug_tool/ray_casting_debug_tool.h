#pragma once

#include "../../../../engine/scene/cameras/arc_rotate_camera.h"
#include "../../../../engine/scene/cameras/ortho_projection_info.h"
#include "../../../../engine/graphics/mesh/meshes/line3d.h"
#include "../../context/tool_context.h"
#include "../../tool.h"

namespace spright
{
namespace editor
{
    using namespace ::spright::engine;

    class RayCastingDebugTool : public Tool
    {
    public:
        RayCastingDebugTool();

    private:
        void pointerDown(const ToolContext &) override;

        void deactivate(const ToolContext &) override;

    private:
        float m_LineThickness = 0.1f;

        std::vector<Mesh *> m_Lines;
    };
} // namespace editor
} // namespace spright
