#pragma once

#include "../../tool/tool.h"
#include "../../tool_handler.h"
#include "../../tool/tool_context.h"

namespace spright
{
namespace editor
{
    class ShearTool : public Tool
    {
    public:
        ShearTool();

        void execute(const ToolContext &toolContext);
    };
} // namespace editor
} // namespace spright
