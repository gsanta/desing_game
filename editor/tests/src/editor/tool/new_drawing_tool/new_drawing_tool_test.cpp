#include <catch2/catch_test_macros.hpp>
#include "../../test_helpers/test_document_factory.h"
#include "../src/app/tool/new_drawing_tool/new_drawing_tool.h"

using namespace ::spright::editor;

TEST_CASE("NewDrawingTool", "[new-drawing-tool]") {
	SECTION("can create a new drawing with selection") {
		Container windowContainer(Bounds(0, 0, 500, 500));

		DocumentStore documentStore = DocumentStoreBuilder().build();
		DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(windowContainer);

		NewDrawingTool newDrawingTool(&documentStore, &documentFactory);

		PointerInfo pointerInfo;
		//pointerInfo.curr = eraseLayer.getWorldPos(Vec2Int(1, 1));

		//eraseTool.pointerDown(pointerInfo);
	}
}