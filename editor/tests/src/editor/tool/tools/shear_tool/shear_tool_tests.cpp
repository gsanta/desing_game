#include "../../../test_helpers/document_builder.h"
#include "../../../test_helpers/drawing_builder.h"
#include "../../../test_helpers/tile_layer_builder.h"
#include "../../../test_helpers/tool_context_builder.h"
#include "../src/app/tool/rectangle_tool/rectangle_tool.h"
#include "../src/app/tool/select_tool/select_tool.h"
#include "../src/app/tool/tools/shear_tool/shear_tool.h"

#include <catch2/catch_test_macros.hpp>

SCENARIO("Shear tool")
{
    using namespace spright::editor;

    GIVEN("A shear tool with horizontal direction")
    {
        Document document =
            DocumentBuilder()
                .withDrawing(DrawingBuilder().withBounds(Bounds(0, 0, 12, 12)).withTileLayer(TileLayerBuilder()))
                .build();

        Drawing &drawing = document.getActiveDrawing();
        TileLayer &activeLayer = drawing.getActiveLayer();

        Vec2 start = activeLayer.getCenterPos(Vec2Int(2, 1));
        ToolContext toolContext =
            ToolContextBuilder().withPointerInfo(PointerInfoBuilder().with(start, start, start)).build(document);


        RectangleTool rectTool;
        rectTool.setFilled(true);

        toolContext.pointer.isDown = true;

        rectTool.execPointerDown(toolContext);

        toolContext.pointer.curr = activeLayer.getCenterPos(Vec2Int(5, 4));

        rectTool.execPointerMove(toolContext);
        rectTool.execPointerUp(toolContext);

        ShearTool shearTool;
        shearTool.setShearDirectionAsHorizontal();


        WHEN("executing a shear")
        {
            shearTool.execute(toolContext);
        }
    }
}
