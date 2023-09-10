#include "../../../test_helpers/matchers/equals_bounds_matcher.h"
#include "../../../test_helpers/pointer_info_builder.h"
#include "../../../test_helpers/test_document_factory.h"
#include "../src/app/tool/common/rectangle_cursor/rectangle_cursor.h"
#include "../src/engine/graphics/impl/headless/headless_renderer2d.h"
#include "../src/maths/vec2.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace spright::editor;
using namespace spright::maths;

TEST_CASE("Rectangle stroke draw", "[rectangle-stroke]")
{
    SECTION("creates the rectangular stroke, rectangle size is even, rectangle position is at the origin")
    {
        int rectangleSize = 4;
        float tileSize = 1.0f;

        TileLayer tempLayer =
            TestDocumentFactory::createTileLayer(0, tileSize, Bounds::createWithPositions(-5.0f, -5.0f, 5.0f, 5.0f));
        PointerInfo pointer = PointerInfoBuilder().withCurr(Vec2(0, 0)).build();

        RectangleCursor rectangleCursor(rectangleSize);

        rectangleCursor.update(tempLayer, pointer);

        std::vector<Rect2D *> &rects = tempLayer.getTiles();

        REQUIRE_THAT(rects[0]->getBounds(), EqualsBounds(Bounds(-2.0f, -2.0f, 2.0f, 2.0f)));
    }

    SECTION("creates the rectangular stroke, rectangle size is odd, rectangle position is at the origin")
    {
        int rectangleSize = 3;
        float tileSize = 1.0f;

        TileLayer drawLayer =
            TestDocumentFactory::createTileLayer(0, tileSize, Bounds::createWithPositions(-5.0f, -5.0f, 5.0f, 5.0f));
        PointerInfo pointer = PointerInfoBuilder().withCurr(Vec2(0, 0)).build();

        RectangleCursor rectangleCursor(rectangleSize);

        rectangleCursor.update(drawLayer, pointer);

        std::vector<Rect2D *> &rects = drawLayer.getTiles();

        REQUIRE_THAT(rects[0]->getBounds(), EqualsBounds(Bounds(-1.0f, -1.0f, 2.0f, 2.0f)));
    }

    SECTION("creates the rectangular stroke when the rectangle is not at the origin")
    {
        int rectangleSize = 4;
        float tileSize = 1.0f;

        Container container(Bounds::createWithPositions(-5.0f, -5.0f, 5.0f, 5.0f));

        TileLayer drawLayer =
            TestDocumentFactory::createTileLayer(0, tileSize, Bounds::createWithPositions(-5.0f, -5.0f, 5.0f, 5.0f));
        PointerInfo pointer = PointerInfoBuilder().withCurr(Vec2(2.0f, 3.0f)).build();

        RectangleCursor rectangleCursor(rectangleSize);

        rectangleCursor.update(drawLayer, pointer);

        std::vector<Rect2D *> &rects = drawLayer.getTiles();

        REQUIRE_THAT(rects[0]->getBounds(), EqualsBounds(Bounds(0, 1.0f, 4.0f, 5.0f)));
    }
}
