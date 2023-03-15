#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include "../src/app/document/frame_impl.h"
#include "../src/app/document/frame_store.h"
#include "../test_helpers/test_document_factory.h"

using namespace ::spright::editor;

TEST_CASE("FrameStore", "[frame_handler]") {
	SECTION("can return frame by index") {

		FrameImpl frame1(0);
		FrameImpl frame2(0);

		FrameStore frameHandler;

		frameHandler.addFrame(frame1);
		frameHandler.addFrame(frame2);
	
		REQUIRE(frameHandler.getFrame(0).getIndex() == 0);
		REQUIRE(frameHandler.getFrame(1).getIndex() == 1);
		REQUIRE_THROWS_WITH(frameHandler.getFrame(2), "Frame with index 2 not found");
	}

	SECTION("can get/set the active frame") {
		std::vector<TileLayer> layers = TestDocumentFactory::createTileLayers(2);

		FrameImpl frame1(0);
		frame1.addLayer(layers[0]);
		FrameImpl frame2(1);
		frame2.addLayer(layers[1]);

		FrameStore frameHandler;

		frameHandler.addFrame(frame1);
		frameHandler.addFrame(frame2);


		REQUIRE(frameHandler.getActiveFrame().getIndex() == frame1.getIndex());

		frameHandler.setActiveFrame(1);

		REQUIRE(frameHandler.getActiveFrame().getIndex() == frame2.getIndex());
	}

	SECTION("throws when trying to remove the last frame") {
		std::vector<TileLayer> layers = TestDocumentFactory::createTileLayers(1);

		FrameImpl frame(0);
		frame.addLayer(layers[0]);

		FrameStore frameHandler;
		frameHandler.addFrame(frame);

		REQUIRE_THROWS_WITH(frameHandler.removeFrame(0), "The last frame can not be removed");
	}

	SECTION("can remove a frame") {
		std::vector<TileLayer> layers = TestDocumentFactory::createTileLayers(3);

		FrameImpl frame(0);
		frame.addLayer(layers[0]);
		FrameImpl frame2(1);
		frame2.addLayer(layers[1]);
		FrameImpl frame3(1);
		frame3.addLayer(layers[2]);

		FrameStore frameHandler;
		frameHandler.addFrame(frame);
		frameHandler.addFrame(frame2);
		frameHandler.addFrame(frame3);

		frameHandler.removeFrame(1);
	}
}