#pragma once
#include "../tool/tool.h"

namespace spright
{
namespace editor
{

    class CircleTool : public Tool
    {
    public:
        CircleTool();
        void pointerUp(const ToolContext &) override;
    };
} // namespace editor
} // namespace spright
