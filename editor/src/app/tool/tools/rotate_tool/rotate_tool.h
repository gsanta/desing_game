#pragma once

#include "../../../algorithm/rotate.h"
#include "../../../algorithm/tile_operations.h"
#include "../../tool/tool.h"
#include "../../tool/tool_context.h"
#include "../../tool_handler.h"
#include "../../../core/run_loop/timer.h"

#include <cmath>

namespace spright
{
namespace editor
{
    class RotateTool : public Tool
    {
    public:
        RotateTool();

        void setRotationInRad(float rad);

        void pointerDown(const ToolContext &toolContext) override;

        void pointerMove(const ToolContext &toolContext) override;

        void pointerUp(const ToolContext &toolContext) override;

        void execute(ToolContext &toolContext) override;

    private:
        float m_RotateInRad = 0;

        Timer *m_Timer;

        std::unique_ptr<TileView> m_OrigTiles;

        std::vector<int> m_OrigIndexes;

        Vec2 m_RotationCenter;
    };
} // namespace editor
} // namespace spright
