
#include "../src/app/tool/tool_handler.h"
#include "../src/engine/system/window/impl/headless/headless_window.h"
#include "../test_helpers/builders/document_store_builder.h"
#include "../test_helpers/builders/drawing_builder.h"

#include <catch2/catch_test_macros.hpp>

using namespace ::spright::editor;
using namespace ::spright::engine;

SCENARIO("Tool handler")
{
    GIVEN("a document with drawings")
    {
        DocumentStore documentStore = DocumentStoreBuilder()
                                          .withDocumentBounds(Bounds(-10.0, -10.0, 10.0, 10.0))
                                          .withDrawing(DrawingBuilder().withBounds(Bounds(-3.0f, -3.0f, 3.0f, 3.0f)))
                                          .withDrawing(DrawingBuilder().withBounds(Bounds(5.0f, -2.0f, 7.0f, 4.0f)))
                                          .build();

        Document &document = documentStore.getActiveDocument();

        HeadlessWindow window(4, 4);

        ToolHandler toolHandler(&documentStore);

        WHEN("pointer moves over the first drawing")
        {
            Vec2Int screenPos = document.getCamera().worldToScreenPos(0, 0);
            toolHandler.onMouseMove(screenPos.x, screenPos.y);

            THEN("it sets it as the active drawing")
            {
                REQUIRE(document.getActiveDrawing() != nullptr);
                REQUIRE(document.getActiveDrawing() == &document.getDrawings()[0]);
            }
        }

        WHEN("pointer moves over the second drawing")
        {
            Vec2Int screenPos = document.getCamera().worldToScreenPos(6.0, 2.0);
            toolHandler.onMouseMove(screenPos.x, screenPos.y);

            THEN("it sets it as the active drawing")
            {
                REQUIRE(document.getActiveDrawing() != nullptr);
                REQUIRE(document.getActiveDrawing() == &document.getDrawings()[1]);
            }
        }

        WHEN("pointer is not over a drawing")
        {
            Vec2Int screenPos = document.getCamera().worldToScreenPos(4.0, 2.0);
            toolHandler.onMouseMove(screenPos.x, screenPos.y);

            THEN("it sets the active drawing to null")
            {
                REQUIRE(document.getActiveDrawing() == nullptr);
            }
        }

        WHEN("pointer is down over a drawing") {
            Vec2Int screenPos = document.getCamera().worldToScreenPos(6.0, 2.0);
            toolHandler.onMouseMove(screenPos.x, screenPos.y);

            bool buttons[3] = {true, false, false};

            toolHandler.onMouseDown(buttons);

            WHEN("moving pointer out of the drawing") {
                screenPos = document.getCamera().worldToScreenPos(4.0, 2.0);
                toolHandler.onMouseMove(screenPos.x, screenPos.y);

                THEN("the active drawing remains") {
                    REQUIRE(document.getActiveDrawing() != nullptr);
                    REQUIRE(document.getActiveDrawing() == &document.getDrawings()[1]);
                }
            }
        }
    }
}
