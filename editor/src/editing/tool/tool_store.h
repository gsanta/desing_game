#pragma once

#include <string>
#include <vector>

namespace spright
{
namespace editing
{
    class Tool;
    class SelectTool;
    class ShearTool;
    class ColorPickerTool;
    class RotateTool;
    class MoveTool;
    class BrushTool;

    class ToolStore
    {
    public:
        Tool *getTool(std::string name) const;

        void addTool(Tool *tool);

        SelectTool &getSelectTool();

        ColorPickerTool &getColorPickerTool();

        ShearTool &getShearTool();

        RotateTool &getRotateTool();

        MoveTool &getMoveTool();

        BrushTool &getBrushTool();

    private:
        std::vector<Tool *> m_Tools;
    };
} // namespace editing
} // namespace spright
