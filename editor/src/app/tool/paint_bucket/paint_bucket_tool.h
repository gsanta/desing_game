#pragma once

#include "../tool/tool.h"
#include "../tool/tool_context.h"
#include "../../../engine/graphics/camera/camera.h"
#include "queue_linear_flood_fill.h"
#include "../../service/services.h"
#include "../../document/document_store.h"

namespace spright { namespace editor {
    using namespace ::spright::engine;
    using namespace ::spright::maths;

    class PaintBucketTool : public Tool
    {
    private:
        QueueLinearFloodFill m_FloodFill;
        Services* m_Services;

    public:
        PaintBucketTool(Services *services);
        void pointerUp(ToolContext &) override;
    };
}}
