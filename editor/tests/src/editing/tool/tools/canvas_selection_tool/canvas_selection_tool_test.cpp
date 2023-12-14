
#include "../../../../test_helpers/builders/document_store_builder.h"
#include "../../../../test_helpers/builders/drawing_builder.h"
#include "../../../../test_helpers/builders/tool_context_builder.h"
#include "../../../../test_helpers/common_tool_funcs.h"
#include "../../../../test_helpers/matchers/equals_bounds_matcher.h"
#include "../src/editing/tool/tools/canvas_selection_tool/canvas_border_component.h"
#include "../src/editing/tool/tools/canvas_selection_tool/canvas_selection_tool.h"
#include "../src/editing/utils/conversions.h"
#include "../src/engine/system/window/impl/headless/headless_window.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editing;
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

        Canvas *canvas1 = document.getCanvas(0);
        canvas1->addComponent<CanvasBorderComponent>();
        Canvas *canvas2 = document.getCanvas(1);
        canvas2->addComponent<CanvasBorderComponent>();

        ToolContext toolContext = ToolContextBuilder().build(document);

        CommonToolFuncs commonToolFuncs(document, toolContext);

        HeadlessWindow window(4, 4);

        CanvasSelectionTool canvasSelectionTool;

        WHEN("pointer down on the first drawing")
        {
            commonToolFuncs.setPrevCurrDown(Vec2(0, 0));
            canvasSelectionTool.execPointerDown(toolContext);

            THEN("it sets it as the active drawing")
            {
                REQUIRE(document.getActiveCanvas() != nullptr);
                REQUIRE(document.getActiveCanvas() == canvas1);
            }

            WHEN("pointer down on the second drawing")
            {
                commonToolFuncs.setPrevCurrDown(Vec2(6.0, -1.0));
                canvasSelectionTool.execPointerDown(toolContext);

                THEN("it sets it as the active drawing")
                {
                    REQUIRE(document.getActiveCanvas() != nullptr);
                    REQUIRE(document.getActiveCanvas() == canvas2);
                }

                THEN("highlights the active drawing")
                {
                    Group<Renderable2D> &gizmoLayer = canvas2->getGizmoLayer();

                    REQUIRE(gizmoLayer.getRenderables().size() == 4);

                    for (Renderable2D *rect : gizmoLayer.getRenderables())
                    {
                        REQUIRE(dynamic_cast<Rect2D *>(rect)->getColor() == COLOR_BLUE);
                    }
                }

                THEN("removes the highlight from the prev active layer")
                {
                    Group<Renderable2D> &gizmoLayer = canvas1->getGizmoLayer();

                    for (Renderable2D *rect : gizmoLayer.getRenderables())
                    {
                        REQUIRE(dynamic_cast<Rect2D *>(rect)->getColor() == COLOR_WHITE);
                    }
                }
            }
        }
    }
}
