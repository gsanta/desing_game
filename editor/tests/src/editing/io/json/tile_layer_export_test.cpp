
#include "../../../test_helpers/builders/tile_layer_builder.h"
#include "../../../test_helpers/test_document_factory.h"
#include "../src/editing/io/json/tile_layer_export.h"
#include "../src/engine/graphics/colors.h"
#include "../src/engine/system/window/impl/headless/headless_window.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editing;

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
                                      .withTile(Vec2Int(1, 1), COLOR_YELLOW)
                                      .build();

            HeadlessWindow window(bounds.getWidth(), bounds.getHeight());
            DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(window);


            TileLayerExport exporter(std::make_shared<DocumentFactory>(documentFactory));


            nlohmann::json json = exporter.exportLayer(tileLayer);

            std::string a = json["tiles"].dump();

            REQUIRE(json["tile_size"].dump() == "1.0");
            REQUIRE(json["bounds"].dump() == "[-1.0,-1.0,1.0,1.0]");
            REQUIRE(json["tiles"].dump() == "[\"0xff0000ff:0\",\"0xffff0000:1\",\"0xff00ffff:3\"]");
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
                                      "\"name\": \"layer23\","
                                      "\"tile_size\": 1,"
                                      "\"bounds\": [-1.0,-1.0,1.0,1.0],"
                                      "\"tiles\": [\"0xff0000ff:0\",\"0xffff0000:2\"] }";
                nlohmann::json json = nlohmann::json::parse(jsonStr);

                Bounds bounds = Bounds::createWithPositions(-1.0f, -1.0f, 1.0f, 1.0f);

                HeadlessWindow window(bounds.getWidth(), bounds.getHeight());
                DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(window);


                TileLayerExport exporter(std::make_shared<DocumentFactory>(documentFactory));


                TileLayer tileLayer = exporter.importLayer(json);

                REQUIRE(tileLayer.getName() == "layer23");
                REQUIRE(tileLayer.getTiles().size() == 2);
                REQUIRE(tileLayer.getAtTileIndex(0) != nullptr);
                REQUIRE(tileLayer.getAtTileIndex(0)->getColor() == COLOR_RED);
                REQUIRE(tileLayer.getAtTileIndex(2) != nullptr);
                REQUIRE(tileLayer.getAtTileIndex(2)->getColor() == COLOR_BLUE);
                REQUIRE(tileLayer.getAtTileIndex(1) == nullptr);
                REQUIRE(tileLayer.getAtTileIndex(3) == nullptr);
            }
        }
    }
}
