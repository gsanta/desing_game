#include "../../../../test_helpers/builders/drawing_builder.h"
#include "../../../../test_helpers/matchers/equals_bounds_matcher.h"
#include "../src/editing/tool/tools/canvas_selection_tool/canvas_border_component.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

void require_border_bounds(Layer &decorationLayer) {
    REQUIRE(decorationLayer.getRenderables().size() == 4);

    REQUIRE_THAT(decorationLayer.getRenderables()[0]->getBounds(), EqualsBounds(Bounds(5.0, 4.0, 7.0, 4.2)));  // top
    REQUIRE_THAT(decorationLayer.getRenderables()[1]->getBounds(), EqualsBounds(Bounds(7.0, -2.0, 7.2, 4.0))); // right
    REQUIRE_THAT(decorationLayer.getRenderables()[2]->getBounds(),
                 EqualsBounds(Bounds(5.0, -2.2, 7.0, -2.0)));                                                  // bottom
    REQUIRE_THAT(decorationLayer.getRenderables()[3]->getBounds(), EqualsBounds(Bounds(4.8, -2.0, 5.0, 4.0))); // left
}

SCENARIO("Canvas border component")
{
    GIVEN("a canvas")
    {
        TileCanvas canvas = DrawingBuilder().withBounds(Bounds(5.0f, -2.0f, 7.0f, 4.0f)).build();

        WHEN("adding a canvas border component to it")
        {
            canvas.addComponent<CanvasBorderComponent>();

            THEN("the component draws a white border around the canvas")
            {
                Layer &decorationLayer = canvas.getGizmoLayer();

                require_border_bounds(decorationLayer);

                for (Renderable2D *renderable : decorationLayer.getRenderables()) {
                    REQUIRE(renderable->getColor() == COLOR_WHITE);
                }
            }

            WHEN("setting it to selected") {
                canvas.getComponent<CanvasBorderComponent>()->setSelected(true);

                THEN("the component draws a blue border around the canvas")
                {
                    Layer &decorationLayer = canvas.getGizmoLayer();

                    require_border_bounds(decorationLayer);

                    for (Renderable2D *renderable : decorationLayer.getRenderables())
                    {
                        REQUIRE(renderable->getColor() == COLOR_BLUE);
                    }
                }
            }
        }
    }
}
