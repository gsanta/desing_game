#include "../src/app/algorithm/flip.h"
#include "../src/app/core/colors.h"
#include "../src/engine/graphics/layer/tileLayer.h"
#include "../test_helpers/document_store_builder.h"
#include "../test_helpers/drawing_builder.h"
#include "../test_helpers/tile_layer_builder.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editor;
using namespace spright::engine;

TEST_CASE("flip_horizontal", "[flip-horizontal]")
{
    SECTION("can flip a layer")
    {
        DocumentStore documentStore =
            DocumentStoreBuilder()
                .withDrawing(DrawingBuilder().withTileLayer(TileLayerBuilder()
                                                                .withTile(Vec2Int(0, 1), COLOR_RED)
                                                                .withTile(Vec2Int(1, 1), COLOR_RED)
                                                                .withTile(Vec2Int(0, 2), COLOR_RED)
                                                                .withTile(Vec2Int(11, 1), COLOR_BLUE)
                                                                .withTile(Vec2Int(10, 1), COLOR_BLUE)
                                                                .withTile(Vec2Int(11, 2), COLOR_BLUE)))
                .build();

        TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();

        int tileWidth = layer.getTileBounds().getWidth();
        int tileHeight = layer.getTileBounds().getHeight();

        Drawing &drawing = documentStore.getActiveDocument().getActiveDrawing();
        flip_horizontal(drawing.getActiveFrame().getActiveLayer());

        REQUIRE(layer.getAtTilePos(tileWidth - 1, 1)->getColor() == COLOR_RED);
        REQUIRE(layer.getTileIndex(tileWidth - 1, 1) == 23);
        REQUIRE(layer.getAtTilePos(tileWidth - 2, 1)->getColor() == COLOR_RED);
        REQUIRE(layer.getTileIndex(tileWidth - 2, 1) == 22);
        REQUIRE(layer.getAtTilePos(tileWidth - 1, 2)->getColor() == COLOR_RED);
        REQUIRE(layer.getTileIndex(tileWidth - 1, 2) == 35);
        REQUIRE(layer.getAtTilePos(0, 1)->getColor() == COLOR_BLUE);
        REQUIRE(layer.getTileIndex(0, 1) == 12);
        REQUIRE(layer.getAtTilePos(1, 1)->getColor() == COLOR_BLUE);
        REQUIRE(layer.getTileIndex(1, 1) == 13);
        REQUIRE(layer.getAtTilePos(0, 2)->getColor() == COLOR_BLUE);
        REQUIRE(layer.getTileIndex(0, 2) == 24);
    }

    SECTION("can flip multiple layers")
    {
        DocumentStore documentStore =
            DocumentStoreBuilder()
                .withDrawing(DrawingBuilder()
                                 .withTileLayer(TileLayerBuilder().withTile(Vec2Int(0, 1), COLOR_RED))
                                 .withTileLayer(TileLayerBuilder().withTile(Vec2Int(0, 1), COLOR_BLUE))
                                 .withTileLayer(TileLayerBuilder().withTile(Vec2Int(1, 1), COLOR_YELLOW)))
                .build();

        TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();

        int tileWidth = layer.getTileBounds().getWidth();
        int tileHeight = layer.getTileBounds().getHeight();

        Drawing &drawing = documentStore.getActiveDocument().getActiveDrawing();
        Frame &frame = drawing.getActiveFrame();

        flip_horizontal(drawing.getActiveFrame().getLayers());

        REQUIRE(frame.getLayer(0).getAtTilePos(tileWidth - 1, 1)->getColor() == COLOR_RED);
        REQUIRE(frame.getLayer(0).getAtTilePos(0, 1) == nullptr);
        REQUIRE(frame.getLayer(1).getAtTilePos(tileWidth - 1, 1)->getColor() == COLOR_BLUE);
        REQUIRE(frame.getLayer(1).getAtTilePos(0, 1) == nullptr);
        REQUIRE(frame.getLayer(2).getAtTilePos(tileWidth - 2, 1)->getColor() == COLOR_YELLOW);
        REQUIRE(frame.getLayer(2).getAtTilePos(1, 1) == nullptr);
    }
}
