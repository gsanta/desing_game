#include "../../../test_helpers/builders/document_builder.h"
#include "../../../test_helpers/builders/drawing_builder.h"
#include "../../../test_helpers/test_document_factory.h"
#include "../src/editing/io/json/json_io.h"
#include "../src/editing/utils/conversions.h"
#include "../src/engine/graphics/colors.h"
#include "../src/engine/scene/canvas/tile_canvas.h"
#include "../src/engine/system/window/impl/headless/headless_window.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editing;

SCENARIO("JsonIO")
{
    WHEN("the user exports a document")
    {
        THEN("the json contains all the relevant information")
        {
            Bounds bounds = Bounds::createWithPositions(-1.0f, -1.0f, 1.0f, 1.0f);

            TileCanvas canvas =
                DrawingBuilder()
                    .withFrame(
                        FrameBuilder()
                            .withTileLayer(TileLayerBuilder().withTileSize(1).withBounds(bounds).withTile(Vec2Int(0, 0),
                                                                                                          COLOR_RED))
                            .withTileLayer(TileLayerBuilder().withTileSize(1).withBounds(bounds).withTile(Vec2Int(1, 0),
                                                                                                          COLOR_BLUE)))
                    .withFrame(
                        FrameBuilder()
                            .withTileLayer(TileLayerBuilder().withTileSize(1).withBounds(bounds).withTile(Vec2Int(0, 1),
                                                                                                          COLOR_RED))
                            .withTileLayer(TileLayerBuilder().withTileSize(1).withBounds(bounds).withTile(Vec2Int(1, 1),
                                                                                                          COLOR_BLUE)))
                    .build();

            HeadlessWindow window(bounds.getWidth(), bounds.getHeight());
            DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(window);

            Document document = DocumentBuilder().withEmptyDocument().build();

            document.addCanvas(canvas);

            JsonIO jsonIO(std::make_shared<DocumentFactory>(documentFactory));

            nlohmann::json json = jsonIO.exportDocument(document);

            REQUIRE(json["frames"].size() == 2);
            REQUIRE(json["frames"][0]["layers"].size() == 2);

            REQUIRE(json["frames"][0]["layers"][0]["bounds"].dump() == "[-1.0,-1.0,1.0,1.0]");
            REQUIRE(json["frames"][0]["layers"][0]["tiles"].dump() == "[\"0xff0000ff:0\"]");

            REQUIRE(json["frames"][0]["layers"][1]["bounds"].dump() == "[-1.0,-1.0,1.0,1.0]");
            REQUIRE(json["frames"][0]["layers"][1]["tiles"].dump() == "[\"0xffff0000:1\"]");

            REQUIRE(json["frames"][1]["layers"][0]["bounds"].dump() == "[-1.0,-1.0,1.0,1.0]");
            REQUIRE(json["frames"][1]["layers"][0]["tiles"].dump() == "[\"0xff0000ff:2\"]");

            REQUIRE(json["frames"][1]["layers"][1]["bounds"].dump() == "[-1.0,-1.0,1.0,1.0]");
            REQUIRE(json["frames"][1]["layers"][1]["tiles"].dump() == "[\"0xffff0000:3\"]");
        }
    }

    WHEN("the user imports a document from json")
    {
        THEN("the created document contains all the relevant information")
        {

            const char *jsonStr = "{\"frames\":"
                                  "["
                                  "{"
                                  "\"layers\":"
                                  "["
                                  "{"
                                  "\"bounds\":[-1.0,-1.0,1.0,1.0],"
                                  "\"index\":0,"
                                  "\"name\":\"layer_1\","
                                  "\"tile_size\":1.0,"
                                  "\"tiles\":[\"0xff0000ff:0\"]"
                                  "},"
                                  "{"
                                  "\"bounds\":[-1.0,-1.0,1.0,1.0],"
                                  "\"index\":1,"
                                  "\"name\":\"layer_2\","
                                  "\"tile_size\":1.0,"
                                  "\"tiles\":[\"0xffff0000:1\"]"
                                  "}"
                                  "]"
                                  "},"
                                  "{"
                                  "\"layers\":"
                                  "["
                                  "{"
                                  "\"bounds\":[-1.0,-1.0,1.0,1.0],"
                                  "\"index\":0,"
                                  "\"name\":\"layer_1\","
                                  "\"tile_size\":1.0,"
                                  "\"tiles\":[\"0xff0000ff:2\"]"
                                  "},"
                                  "{"
                                  "\"bounds\":[-1.0,-1.0,1.0,1.0],"
                                  "\"index\":1,"
                                  "\"name\":\"layer_2\","
                                  "\"tile_size\":1.0,"
                                  "\"tiles\":[\"0xffff0000:3\"]"
                                  "}"
                                  "]"
                                  "}"
                                  "]"
                                  "}";

            Bounds bounds = Bounds::createWithPositions(-1.0f, -1.0f, 1.0f, 1.0f);

            HeadlessWindow window(bounds.getWidth(), bounds.getHeight());
            DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(window);

            JsonIO jsonIO(std::make_shared<DocumentFactory>(documentFactory));

            Document document = jsonIO.importDocument(jsonStr);

            TileCanvas &canvas = get_active_tile_canvas(document);

            REQUIRE(canvas.getFrames().size() == 2);

            REQUIRE(canvas.getFrames()[0].getLayers().size() == 2);

            REQUIRE(canvas.getFrames()[0].getLayer(0).getName() == "layer_1");
            REQUIRE(canvas.getFrames()[0].getLayer(0).getTiles().size() == 1);
            REQUIRE(canvas.getFrames()[0].getLayer(0).getAtTileIndex(0)->getColor() == COLOR_RED);

            REQUIRE(canvas.getFrames()[0].getLayer(1).getName() == "layer_2");
            REQUIRE(canvas.getFrames()[0].getLayer(1).getTiles().size() == 1);
            REQUIRE(canvas.getFrames()[0].getLayer(1).getAtTileIndex(1)->getColor() == COLOR_BLUE);

            REQUIRE(canvas.getFrames()[0].getLayers().size() == 2);

            REQUIRE(canvas.getFrames()[1].getLayer(0).getName() == "layer_1");
            REQUIRE(canvas.getFrames()[1].getLayer(0).getTiles().size() == 1);
            REQUIRE(canvas.getFrames()[1].getLayer(0).getAtTileIndex(2)->getColor() == COLOR_RED);

            REQUIRE(canvas.getFrames()[1].getLayer(1).getName() == "layer_2");
            REQUIRE(canvas.getFrames()[1].getLayer(1).getTiles().size() == 1);
            REQUIRE(canvas.getFrames()[1].getLayer(1).getAtTileIndex(3)->getColor() == COLOR_BLUE);
        }
    }
}
