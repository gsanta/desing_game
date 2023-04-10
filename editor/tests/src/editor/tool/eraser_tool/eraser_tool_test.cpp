#include <catch2/catch_test_macros.hpp>
#include "../src/app/tool/eraser_tool/eraser_tool.h"
#include "../src/app/document/factory/document_factory.h"
#include "../src/app/document/document_store.h"
#include "../src/engine/graphics/renderable/rect2d.h"
#include "../src/engine/graphics/layer/group.h"
#include "../src/engine/graphics/impl/headless/headless_shader.h"
#include "../src/engine/graphics/impl/headless/headless_renderer2d.h"
#include "../src/engine/system/window/impl/headless/headless_window.h"
#include "../src/app/tool/brush_tool.h"
#include "../src/app/tool/pointer_info.h"
#include "../src/app/tool/common/document_info.h"
#include "../layer_provider_test_impl.h"
#include "../../test_helpers/test_document_factory.h"
#include "../../test_helpers/document_store_builder.h"

using namespace ::spright::engine;
using namespace ::spright::editor;

TEST_CASE("EraseTool pointerDown", "[erase-tool]") {
	SECTION("removes the tiles at the given pointer position") {
		DocumentStore documentStore = DocumentStoreBuilder().withDrawing().build();
		TileLayer& eraseLayer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();
		TileLayer& drawLayer = documentStore.getActiveDocument().getActiveDrawing().getForegroundLayer();

		Brush brush;
		brush.paint(eraseLayer, Vec2Int(0, 0), 0xFFFFFFFF);
		brush.paint(eraseLayer, Vec2Int(1, 0), 0xFFFFFFFF);
		brush.paint(eraseLayer, Vec2Int(2, 0), 0xFFFFFFFF);
		brush.paint(eraseLayer, Vec2Int(0, 1), 0xFFFFFFFF);
		brush.paint(eraseLayer, Vec2Int(1, 1), 0xFFFFFFFF);
		brush.paint(eraseLayer, Vec2Int(2, 1), 0xFFFFFFFF);
		brush.paint(eraseLayer, Vec2Int(0, 2), 0xFFFFFFFF);
		brush.paint(eraseLayer, Vec2Int(1, 2), 0xFFFFFFFF);
		brush.paint(eraseLayer, Vec2Int(2, 2), 0xFFFFFFFF);

		Rect2D* renderable = eraseLayer.getAtTileIndex(0);

		EraserTool eraseTool(&documentStore, 1);

		PointerInfo pointerInfo;
		pointerInfo.curr = eraseLayer.getWorldPos(Vec2Int(1, 1));
		DocumentInfo documentInfo;
		documentInfo.activeDrawing = &documentStore.getActiveDocument().getActiveDrawing();

		eraseTool.pointerDown(pointerInfo, documentInfo);

		REQUIRE(eraseLayer.getAtTilePos(0, 0) != nullptr);
		REQUIRE(eraseLayer.getAtTilePos(1, 0) != nullptr);
		REQUIRE(eraseLayer.getAtTilePos(2, 0) != nullptr);
		REQUIRE(eraseLayer.getAtTilePos(0, 1) != nullptr);
		REQUIRE(eraseLayer.getAtTilePos(1, 1) == nullptr);
		REQUIRE(eraseLayer.getAtTilePos(2, 1) != nullptr);
		REQUIRE(eraseLayer.getAtTilePos(0, 2) != nullptr);
		REQUIRE(eraseLayer.getAtTilePos(1, 2) != nullptr);
		REQUIRE(eraseLayer.getAtTilePos(2, 2) != nullptr);
	}

	SECTION("removes the tiles at the given pointer position") {
		DocumentStore documentStore = DocumentStoreBuilder()
			.withDrawing(
				DrawingBuilder().withBounds(Bounds::createWithPositions(0, 0, 2, 2))
			)
			.withDrawing(
				DrawingBuilder().withBounds(Bounds::createWithPositions(3, 3, 5, 5))
			)
			.build();

		TileLayer& foregroundLayer1 = documentStore.getActiveDocument().getDrawings()[0].getForegroundLayer();
		TileLayer& foregroundLayer2 = documentStore.getActiveDocument().getDrawings()[1].getForegroundLayer();

		EraserTool eraseTool(&documentStore, 1);

		PointerInfo pointerInfo;
		DocumentInfo documentInfo;
		documentInfo.activeDrawing = &documentStore.getActiveDocument().getDrawings()[0];

		eraseTool.pointerMove(pointerInfo, documentInfo);

		REQUIRE(foregroundLayer1.getRenderables().size() > 0);

		documentInfo.prevDrawing = documentInfo.activeDrawing;
		documentInfo.activeDrawing = &documentStore.getActiveDocument().getDrawings()[1];
		documentInfo.isLeavingDrawing = true;
		eraseTool.pointerMove(pointerInfo, documentInfo);

		REQUIRE(foregroundLayer1.getRenderables().size() == 0);

		// PointerInfo pointerInfo;
		// pointerInfo.curr = activeLayer1.getWorldPos(Vec2Int(1, 1));
		// DocumentInfo documentInfo;
		// documentInfo.activeDrawing = &documentStore.getActiveDocument().getActiveDrawing();


	}
}
