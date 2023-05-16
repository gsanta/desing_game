
#include "../src/app/core/colors.h"
#include "../src/app/tool/paint_bucket/paint_bucket_tool.h"
#include "src/editor/test_helpers/document_store_builder.h"
#include "src/editor/test_helpers/tool_context_builder.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::engine;

TEST_CASE("PaintBucketTool", "[paint-bucket-tool]")
{
    SECTION("can fill a continuous area")
    {
        DocumentStore documentStore = DocumentStoreBuilder().withDocumentBounds(Bounds(0, 0, 1, 1)).build();
        ToolContext toolContext = ToolContextBuilder().withActiveDrawing(documentStore).build();

        PaintBucketTool paintBucketTool;

        paintBucketTool.execPointerUp(toolContext);

        TileLayer &layer = documentStore.getActiveDocument().getActiveLayer();

        REQUIRE(layer.getRenderables().size() == 4);
        REQUIRE(layer.getRenderables()[0]->getColor() == COLOR_SPRIGHT_ORANGE);
        REQUIRE(layer.getRenderables()[1]->getColor() == COLOR_SPRIGHT_ORANGE);
        REQUIRE(layer.getRenderables()[2]->getColor() == COLOR_SPRIGHT_ORANGE);
        REQUIRE(layer.getRenderables()[3]->getColor() == COLOR_SPRIGHT_ORANGE);
    }
}