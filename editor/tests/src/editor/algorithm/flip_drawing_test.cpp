#include "../src/app/algorithm/flip_drawing.h"
#include "../src/engine/graphics/layer/tileLayer.h"
#include "../test_helpers/document_store_builder.h"
#include "../test_helpers/drawing_builder.h"
#include "../test_helpers/tile_layer_builder.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editor;
using namespace spright::engine;

TEST_CASE("flipDrawing", "[flip-drawing]")
{
    SECTION("can flip a drawing")
    {
        DocumentStore documentStore =
            DocumentStoreBuilder()
                .withDrawing(DrawingBuilder().withTileLayer(
                    TileLayerBuilder().withTile(Vec2Int(0, 1)).withTile(Vec2Int(1, 1)).withTile(Vec2Int(0, 2))))
                .build();

        TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();

        int tileWidth = layer.getTileBounds().getWidth();
        int tileHeight = layer.getTileBounds().getHeight();

        flip_drawing(documentStore.getActiveDocument().getActiveDrawing());

        REQUIRE(layer.getAtTilePos(tileWidth - 1, 1) != nullptr);
        REQUIRE(layer.getAtTilePos(tileWidth - 2, 1) != nullptr);
        REQUIRE(layer.getAtTilePos(tileWidth - 1, 2) != nullptr);
        REQUIRE(layer.getAtTilePos(0, 1) == nullptr);
        REQUIRE(layer.getAtTilePos(1, 1) == nullptr);
        REQUIRE(layer.getAtTilePos(0, 2) == nullptr);
    }
}
