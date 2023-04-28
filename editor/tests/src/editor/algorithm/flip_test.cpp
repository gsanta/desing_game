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

    SECTION("can flip a selected region")
    {
        DocumentStore documentStore =
            DocumentStoreBuilder()
                .withDrawing(DrawingBuilder().withTileSize(1).withTileLayer(TileLayerBuilder()
                                                                                .withTile(Vec2Int(0, 0))
                                                                                .withTile(Vec2Int(0, 1))
                                                                                .withTile(Vec2Int(1, 0))
                                                                                .withTile(Vec2Int(1, 1))))
                .build();

        Drawing &drawing = documentStore.getActiveDocument().getActiveDrawing();
        TileLayer &activeLayer = drawing.getActiveLayer();

        const Vec2 bottomLeft = activeLayer.getWorldPos(1, 0);
        const Vec2 topRight = activeLayer.getWorldPos(3, 2);
        const Bounds bounds(bottomLeft, topRight);

        drawing.getState().setBounds(bounds);

        Frame &frame = drawing.getActiveFrame();

        flip_horizontal(frame.getLayers(), bounds);

        REQUIRE(frame.getLayer(0).getAtTilePos(4, 0) != nullptr);
        REQUIRE(frame.getLayer(0).getAtTilePos(4, 1) != nullptr);
        REQUIRE(frame.getLayer(0).getAtTilePos(1, 0) == nullptr);
        REQUIRE(frame.getLayer(0).getAtTilePos(1, 1) == nullptr);
        REQUIRE(frame.getLayer(0).getAtTilePos(0, 0) != nullptr);
        REQUIRE(frame.getLayer(0).getAtTilePos(0, 1) != nullptr);
    }

    SECTION("removes tiles that would be out of bounds after the flip")
    {
        DocumentStore documentStore = DocumentStoreBuilder()
                                          .withDrawing(DrawingBuilder()
                                                           .withBounds(Bounds(0, 0, 7.0f, 7.0f))
                                                           .withTileSize(1)
                                                           .withTileLayer(TileLayerBuilder()
                                                                              .withTile(Vec2Int(0, 0))
                                                                              .withTile(Vec2Int(0, 1))
                                                                              .withTile(Vec2Int(1, 0))
                                                                              .withTile(Vec2Int(1, 1))))
                                          .build();

        Drawing &drawing = documentStore.getActiveDocument().getActiveDrawing();
        TileLayer &activeLayer = drawing.getActiveLayer();

        const Vec2 bottomLeft = activeLayer.getWorldPos(0, 0);
        const Vec2 topRight = activeLayer.getWorldPos(4, 2);
        const Bounds bounds(bottomLeft, topRight);

        drawing.getState().setBounds(bounds);

        Frame &frame = drawing.getActiveFrame();

        flip_horizontal(frame.getLayers(), bounds);

        REQUIRE(activeLayer.getRenderables().size() == 2);
        REQUIRE(frame.getLayer(0).getAtTilePos(6, 0) != nullptr);
        REQUIRE(frame.getLayer(0).getAtTilePos(6, 1) != nullptr);
    }
}
