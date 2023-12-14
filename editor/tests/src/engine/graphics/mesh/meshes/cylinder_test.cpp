#include "../../../../test_helpers/matchers/equals_vec3_approx_matcher.h"
#include "../src/engine/graphics/colors.h"
#include "../src/engine/graphics/mesh/meshes/cylinder.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace spright::engine;

TEST_CASE("Cylinder", "[cylinder]")
{
    SECTION("a cylinder can be constructed")
    {
        Cylinder cylinder(Vec3(0, 0, 0), 10, 4, 8, 3);

        REQUIRE_THAT(cylinder.getPositions()[0], EqualsVec3Approx(Vec3(4, -5, 0)));
        REQUIRE_THAT(cylinder.getPositions()[1], EqualsVec3Approx(Vec3(2, 5, 0)));
        REQUIRE_THAT(cylinder.getPositions()[2], EqualsVec3Approx(Vec3(-1, 5, -1.73)));
        REQUIRE_THAT(cylinder.getPositions()[3], EqualsVec3Approx(Vec3(4, -5, 0)));
        REQUIRE_THAT(cylinder.getPositions()[4], EqualsVec3Approx(Vec3(-1, 5, -1.73)));
        REQUIRE_THAT(cylinder.getPositions()[5], EqualsVec3Approx(Vec3(-2, -5, -3.46)));

        REQUIRE_THAT(cylinder.getPositions()[6], EqualsVec3Approx(Vec3(-2, -5, -3.46)));
        REQUIRE_THAT(cylinder.getPositions()[7], EqualsVec3Approx(Vec3(-1, 5, -1.73)));
        REQUIRE_THAT(cylinder.getPositions()[8], EqualsVec3Approx(Vec3(-1, 5, 1.73)));
        REQUIRE_THAT(cylinder.getPositions()[9], EqualsVec3Approx(Vec3(-2, -5, -3.46)));
        REQUIRE_THAT(cylinder.getPositions()[10], EqualsVec3Approx(Vec3(-1, 5, 1.73)));
        REQUIRE_THAT(cylinder.getPositions()[11], EqualsVec3Approx(Vec3(-2, -5, 3.46)));

        REQUIRE_THAT(cylinder.getPositions()[12], EqualsVec3Approx(Vec3(-2, -5, 3.46)));
        REQUIRE_THAT(cylinder.getPositions()[13], EqualsVec3Approx(Vec3(-1, 5, 1.73)));
        REQUIRE_THAT(cylinder.getPositions()[14], EqualsVec3Approx(Vec3(2, 5, 0)));
        REQUIRE_THAT(cylinder.getPositions()[15], EqualsVec3Approx(Vec3(-2, -5, 3.46)));
        REQUIRE_THAT(cylinder.getPositions()[16], EqualsVec3Approx(Vec3(2, 5, 0)));
        REQUIRE_THAT(cylinder.getPositions()[17], EqualsVec3Approx(Vec3(4, -5, 0)));
    }
}
