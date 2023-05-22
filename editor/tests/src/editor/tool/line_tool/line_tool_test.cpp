
#include "../src/app/tool/line_tool/line_tool.h"
#include "catch2/catch_test_macros.hpp"
#include "src/editor/test_helpers/document_store_builder.h"
#include "src/editor/test_helpers/tool_context_builder.h"
#include "../src/app/core/colors.h"

using namespace spright::editor;

TEST_CASE("LineTool", "[line-tool]")
{
    SECTION("can draw a straight horizontal line")
    {
        DocumentStore documentStore = DocumentStoreBuilder().build();
        ToolContext toolContext = ToolContextBuilder().withActiveDrawing(documentStore).build();

        LineTool lineTool;

        toolContext.pointer.curr = Vec2(1.0f, 1.1f);
        toolContext.pointer.down = toolContext.pointer.curr;

        lineTool.execPointerDown(toolContext);

        toolContext.pointer.isDown = true;

        toolContext.pointer.curr = Vec2(3.1f, 1.1f);

        lineTool.execPointerMove(toolContext);
        lineTool.execPointerUp(toolContext);

        TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();

        REQUIRE(layer.getRenderables().size() == 5);
        REQUIRE(layer.getAtWorldPos(Vec2(1.1f, 1.1f)) != nullptr);
        REQUIRE(layer.getAtWorldPos(Vec2(1.6f, 1.1f)) != nullptr);
        REQUIRE(layer.getAtWorldPos(Vec2(2.1f, 1.1f)) != nullptr);
        REQUIRE(layer.getAtWorldPos(Vec2(2.6, 1.1f)) != nullptr);
        REQUIRE(layer.getAtWorldPos(Vec2(3.1, 1.1f)) != nullptr);
    }
}