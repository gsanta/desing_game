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

        // only relevant when using execute directly, without using pointer events
        void setShearInRad(float rad);

        // only relevant when using execute directly, without using pointer events
        void setShearDirectionAsVertical();

        // only relevant when using execute directly, without using pointer events
        void setShearDirectionAsHorizontal();

    private:
        float m_ShearInRad = 0;

        float m_IsHorizontal = true;
    };
} // namespace editor
} // namespace spright
