#pragma once

#include "../../tool/tool.h"
#include "../../tool_handler.h"
#include "../../tool/tool_context.h"
#include "../../../algorithm/rotate.h"
// #include "../../../algorithm/shear_vertical.h"

namespace spright
{
namespace editor
{
    class ShearTool : public Tool
    {
    public:
        ShearTool();

        void execute(ToolContext &toolContext) override;
    };
} // namespace editor
} // namespace spright
