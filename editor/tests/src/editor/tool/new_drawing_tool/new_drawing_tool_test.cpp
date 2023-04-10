#include <catch2/catch_test_macros.hpp>
#include "../../test_helpers/test_document_factory.h"
#include "../../test_helpers/document_store_builder.h"
#include "../src/app/tool/new_drawing_tool/new_drawing_tool.h"

using namespace ::spright::editor;

TEST_CASE("NewDrawingTool", "[new-drawing-tool]") {
	SECTION("can create a new drawing with selection") {
		Container windowContainer(Bounds(0, 0, 500, 500));

		DocumentStore documentStore = DocumentStoreBuilder().build();
		DocumentFactory documentFactory = TestDocumentFactory::createDocumentFactory(windowContainer);

		NewDrawingTool newDrawingTool(&documentStore, &documentFactory);

		Drawing& canvas = documentStore.getActiveDocument().getCanvas();
		Drawing& activeDrawing = documentStore.getActiveDocument().getDrawings()[0];

		PointerInfo pointerInfo;
		pointerInfo.curr = canvas.getForegroundLayer().getWorldPos(Vec2Int(1, 1));
		DocumentInfo documentInfo;
		documentInfo.activeDrawing = &activeDrawing;

		newDrawingTool.pointerDown(pointerInfo, documentInfo);

		pointerInfo.prev = pointerInfo.curr;
		pointerInfo.curr = canvas.getForegroundLayer().getWorldPos(Vec2Int(3, 3));
		newDrawingTool.pointerMove(pointerInfo, documentInfo);
		newDrawingTool.pointerUp(pointerInfo, documentInfo);

		REQUIRE(documentStore.getActiveDocument().getDrawings().size() == 1);
	}
}
