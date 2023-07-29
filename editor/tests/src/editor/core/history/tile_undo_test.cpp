#include <catch2/catch_test_macros.hpp>
#include "../../test_helpers/tile_layer_builder.h"
#include "../../test_helpers/drawing_builder.h"
#include "../../test_helpers/document_builder.h"
#include "../../test_helpers/builders/tile_builder.h"
#include "../src/app/core/colors.h"
#include "../../mocks/test_editor.h"

SCENARIO("TileUndo")
{
    GIVEN("the user calls undo")
    {
        Document document = DocumentBuilder().build();
        TestEditor editor(document);

        Drawing drawing = DrawingBuilder()
                        .withFrame(FrameBuilder().withTileLayer(
                                        TileLayerBuilder()
                                            .withTileSize(1)
                                            .withBounds(Bounds::createWithPositions(-2.0f, -2.0f, 2.0f, 2.0f))
                                            //   .withTile(Vec2Int(-5, 0), COLOR_RED)
                                            // .withTile(Vec2Int(0, 0), COLOR_RED)
                                            // .withTile(Vec2Int(1, 0), COLOR_RED)
                                            // .withTile(Vec2Int(1, 1), COLOR_RED)
                                            ),
                                    2)
                        .build();

        document.addDrawing(drawing);

        THEN("it undoes the changes on the tile layer")
        {
            TileLayer &layer = document.getDrawings()[0].getFrames()[1].getLayers()[1];

            TileBuilder tileBuilder(layer);

            layer.add(tileBuilder.withPos(Vec2Int(0, 0)).build());
            REQUIRE(1 == 2);
        }
    }
}
