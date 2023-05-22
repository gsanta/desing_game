#pragma once

#include "../tool/tool.h"
#include "../brush.h"

namespace spright
{
namespace editor
{
    class LineTool : public Tool
    {
    public:
        LineTool();

        void pointerDown(const ToolContext &toolContext) override;

        void pointerMove(const ToolContext &toolContext) override;

        void pointerUp(const ToolContext &toolContext) override;

    private:
        std::vector<Rect2D*> m_Rects;

        Brush brush;
    };
} // namespace editor
} // namespace spright
