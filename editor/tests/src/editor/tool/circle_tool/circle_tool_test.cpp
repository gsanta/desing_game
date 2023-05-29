
#include "../src/app/tool/circle_tool/circle_tool.h"
#include "src/editor/test_helpers/document_store_builder.h"
#include "src/editor/test_helpers/tool_context_builder.h"

#include <catch2/catch_test_macros.hpp>

using namespace ::spright::engine;
using namespace ::spright::editor;

TEST_CASE("CircleTool", "[circle_tool]") {
    SECTION("it can draw a circle on mouseUp") {
        DocumentStore documentStore = DocumentStoreBuilder().build();
        ToolContext toolContext = ToolContextBuilder().withActiveDrawing(documentStore).build();

        TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();

        CircleTool circleTool;

        toolContext.pointer.down = layer.getWorldPos(Vec2Int(0, 0));
        toolContext.pointer.curr = layer.getWorldPos(Vec2Int(4.0f, 2.0f));
        toolContext.pointer.isDown = true;

        circleTool.pointerUp(toolContext);


        Vec2 wp1 = layer.getWorldPos(Vec2Int(0, 0));
        Vec2 wp2 = layer.getWorldPos(Vec2Int(1, 5));

        REQUIRE(layer.getRenderables().size() == 8);

        REQUIRE(layer.getAtTilePos(0, 1) != nullptr);
        REQUIRE(layer.getAtTilePos(1, 2) != nullptr);
        REQUIRE(layer.getAtTilePos(2, 2) != nullptr);
        REQUIRE(layer.getAtTilePos(3, 2) != nullptr);
        REQUIRE(layer.getAtTilePos(4, 1) != nullptr);
        REQUIRE(layer.getAtTilePos(3, 0) != nullptr);
        REQUIRE(layer.getAtTilePos(2, 0) != nullptr);
        REQUIRE(layer.getAtTilePos(1, 0) != nullptr);
    }
}
