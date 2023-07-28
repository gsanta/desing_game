
#include "../src/app/core/editor/abstract_editor.h"
#include "../src/app/core/history/history.h"
#include "../src/app/core/history/undoable.h"
#include "../../mocks/test_editor.h"
#include "../../test_helpers/document_builder.h"
#include <catch2/catch_test_macros.hpp>

using namespace spright::editor;

SCENARIO("History")
{
    GIVEN("the user calls the undo action") {

        WHEN("the undo list is empty") {

            THEN("nothing happens") {
                Document document = DocumentBuilder().build();
                TestEditor editor(document);
                int undoCount = 0;

                History history;

                history.undo(editor);

                REQUIRE(undoCount == 0);
                REQUIRE(history.undoSize() == 0);
            }
        }
    }
}
