#include "../src/app/algorithm/raster_operations.h"
#include "../test_helpers/tile_layer_builder.h"
#include <catch2/catch_test_macros.hpp>

using namespace spright::editor;
using namespace spright::engine;

SCENARIO("Raster operations")
{
    GIVEN("a tile layer") {
        // TileLayer sourceTileLayer = TileLayerBuilder().withBounds(BoundsInt(2, 2, 5, 5)).withTileFill().build();
        // TileLayer destTileLayer = TileLayerBuilder().withBounds(BoundsInt(2, 2, 5, 5)).withTileFill().build();

        // WHEN("copying an area of raster to another tile layer") {
        //     raster_operation_copy_area(sourceTileLayer, destTileLayer, Vec2Int(1, 1), Vec2Int(1, 1), Vec2Int(2, 2));

        //     THEN("the destination layer contains the raster area")
        //     {
        //         REQUIRE(destTileLayer.getRenderables().size() == 4);
        //     }
        // }
    }
}
