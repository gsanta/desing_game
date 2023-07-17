
#include "../../../test_helpers/test_document_factory.h"
#include "../../../test_helpers/tile_layer_builder.h"
#include "../src/app/core/colors.h"
#include "../src/app/service/io/json/tile_layer_export.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editor;

SCENARIO("TileLayerExport")
{
    GIVEN("the user exports a tile layer")
    {
        WHEN("hello")
        {

            THEN("the json contains all the relevant information")
            {
                Bounds bounds = Bounds::createWithPositions(-1.0f, 1.0f, -1.0f, 1.0f);
                TileLayer tileLayer = TileLayerBuilder()
                                          .withBounds(bounds)
                                          .withTile(Vec2Int(0, 0), COLOR_RED)
                                          .withTile(Vec2Int(1, 0), COLOR_BLUE)
                                          .build();

                Container container(bounds);
                DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(container);


                TileLayerExport exporter(&documentFactory);
                // TileLayer layer("layer",
                //                 Group<Rect2D>(new HeadlessRenderer2D()),
                //                 Bounds::createWithPositions(-1.0f, 1.0f, -1.0f, 1.0f));

                // layer.add(Rect2D(0, 0, 1, 1, 0x00000000));


                REQUIRE(exporter.exportLayer(tileLayer)["tiles"] == "");
            }
        }
    }
}
