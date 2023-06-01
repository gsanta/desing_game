
#include "../src/app/tool/circle_tool/circle_tool.h"
#include "src/editor/test_helpers/document_store_builder.h"
#include "src/editor/test_helpers/tool_context_builder.h"

#include <catch2/catch_test_macros.hpp>

using namespace ::spright::engine;
using namespace ::spright::editor;

void REQUIRE_ELLIPSE(TileLayer &layer)
{
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

void REQUIRE_CIRCLE(TileLayer &layer)
{
    REQUIRE(layer.getRenderables().size() == 16);

    REQUIRE(layer.getAtTilePos(0, 2) != nullptr);
    REQUIRE(layer.getAtTilePos(0, 3) != nullptr);
    REQUIRE(layer.getAtTilePos(0, 4) != nullptr);
    REQUIRE(layer.getAtTilePos(1, 1) != nullptr);
    REQUIRE(layer.getAtTilePos(1, 5) != nullptr);
    REQUIRE(layer.getAtTilePos(2, 0) != nullptr);
    REQUIRE(layer.getAtTilePos(2, 6) != nullptr);
    REQUIRE(layer.getAtTilePos(3, 0) != nullptr);
    REQUIRE(layer.getAtTilePos(3, 6) != nullptr);
    REQUIRE(layer.getAtTilePos(4, 0) != nullptr);
    REQUIRE(layer.getAtTilePos(4, 6) != nullptr);
    REQUIRE(layer.getAtTilePos(5, 1) != nullptr);
    REQUIRE(layer.getAtTilePos(5, 5) != nullptr);
    REQUIRE(layer.getAtTilePos(6, 2) != nullptr);
    REQUIRE(layer.getAtTilePos(6, 3) != nullptr);
    REQUIRE(layer.getAtTilePos(6, 4) != nullptr);
}

TEST_CASE("CircleTool", "[circle_tool]")
{
    SECTION("draws a horizontal oval shape on pointer up")
    {
        DocumentStore documentStore = DocumentStoreBuilder().build();
        ToolContext toolContext = ToolContextBuilder().withActiveDrawing(documentStore).build();

        TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();

        CircleTool circleTool;

        toolContext.pointer.down = layer.getWorldPos(Vec2Int(0, 0));
        toolContext.pointer.curr = layer.getWorldPos(Vec2Int(4.0f, 2.0f));
        toolContext.pointer.isDown = true;

        circleTool.pointerUp(toolContext);

        REQUIRE_ELLIPSE(layer);
    }

    SECTION("draws a circle on pointer up")
    {
        DocumentStore documentStore = DocumentStoreBuilder().build();

        ToolContext toolContext = ToolContextBuilder().withActiveDrawing(documentStore).build();
        TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();

        CircleTool circleTool;

        toolContext.pointer.down = layer.getWorldPos(Vec2Int(0, 0));
        toolContext.pointer.curr = layer.getWorldPos(Vec2Int(6.0f, 6.0f));
        toolContext.pointer.isDown = true;

        circleTool.pointerUp(toolContext);

        REQUIRE_CIRCLE(layer);
    }

    SECTION("draws on pointer drag")
    {
        DocumentStore documentStore = DocumentStoreBuilder().build();

        ToolContext toolContext = ToolContextBuilder().withActiveDrawing(documentStore).build();
        TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getForegroundLayer();

        CircleTool circleTool;

        toolContext.pointer.down = layer.getWorldPos(Vec2Int(0, 0));
        toolContext.pointer.curr = layer.getWorldPos(Vec2Int(4.0f, 2.0f));
        toolContext.pointer.isDown = true;

        circleTool.pointerMove(toolContext);

        toolContext.pointer.curr = layer.getWorldPos(Vec2Int(6.0f, 6.0f));

        REQUIRE_ELLIPSE(layer);

        circleTool.pointerMove(toolContext);

        REQUIRE_CIRCLE(layer);
    }
}
