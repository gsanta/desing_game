#pragma once

// #include "../color_picker_tool.h"
// #include "../select_tool/select_tool.h"
// #include "../tools/shear_tool/shear_tool.h"
// #include "../tool/tool.h"

#include <vector>

namespace spright
{
namespace editor
{
    class Tool;
    class SelectTool;
    class ShearTool;
    class ColorPickerTool;

    class ToolStore
    {
    public:
        Tool *getTool(std::string name) const;

        void addTool(Tool *tool);

        SelectTool &getSelectTool();

        ColorPickerTool &getColorPickerTool();

        ShearTool &getShearTool();

    private:
        std::vector<Tool *> m_Tools;
    };
} // namespace editor
} // namespace spright
