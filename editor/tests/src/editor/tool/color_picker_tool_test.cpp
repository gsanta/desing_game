#include <catch2/catch_test_macros.hpp>
#include "../src/app/tool/color_picker_tool.h"
#include "../src/engine/graphics/impl/headless/headless_renderer2d.h"
#include "../src/app/tool/brush_tool.h"
#include "../src/app/tool/common/document_info.h"
#include "../src/app/tool/pointer_info.h"
#include "./layer_provider_test_impl.h"
#include "../test_helpers/test_event_emitter.h"
#include "../test_helpers/test_document_factory.h"
#include "../test_helpers/document_store_builder.h"

using namespace ::spright::editor;

TEST_CASE("ColorPickerTool pointerDown", "[color-picker-tool]") {
	SECTION("picks the color at the given pointer position") {
		TestEventEmitter eventEmitter;

		ToolHandler toolHandler;

		DocumentStore documentStore = DocumentStoreBuilder().withDrawing().build();
		Drawing& activeDrawing = documentStore.getActiveDocument().getActiveDrawing();
		TileLayer& tileLayer = activeDrawing.getActiveLayer();

		// TODO: destroy layerprovider
		ColorPickerTool colorPickerTool(&toolHandler, &eventEmitter);

		Brush brush;
		brush.paint(tileLayer, Vec2Int(0, 0), 0xFFFF0000);
		brush.paint(tileLayer, Vec2Int(1, 1), 0xFF00FF00);

		PointerInfo pointerInfo;
		DocumentInfo documentInfo;
		documentInfo.activeDrawing = &activeDrawing;
		pointerInfo.curr = tileLayer.getWorldPos(Vec2Int(0, 0));
		colorPickerTool.pointerDown(pointerInfo, documentInfo);

		REQUIRE(colorPickerTool.getPickedColor() == 0xFFFF0000);

		pointerInfo.curr = tileLayer.getWorldPos(Vec2Int(1, 1));
		colorPickerTool.pointerDown(pointerInfo, documentInfo);

		REQUIRE(colorPickerTool.getPickedColor() == 0xFF00FF00);
	}

	SECTION("emits event if picked color changes") {
		DocumentStore documentStore = DocumentStoreBuilder().withDrawing().build();

		TestEventEmitter eventEmitter;

		ToolHandler toolHandler;


		ColorPickerTool colorPickerTool(&toolHandler, &eventEmitter);

		Brush brush;

		Drawing& activeDrawing = documentStore.getActiveDocument().getActiveDrawing();
		TileLayer& tileLayer = activeDrawing.getActiveLayer();

		brush.paint(tileLayer, Vec2Int(0, 0), 0xFFFF0000);

		PointerInfo pointerInfo;
		pointerInfo.curr = tileLayer.getWorldPos(Vec2Int(1, 1));
		DocumentInfo documentInfo;
		documentInfo.activeDrawing = &activeDrawing;

		colorPickerTool.pointerDown(pointerInfo, documentInfo);
		// no tile at that position
		REQUIRE(eventEmitter.getEmitCount() == 0);

		pointerInfo.curr = tileLayer.getWorldPos(Vec2Int(0, 0));
		colorPickerTool.pointerDown(pointerInfo, documentInfo);

		REQUIRE(eventEmitter.getLastEventType() == "tool_data_changed");
		REQUIRE(eventEmitter.getLastData()["tool"] == "color_picker");
		REQUIRE(eventEmitter.getEmitCount() == 1);

		colorPickerTool.pointerDown(pointerInfo, documentInfo);
		// picking the already picked color
		REQUIRE(eventEmitter.getEmitCount() == 1);
	}
}
