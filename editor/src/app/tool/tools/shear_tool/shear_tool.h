#pragma once

#include "../../../algorithm/rotate.h"
#include "../../tool/tool.h"
#include "../../tool/tool_context.h"

namespace spright
{
namespace editor
{
    class ShearTool : public Tool
    {
    public:
        ShearTool();

        void execute(ToolContext &toolContext) override;

        void setShearInRad(float rad);

        void setShearDirectionAsVertical();

        void setShearDirectionAsHorizontal();

    private:
        float m_ShearInRad = 0;

        float m_IsHorizontal = true;
    };
} // namespace editor
} // namespace spright
