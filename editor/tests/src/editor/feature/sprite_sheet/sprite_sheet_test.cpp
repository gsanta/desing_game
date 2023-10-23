
#include "../../test_helpers/builders/document_builder.h"
#include "../../test_helpers/builders/drawing_builder.h"
#include "../../test_helpers/builders/frame_builder.h"
#include "../../test_helpers/builders/tool_context_builder.h"
#include "../../test_helpers/common_tool_funcs.h"
#include "../../test_helpers/matchers/equals_bounds_matcher.h"
#include "../../test_helpers/test_document_factory.h"
#include "../src/app/feature/sprite_sheet/sprite_sheet.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editor;

SCENARIO("Sprite sheet")
{

    GIVEN("a drawing with a single frame and layer")
    {
        Document document = DocumentBuilder().withDrawing(DrawingBuilder().withBounds(Bounds(0, 0, 12, 12))).build();
        ToolContext toolContext = ToolContextBuilder().build(document);
        CommonToolFuncs commonToolFuncs(document, toolContext);
        commonToolFuncs.buildRect(BoundsInt(4, 1, 5, 3));

        HeadlessWindow window(4, 4);
        DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(window);

        TileLayer &origLayer = document.getActiveDrawing().getActiveLayer();

        SpriteSheet spriteSheet(std::make_shared<DocumentFactory>(documentFactory), &document);

        WHEN("generating a sprite sheet")
        {
            spriteSheet.generateSpriteSheet(document.getActiveDrawing());

            Drawing &spriteSheetDrawing = document.getDrawing(1);
            TileLayer &spriteSheetLayer = spriteSheetDrawing.getFrames()[0].getLayer(0);

            THEN("it creates a new drawing on the right side of the original with half the size")
            {
                REQUIRE(document.getDrawings().size() == 2);

                REQUIRE_THAT(spriteSheetDrawing.getBounds(), EqualsBounds(Bounds(14, 6, 20, 12)));
            }

            THEN("it copies the layer's tiles")
            {
                REQUIRE(spriteSheetLayer.getTiles().size() == origLayer.getTiles().size());

                for (Rect2D *tile : origLayer.getTiles())
                {
                    Vec2Int origTilePos = origLayer.getTilePos(origLayer.getTileIndex(*tile));

                    REQUIRE(spriteSheetLayer.getAtTilePos(origTilePos.x, origTilePos.y) != nullptr);
                }
            }
        }
    }

    GIVEN("a drawing with multiple frames and layers")
    {
        TileLayerBuilder tileLayerBuilder = TileLayerBuilder().withBounds(Bounds(0, 0, 12, 8));
        Document document = DocumentBuilder()
                                .withDrawing(DrawingBuilder().withFrame(
                                    FrameBuilder().withTileLayer(tileLayerBuilder).withTileLayer(tileLayerBuilder),
                                    2))
                                .build();

        HeadlessWindow window(4, 4);
        DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(window);

        SpriteSheet spriteSheet(std::make_shared<DocumentFactory>(documentFactory), &document);

        WHEN("generating a sprite sheet") {
            spriteSheet.generateSpriteSheet(document.getActiveDrawing());
            Drawing &spriteSheetDrawing = document.getDrawing(1);

            THEN("it creates a new drawing on the right side of the original to fit all frames horizontally") {
                REQUIRE_THAT(spriteSheetDrawing.getBounds(), EqualsBounds(Bounds(14, 4, 26, 8)));
            }
        }
    }
}
