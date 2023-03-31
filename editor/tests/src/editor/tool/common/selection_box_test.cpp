#include <catch2/catch_test_macros.hpp>
#include "../../test_helpers/test_document_factory.h"
#include "../src/engine/graphics/layer/tileLayer.h"
#include "../src/app/tool/common/selection_box.h"
#include "../src/app/tool/color_picker_tool.h"

using namespace ::spright::editor;
using namespace ::spright::engine;

TEST_CASE("SelectionBox", "[selection-box]") {
	SECTION("can copy assign") {
		TileLayer tileLayer = TestDocumentFactory::createTileLayers(0)[0];

		spright::SelectionBox selectionBox(tileLayer);
	}
}
