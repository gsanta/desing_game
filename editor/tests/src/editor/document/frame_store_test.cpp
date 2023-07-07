// #include <catch2/catch_test_macros.hpp>
// #include <catch2/matchers/catch_matchers.hpp>
// #include "../src/app/document/frame.h"
// #include "../test_helpers/test_document_factory.h"

// using namespace ::spright::editor;

// TEST_CASE("FrameStore", "[frame_handler]") {
// 	SECTION("throws when trying to remove the last frame") {
// 		std::vector<TileLayer> layers = TestDocumentFactory::createTileLayers(1);

// 		FrameImpl frame(0);
// 		frame.addLayer(layers[0]);

// 		FrameStore frameStore;
// 		frameStore.addFrame(frame);

// 		REQUIRE_THROWS_WITH(frameStore.removeFrame(0), "The last frame can not be removed");
// 	}

// 	SECTION("can remove a frame") {
// 		std::vector<TileLayer> layers = TestDocumentFactory::createTileLayers(3);

// 		FrameImpl frame(0);
// 		frame.addLayer(layers[0]);
// 		FrameImpl frame2(1);
// 		frame2.addLayer(layers[1]);
// 		FrameImpl frame3(1);
// 		frame3.addLayer(layers[2]);

// 		FrameStore frameStore;
// 		frameStore.addFrame(frame);
// 		frameStore.addFrame(frame2);
// 		frameStore.addFrame(frame3);

// 		frameStore.setActiveFrame(1);
// 		frameStore.removeFrame(1);

// 		REQUIRE(frameStore.getFrame(1) == frame3);

// 		// no better way to check that the active frame is frame3
// 		REQUIRE(frameStore.getActiveFrame().getLayer(0).getName() == frame3.getLayer(0).getName());

// 		frameStore.removeFrame(1);
// 		REQUIRE(frameStore.getActiveFrame().getLayer(0).getName() == frame.getLayer(0).getName());
// 	}
// }
