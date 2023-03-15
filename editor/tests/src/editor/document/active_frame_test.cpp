#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_contains.hpp>
#include "../src/app/document/active_frame.h"
#include "../src/app/document/frame_impl.h"
#include "../test_helpers/test_document_factory.h"

using namespace ::spright::engine;
using namespace ::spright::editor;

TEST_CASE("ActiveFrame", "[active_frame]") {
	SECTION("can get a layer by it's id") {
		std::vector<TileLayer> layers = TestDocumentFactory::createTileLayers(3);

		std::vector<FrameImpl> frames{ FrameImpl() };
		frames[0].addLayer(layers[2]);

		ActiveFrame activeFrame(frames, 0);

		activeFrame.addBackgroundLayer(layers[0]);
		activeFrame.addForegroundLayer(layers[1]);

		REQUIRE(activeFrame.getLayer("id0").getId() == "id0");
		REQUIRE(activeFrame.getLayer("id1").getId() == "id1");
		REQUIRE(activeFrame.getLayer("id2").getId() == "id2");
	}

	SECTION("throws if layer with id is not found") {
		std::vector<TileLayer> layers = TestDocumentFactory::createTileLayers(2);

		std::vector<FrameImpl> frames{ FrameImpl() };

		frames[0].addLayer(layers[1]);
		ActiveFrame activeFrame(frames, 0);

		activeFrame.addBackgroundLayer(layers[0]);

		REQUIRE_THROWS_WITH(activeFrame.getLayer("id2"), "Layer with id id2 not found");
	}

	SECTION("can set the active layer") {
		std::vector<TileLayer> layers = TestDocumentFactory::createTileLayers(3);

		std::vector<FrameImpl> frames{ FrameImpl() };

		frames[0].addLayer(layers[0]);
		frames[0].addLayer(layers[1]);
		frames[0].addLayer(layers[2]);

		ActiveFrame activeFrame(frames, 0);

		activeFrame.setActiveLayer(layers[1]);

		REQUIRE(activeFrame.getActiveLayer().getId() == layers[1].getId());
	}
}