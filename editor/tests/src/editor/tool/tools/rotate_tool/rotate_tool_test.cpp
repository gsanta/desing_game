#include "../../../test_helpers/builders/content_builder.h"
#include "../../../test_helpers/document_builder.h"
#include "../../../test_helpers/drawing_builder.h"
#include "../../../test_helpers/tool_context_builder.h"
#include "../src/app/tool/tools/rotate_tool/rotate_tool.h"
#include "../src/app/core/run_loop/test_timer.h"

#include <catch2/catch_test_macros.hpp>


SCENARIO("Rotate tool")
{
    // using namespace spright::editor;

    GIVEN("a shape drawn onto the active layer")
    {
        Document document = DocumentBuilder().withDrawing(DrawingBuilder().withBounds(Bounds(0, 0, 12, 12))).build();
        ToolContext toolContext = ToolContextBuilder().build(document);
        ContentBuilder &contentBuilder =
            ContentBuilder(document, toolContext).buildRect(BoundsInt(4, 1, 5, 3)).buildTile(Vec2Int(4, 0));

        Drawing &drawing = document.getActiveDrawing();
        TileLayer &activeLayer = drawing.getActiveLayer();
        TileLayer &tempLayer = drawing.getTempLayer();

        WHEN("the nothing is selected")
        {
            WHEN("executing a 90deg rotation")
            {
                THEN("shape is not rotated")
                {
                    REQUIRE(activeLayer.getTiles().size() == 7);

                    REQUIRE(activeLayer.getAtTilePos(4, 0) != nullptr);
                    REQUIRE(activeLayer.getAtTilePos(4, 1) != nullptr);
                    REQUIRE(activeLayer.getAtTilePos(5, 1) != nullptr);
                    REQUIRE(activeLayer.getAtTilePos(4, 2) != nullptr);
                    REQUIRE(activeLayer.getAtTilePos(5, 2) != nullptr);
                    REQUIRE(activeLayer.getAtTilePos(4, 3) != nullptr);
                    REQUIRE(activeLayer.getAtTilePos(5, 3) != nullptr);
                }
            }
        }

        WHEN("selecting the shape")
        {
            contentBuilder.selectRect(BoundsInt(4, 0, 5, 3));

            WHEN("executing a 90deg rotation")
            {
                THEN("it updates the tiles positions according to the rotation")
                {
                    RotateTool &rotateTool = toolContext.tools->getRotateTool();

                    contentBuilder.setPrevCurrDown(Vec2Int(4, 2));

                    rotateTool.execPointerDown(toolContext);

                    TestTimer::getInstance()->setElapsed(250);

                    rotateTool.execPointerMove(toolContext);

                    // contentBuilder.setCurr(Vec2Int(4, 1));

                    // rotateTool.execPointerMove(toolContext);

                    REQUIRE(activeLayer.getTiles().size() == 7);
                }
            }
        }
    }
}
