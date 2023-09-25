#pragma once

#include "../../tool/tool.h"
#include "../../tool_handler.h"
#include "../../tool/tool_context.h"
#include "../../../algorithm/rotate.h"

namespace spright
{
namespace editor
{
    class RotateTool : public Tool
    {
    public:
        RotateTool();

        void execute(ToolContext &toolContext) override;
    };
} // namespace editor
} // namespace spright
