#include "../../test_helpers/document_info_builder.h"
#include "../../test_helpers/document_store_builder.h"
#include "../../test_helpers/pointer_info_builder.h"
#include "../../test_helpers/tool_context_builder.h"
#include "../src/app/tool/select_tool/select_tool.h"

#include <catch2/catch_test_macros.hpp>

SCENARIO("Select tool")
{

    GIVEN("A select tool")
    {
        std::shared_ptr<DocumentStore> documentStore = std::make_shared<DocumentStore>(
            DocumentStoreBuilder()
                .withDrawing(DrawingBuilder().withTileLayer(TileLayerBuilder().withTileFill()))
                .build());
        Drawing &activeDrawing = documentStore->getActiveDocument().getDrawings()[0];

        ToolContext toolContext =
            ToolContextBuilder().withDocumentInfo(DocumentInfoBuilder().withActiveDrawing(&activeDrawing)).build();

        SelectTool selectTool(documentStore);

        WHEN("making a selection")
        {
            TileLayer &tempLayer = activeDrawing.getForegroundLayer();

            toolContext.pointer.curr = tempLayer.getCenterPos(Vec2Int(1, 1));
            toolContext.pointer.prev = toolContext.pointer.curr;
            toolContext.pointer.down = toolContext.pointer.curr;

            selectTool.pointerDown(toolContext);

            toolContext.pointer.isDown = true;

            toolContext.pointer.curr = tempLayer.getCenterPos(Vec2Int(2, 2));
            selectTool.pointerMove(toolContext);

            selectTool.pointerUp(toolContext);

            THEN("it draws the selection to the temp layer")
            {
                REQUIRE(tempLayer.getTiles().size() == 4);
                REQUIRE(tempLayer.getAtTilePos(1, 1) != nullptr);
                REQUIRE(tempLayer.getAtTilePos(2, 1) != nullptr);
                REQUIRE(tempLayer.getAtTilePos(1, 2) != nullptr);
                REQUIRE(tempLayer.getAtTilePos(2, 2) != nullptr);
            }

            THEN("sets the selected tiles on the active layer")
            {
                TileLayer &activeLayer = activeDrawing.getActiveLayer();

                std::shared_ptr<SelectionBuffer> buffer = selectTool.getSelectionBuffer();

                REQUIRE(selectTool.getSelectionBuffer()->getTileIndexes().size() == 4);
                REQUIRE(buffer->containsIndex(tempLayer.getTileIndex(1, 1)) == true);
                REQUIRE(buffer->containsIndex(tempLayer.getTileIndex(2, 1)) == true);
                REQUIRE(buffer->containsIndex(tempLayer.getTileIndex(1, 2)) == true);
                REQUIRE(buffer->containsIndex(tempLayer.getTileIndex(2, 2)) == true);
            }

            WHEN("making another selection") {
                THEN("previous selection is cleared") {

                }
            }
        }
    }
}
TEST_CASE("SelectTool", "[select-tool]")
{
    using namespace ::spright::engine;
    using namespace ::spright::editor;

    SECTION("sets the selection to the active drawing")
    {
        std::shared_ptr<DocumentStore> documentStore = std::make_shared<DocumentStore>(DocumentStoreBuilder().build());
        Drawing &activeDrawing = documentStore->getActiveDocument().getDrawings()[0];

        ToolContext toolContext =
            ToolContextBuilder().withDocumentInfo(DocumentInfoBuilder().withActiveDrawing(&activeDrawing)).build();

        SelectTool selectTool(documentStore);

        selectTool.pointerDown(toolContext);

        toolContext.pointer.isDown = true;

        selectTool.pointerMove(toolContext);
        toolContext.pointer.prev = toolContext.pointer.curr;
        toolContext.pointer.curr = Vec2(2.0f, 2.0f);

        selectTool.pointerUp(toolContext);

        REQUIRE(activeDrawing.getState().getBounds() == Bounds(0, 0, 0, 0));
    }
}
