
#include "../src/engine/graphics/camera/camera.cpp"
#include "../src/engine/system/window/impl/headless/headless_window.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::engine;

SCENARIO("Camera")
{
    GIVEN("a window")
    {
        int windowWidth = 10;
        int windowHeight = 8;
        HeadlessWindow window(10, 8);

        Camera camera(&window, -1.0f, 1.0f, 1);

        THEN("it converts from top/left=zero based system to center=zero system with flipped y coordinate")
        {
            REQUIRE(camera.screenToWorldPos(0, 0) == Vec2(-5.0f, 4.0f));
            REQUIRE(camera.screenToWorldPos(10, 8) == Vec2(5.0f, -4.0f));
            REQUIRE(camera.screenToWorldPos(5, 4) == Vec2(0, 0));
        }

        THEN("it can convert from world to screen pos")
        {
            REQUIRE(camera.worldToScreenPos(0, 0) == Vec2Int(5, 4));
            // REQUIRE(camera.screenToWorldPos(10, 8) == Vec2(5.0f, -4.0f));
            // REQUIRE(camera.screenToWorldPos(5, 4) == Vec2(0, 0));
        }

        WHEN("the camera has a zoom factor of 2")
        {
            int zoomFactor = 2;
            Camera cameraWithZoomFactor(&window, -1.0f, 1.0f, zoomFactor);

            THEN("world pos is half of the screen pos")
            {
                REQUIRE(cameraWithZoomFactor.screenToWorldPos(0, 0) == Vec2(-2.5f, 2.0f));
                REQUIRE(cameraWithZoomFactor.screenToWorldPos(10, 8) == Vec2(2.5f, -2.0f));
                REQUIRE(cameraWithZoomFactor.screenToWorldPos(5, 4) == Vec2(0, 0));
            }
        }

        WHEN("the camera is zoomed")
        {
            camera.zoom(2);

            THEN("world pos is half of the screen pos")
            {
                REQUIRE(camera.screenToWorldPos(0, 0) == Vec2(-2.5f, 2.0f));
                REQUIRE(camera.screenToWorldPos(10, 8) == Vec2(2.5f, -2.0f));
                REQUIRE(camera.screenToWorldPos(5, 4) == Vec2(0, 0));
            }

            WHEN("the camera is translated")
            {
                camera.translate2D(Vec2(1.0f, 2.0f));

                THEN("world pos is translated accordingly")
                {
                    REQUIRE(camera.screenToWorldPos(0, 0) == Vec2(-1.5f, 4.0f));
                    REQUIRE(camera.screenToWorldPos(10, 8) == Vec2(3.5f, 0));
                    REQUIRE(camera.screenToWorldPos(5, 4) == Vec2(1, 2));
                }
            }
        }
    }
}

// TEST_CASE("Camera", "[camera]")
// {
//     SECTION("can convert from screen to world pos")
//     {
//         Camera camera(&window);

//         REQUIRE(camera.screenToWorldPos(500.0f, 500.0f) == Vec2(10.0f, -10.0f));
//         REQUIRE(camera.screenToWorldPos(0.0f, 0.0f) == Vec2(-10.0f, 10.0f));
//         REQUIRE(camera.screenToWorldPos(50.0f, 50.0f) == Vec2(-8.0f, 8.0f));
//     }

//     SECTION("can convert from screen to world pos with camera translate")
//     {
//         Camera camera(&window);

//         camera.translate2D(Vec2(5.0f, 0.0f));

//         REQUIRE(camera.screenToWorldPos(500.0f, 500.0f) == Vec2(15.0f, -10.0f));
//         REQUIRE(camera.screenToWorldPos(0.0f, 0.0f) == Vec2(-5.0f, 10.0f));
//         REQUIRE(camera.screenToWorldPos(50.0f, 50.0f) == Vec2(-3.0f, 8.0f));
//     }

//     SECTION("can convert from world to screen pos")
//     {
//         Camera camera(&window);

//         REQUIRE(camera.worldToScreenPos(10.0f, -10.0f) == Vec2Int(500, 0));
//         REQUIRE(camera.worldToScreenPos(-10.0f, -10.0f) == Vec2Int(0, 0));
//         REQUIRE(camera.worldToScreenPos(-8.0f, 8.0f) == Vec2Int(50, 450));
//     }

//     SECTION("can convert from world to screen pos with camera translate")
//     {
//         Camera camera(&window);

//         camera.translate2D(Vec2(5.0f, 0.0f));

//         REQUIRE(camera.worldToScreenPos(15.0f, -10.0f) == Vec2Int(500, 0));
//         REQUIRE(camera.worldToScreenPos(-5.0f, -10.0f) == Vec2Int(0, 0));
//         REQUIRE(camera.worldToScreenPos(-3.0f, 8.0f) == Vec2Int(50, 450));
//     }
// }
