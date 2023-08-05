#include "../../test_helpers/document_builder.h"
#include "../../test_helpers/document_info_builder.h"
#include "../../test_helpers/document_store_builder.h"
#include "../../test_helpers/drawing_builder.h"
#include "../../test_helpers/matchers/equals_bounds_matcher.h"
#include "../../test_helpers/pointer_info_builder.h"
#include "../../test_helpers/test_document_factory.h"
#include "../../test_helpers/tile_layer_builder.h"
#include "../../test_helpers/tool_context_builder.h"
#include "../src/app/document/document_store.h"
#include "../src/app/document/factory/document_factory.h"
#include "../src/app/tool/brush.h"
#include "../src/app/tool/eraser_tool/eraser_tool.h"
#include "../src/app/tool/tool/tool_context.h"
#include "../src/engine/graphics/impl/headless/headless_renderer2d.h"
#include "../src/engine/graphics/impl/headless/headless_shader.h"
#include "../src/engine/graphics/layer/group.h"
#include "../src/engine/graphics/renderable/rect2d.h"
#include "../src/engine/system/window/impl/headless/headless_window.h"

#include <catch2/catch_test_macros.hpp>

using namespace ::spright::engine;
using namespace ::spright::editor;

SCENARIO("Erase tool")
{
    GIVEN("a document with an active layer with pixels")
    {
        Document document = DocumentBuilder()
                                .withDrawing(DrawingBuilder().withTileLayer(TileLayerBuilder()
                                                                                .withTile(Vec2Int(0, 0))
                                                                                .withTile(Vec2Int(1, 0))
                                                                                .withTile(Vec2Int(2, 0))
                                                                                .withTile(Vec2Int(0, 1))
                                                                                .withTile(Vec2Int(1, 1))
                                                                                .withTile(Vec2Int(2, 1))
                                                                                .withTile(Vec2Int(0, 2))
                                                                                .withTile(Vec2Int(1, 2))
                                                                                .withTile(Vec2Int(2, 2))))
                                .build();
        TileLayer &activeLayer = document.getActiveDrawing().getActiveLayer();

        ToolContext toolContext =
            ToolContextBuilder()
                .withPointerInfo(PointerInfoBuilder().withCurr(activeLayer.getWorldPos(Vec2Int(1, 1))))
                .withDocumentInfo(DocumentInfoBuilder().withActiveDrawing(&document.getActiveDrawing()))
                .build();
        toolContext.doc.document = &document;

        EraserTool eraseTool(1);

        WHEN("clicking with the erase tool")
        {
            eraseTool.execPointerDown(toolContext);

            THEN("it erases the pixels at the click position")
            {
                REQUIRE(activeLayer.getRenderables().size() == 8);
                REQUIRE(activeLayer.getAtTilePos(0, 0) != nullptr);
                REQUIRE(activeLayer.getAtTilePos(1, 0) != nullptr);
                REQUIRE(activeLayer.getAtTilePos(2, 0) != nullptr);
                REQUIRE(activeLayer.getAtTilePos(0, 1) != nullptr);
                REQUIRE(activeLayer.getAtTilePos(1, 1) == nullptr);
                REQUIRE(activeLayer.getAtTilePos(2, 1) != nullptr);
                REQUIRE(activeLayer.getAtTilePos(0, 2) != nullptr);
                REQUIRE(activeLayer.getAtTilePos(1, 2) != nullptr);
                REQUIRE(activeLayer.getAtTilePos(2, 2) != nullptr);
            }

            WHEN("undoing the last action")
            {
                document.getHistory()->undo(document);

                THEN("it restores the erased pixels")
                {

                    REQUIRE(activeLayer.getRenderables().size() == 9);
                    REQUIRE(activeLayer.getAtTilePos(1, 1) != nullptr);
                }

                WHEN("redoing the last action")
                {
                    THEN("it removes the previously restored pixels")
                    {
                        document.getHistory()->redo(document);

                        REQUIRE(activeLayer.getRenderables().size() == 8);
                        REQUIRE(activeLayer.getAtTilePos(1, 1) == nullptr);
                    }
                }
            }
        }

        WHEN("dragging with the erase tool")
        {
            toolContext.pointer.curr = activeLayer.getWorldPos(Vec2Int(1, 0));
            toolContext.pointer.down = toolContext.pointer.curr;
            toolContext.pointer.isDown = true;

            eraseTool.execPointerDown(toolContext);
            eraseTool.execPointerMove(toolContext);

            toolContext.pointer.curr = activeLayer.getWorldPos(Vec2Int(2, 0));
            eraseTool.execPointerMove(toolContext);

            toolContext.pointer.curr = activeLayer.getWorldPos(Vec2Int(2, 1));
            eraseTool.execPointerMove(toolContext);
            eraseTool.execPointerUp(toolContext);

            THEN("it erases the pixels at the drag positions")
            {
                REQUIRE(activeLayer.getRenderables().size() == 6);
                REQUIRE(activeLayer.getAtTilePos(1, 0) == nullptr);
                REQUIRE(activeLayer.getAtTilePos(2, 0) == nullptr);
                REQUIRE(activeLayer.getAtTilePos(2, 1) == nullptr);
            }

            WHEN("undoing the last action")
            {
                document.getHistory()->undo(document);

                THEN("it restores all of the pixels erased during the drag")
                {
                    REQUIRE(activeLayer.getRenderables().size() == 9);
                    REQUIRE(activeLayer.getAtTilePos(1, 0) != nullptr);
                    REQUIRE(activeLayer.getAtTilePos(2, 0) != nullptr);
                    REQUIRE(activeLayer.getAtTilePos(2, 1) != nullptr);
                }
            }
        }
    }

    GIVEN("an empty document")
    {
        Document document = DocumentBuilder().withDrawing(DrawingBuilder().withBounds(Bounds(0, 0, 4, 4))).build();
        TileLayer &foregroundLayer1 = document.getActiveDrawing().getForegroundLayer();

        ToolContext toolContext = ToolContextBuilder().withDocument(document).build();

        EraserTool eraseTool(1);

        WHEN("moving the mouse")
        {
            toolContext.pointer.curr = foregroundLayer1.getWorldPos(Vec2Int(2, 1));
            eraseTool.execPointerMove(toolContext);

            THEN("erase tool cursor follows the mouse")
            {
                float dashSize = eraseTool.getStrokeSize();

                REQUIRE(foregroundLayer1.getRenderables().size() == 4);
                // top
                REQUIRE_THAT(foregroundLayer1.getRenderables()[0]->getBounds(),
                             EqualsBounds(Bounds(2.0f, 2.0 - dashSize / 2.0f, 1.0f, dashSize)));
                // bottom
                REQUIRE_THAT(foregroundLayer1.getRenderables()[2]->getBounds(),
                             EqualsBounds(Bounds(2.0f, 1.0 - dashSize / 2.0f, 1.0f, dashSize)));
                // left
                REQUIRE_THAT(foregroundLayer1.getRenderables()[1]->getBounds(),
                             EqualsBounds(Bounds(3.0 - dashSize / 2.0, 1.0, dashSize, 1.0)));
                // right
                REQUIRE_THAT(foregroundLayer1.getRenderables()[3]->getBounds(),
                             EqualsBounds(Bounds(2.0 - dashSize / 2.0, 1.0, dashSize, 1.0)));

                toolContext.pointer.curr = foregroundLayer1.getWorldPos(Vec2Int(3, 1));
                eraseTool.execPointerMove(toolContext);

                REQUIRE(foregroundLayer1.getRenderables().size() == 4);
                // top
                REQUIRE_THAT(foregroundLayer1.getRenderables()[0]->getBounds(),
                             EqualsBounds(Bounds(3.0f, 2.0 - dashSize / 2.0f, 1.0f, dashSize)));
                // bottom
                REQUIRE_THAT(foregroundLayer1.getRenderables()[2]->getBounds(),
                             EqualsBounds(Bounds(3.0f, 1.0 - dashSize / 2.0f, 1.0f, dashSize)));
                // left
                REQUIRE_THAT(foregroundLayer1.getRenderables()[1]->getBounds(),
                             EqualsBounds(Bounds(4.0 - dashSize / 2.0, 1.0, dashSize, 1.0)));
                // // right
                REQUIRE_THAT(foregroundLayer1.getRenderables()[3]->getBounds(),
                             EqualsBounds(Bounds(3.0 - dashSize / 2.0, 1.0, dashSize, 1.0)));
            }
        }
    }
}
