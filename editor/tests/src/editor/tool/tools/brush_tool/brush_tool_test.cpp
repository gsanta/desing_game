#include "../src/app/tool/tools/brush_tool/brush_tool.h"
#include "../../../test_helpers/document_builder.h"
#include "../../../test_helpers/drawing_builder.h"
#include "../../../test_helpers/tool_context_builder.h"
#include "../../../test_helpers/builders/content_builder.h"

#include <catch2/catch_test_macros.hpp>

SCENARIO("Brush tool")
{
    GIVEN("an empty canvas")
    {
        Document document = DocumentBuilder().withDrawing(DrawingBuilder().withBounds(Bounds(-3.0, -3.0, 3.0, 3.0))).build();
        BrushTool brushTool;
        ToolContext toolContext = ToolContextBuilder().build(document);

        ContentBuilder contentBuilder(document, toolContext);
        TileLayer &layer = document.getActiveLayer();

        WHEN("drawing a sequence of pixels without releasing the mouse")
        {

            toolContext.pointer.curr = layer.getCenterPos(Vec2Int(1, 1));
            toolContext.pointer.down = toolContext.pointer.curr;

            toolContext.pointer.buttons[0] = true;
            brushTool.execPointerDown(toolContext);
            brushTool.execPointerMove(toolContext);

            toolContext.pointer.curr = layer.getCenterPos(Vec2Int(2, 1));
            brushTool.execPointerMove(toolContext);

            toolContext.pointer.curr = layer.getCenterPos(Vec2Int(2, 2));
            brushTool.execPointerMove(toolContext);
            brushTool.execPointerUp(toolContext);

            WHEN("calling undo")
            {
                THEN("it removes all of the pixels")
                {

                    document.getHistory()->undo(document);

                    REQUIRE(layer.getTiles().size() == 0);

                    WHEN("calling redo")
                    {
                        THEN("it restores all of the pixels")
                        {
                            document.getHistory()->redo(document);

                            REQUIRE(layer.getTiles().size() == 3);
                            REQUIRE(layer.getAtTilePos(1, 1) != nullptr);
                            REQUIRE(layer.getAtTilePos(2, 1) != nullptr);
                            REQUIRE(layer.getAtTilePos(2, 2) != nullptr);
                        }
                    }
                }
            }
        }

        WHEN("drawing outside of the drawing's bounds") {
            contentBuilder.setPrevCurrDown(Vec2Int(7, 0));
            brushTool.execPointerDown(toolContext);
            brushTool.execPointerUp(toolContext);

            THEN("does not add the tile to the layer") {
                REQUIRE(layer.getTiles().size() == 0);
            }
        }
    }
}
