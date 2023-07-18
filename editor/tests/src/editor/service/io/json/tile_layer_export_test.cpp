
#include "../../../test_helpers/test_document_factory.h"
#include "../../../test_helpers/tile_layer_builder.h"
#include "../src/app/core/colors.h"
#include "../src/app/service/io/json/tile_layer_export.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editor;

SCENARIO("TileLayerExport")
{
    WHEN("the user exports a tile layer")
    {
        THEN("the json contains all the relevant information")
        {
            Bounds bounds = Bounds::createWithPositions(-1.0f, -1.0f, 1.0f, 1.0f);
            TileLayer tileLayer = TileLayerBuilder()
                                      .withBounds(bounds)
                                      .withTileSize(1)
                                      .withTile(Vec2Int(0, 0), COLOR_RED)
                                      .withTile(Vec2Int(1, 0), COLOR_BLUE)
                                      .build();

            Container container(bounds);
            DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(container);


            TileLayerExport exporter(&documentFactory);


            nlohmann::json json = exporter.exportLayer(tileLayer);

            REQUIRE(json["bounds"].dump() == "[-1.0,-1.0,1.0,1.1]");
            REQUIRE(json["tiles"].dump() == "[4278190335,4294901760,-1,-1]");
        }
    }

    GIVEN("a json representation of a tile layer")
    {
        WHEN("the user imports it")
        {
            THEN("the imported tile layer is equal to the json representation")
            {
                const char *jsonStr = "{"
                                   "\"index\": 0,"
                                   "\"layerType\": \"tile\","
                                   "\"name\": \"\","
                                   "\"tileH\": 32,"
                                   "\"tileW\": 32,"
                                   "\"bounds\": [-1.0,-1.0,1.0,1.1],"
                                   "\"tiles\": [4278190335,4294901760,-1,-1] }";
                nlohmann::json json = nlohmann::json::parse(jsonStr);

                Bounds bounds = Bounds::createWithPositions(-1.0f, -1.0f, 1.0f, 1.0f);
                // TileLayer tileLayer = TileLayerBuilder()
                //                           .withBounds(bounds)
                //                           .withTileSize(1)
                //                           .withTile(Vec2Int(0, 0), COLOR_RED)
                //                           .withTile(Vec2Int(1, 0), COLOR_BLUE)
                //                           .build();

                Container container(bounds);
                DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(container);


                TileLayerExport exporter(&documentFactory);


                TileLayer tileLayer = exporter.importLayer(json);

                REQUIRE(tileLayer.getRenderables().size() == 2);
            }
        }
    }
}
