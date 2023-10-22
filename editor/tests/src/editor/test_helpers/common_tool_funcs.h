#pragma once

#include "../src/app/document/document.h"
#include "../src/app/tool/context/tool_context.h"
#include "../src/app/tool/tools/brush_tool/brush_tool.h"
#include "../src/app/tool/tools/rectangle_tool/rectangle_tool.h"
#include "../src/app/tool/tools/select_tool/select_tool.h"
#include "../src/engine/graphics/renderable/bounds_int.h"

using namespace ::spright::editor;

class CommonToolFuncs
{
public:
    CommonToolFuncs(Document &document, ToolContext &context);

    void buildRect(const BoundsInt &bounds);

    void buildTile(const Vec2Int &pos);

    void setPrevCurrDown(const Vec2Int &pos);

    void setCurr(const Vec2Int &pos);

    void selectTiles(const std::vector<Rect2D *> &tiles);

    void selectRect(const BoundsInt &bounds);

    void clickAt(const Vec2Int &pos, Tool &tool);

private:
    Document &m_Document;

    ToolContext &m_Context;
};
