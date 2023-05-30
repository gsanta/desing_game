#pragma once
#include "../brush.h"
#include "../tool/tool.h"

namespace spright
{
namespace editor
{
    class CircleTool : public Tool
    {
    public:
        CircleTool();

        void pointerMove(const ToolContext &) override;

        void pointerUp(const ToolContext &) override;

    private:
        void drawCircle(BoundsInt &bounds, int color, TileLayer &layer);

        BoundsInt getCircleBounds(const ToolContext &, const TileLayer &);

    private:
        BoundsInt m_PrevCircleBounds;
    };
} // namespace editor
} // namespace spright
