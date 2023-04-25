#include "../../test_helpers/document_store_builder.h"
#include "../../test_helpers/tool_context_builder.h"
#include "../src/app/document/document_store.h"
#include "../src/app/tool/select_tool/select_tool.h"
#include "../src/engine/graphics/layer/tileLayer.h"
#include "../../test_helpers/pointer_info_builder.h"
#include "../../test_helpers/document_info_builder.h"

#include <catch2/catch_test_macros.hpp>


TEST_CASE("SelectTool", "[select-tool]")
{
    using namespace ::spright::engine;
    using namespace ::spright::editor;

    SECTION("sets the selection to the active drawing")
    {
        DocumentStore documentStore = DocumentStoreBuilder().build();

        ToolContext toolContext =
            ToolContextBuilder()
                .withPointerInfo(PointerInfoBuilder().withCurr(canvas.getForegroundLayer().getWorldPos(Vec2Int(1, 1))))
                .withDocumentInfo(DocumentInfoBuilder().withActiveDrawing(&activeDrawing))
                .build();


        SelectTool selectTool;
    }
}
