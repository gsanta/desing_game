#include "../../../test_helpers/builders/drawing_builder.h"
#include "../src/engine/scene/canvas/tile_canvas.h"
#include "../src/engine/scene/canvas/canvas_component.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::engine;

class MockCanvasComponent1 : public CanvasComponent {
public:
    MockCanvasComponent1(int data): data(data) {}
    void onAddedToCanvas(Canvas &canvas) override {};

    MockCanvasComponent1* clone() override {
        return new MockCanvasComponent1(data);
    };

    int data;
};

class MockCanvasComponent2 : public CanvasComponent {
public:
    MockCanvasComponent2(int data): data(data) {}
    void onAddedToCanvas(Canvas &canvas) override {};

    MockCanvasComponent2 *clone() override
    {
        return new MockCanvasComponent2(data);
    }

    int data;
};

SCENARIO("Canvas") {
    GIVEN("an empty canvas") {
        TileCanvas canvas = DrawingBuilder().build();

        WHEN("adding a component") {
            canvas.addComponent<MockCanvasComponent1>(1);

            THEN("it can be queried by it's type") {
                std::shared_ptr<MockCanvasComponent1> component1 = canvas.getComponent<MockCanvasComponent1>();
                std::shared_ptr<MockCanvasComponent2> component2 = canvas.getComponent<MockCanvasComponent2>();

                REQUIRE(component1->data == 1);
                REQUIRE(component2 == nullptr);
            }

            WHEN("adding another component") {
                canvas.addComponent<MockCanvasComponent2>(2);

                THEN("it can also be queried by it's type") {
                    std::shared_ptr<MockCanvasComponent1> component1 = canvas.getComponent<MockCanvasComponent1>();
                    std::shared_ptr<MockCanvasComponent2> component2 = canvas.getComponent<MockCanvasComponent2>();

                    REQUIRE(component1->data == 1);
                    REQUIRE(component2->data == 2);
                }

                WHEN("removing a component") {
                    canvas.removeComponent<MockCanvasComponent1>();

                    THEN("it can not be obtained anymore by type") {
                        std::shared_ptr<MockCanvasComponent1> component1 = canvas.getComponent<MockCanvasComponent1>();
                        std::shared_ptr<MockCanvasComponent2> component2 = canvas.getComponent<MockCanvasComponent2>();

                        REQUIRE(component1 == nullptr);
                        REQUIRE(component2 != nullptr);
                    }
                }
            }
        }
    }
}
