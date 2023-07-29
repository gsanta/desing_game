
#include "../../mocks/test_editor.h"
#include "../../test_helpers/document_builder.h"
#include "../src/app/core/editor/abstract_editor.h"
#include "../src/app/core/history/history.h"
#include "../src/app/core/history/undoable.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editor;

class TestUndoable : public Undoable
{
public:
    TestUndoable(int &undoCounter, int &redoCounter) : undoCounter(undoCounter), redoCounter(redoCounter)
    {
    }

    void undo(AbstractEditor &editor) const
    {
        undoCounter++;
    }

    virtual void redo(AbstractEditor &editor) const
    {
        redoCounter++;
    }

    int &undoCounter;

    int &redoCounter;
};

SCENARIO("History")
{
    Document document = DocumentBuilder().build();
    TestEditor editor(document);

    int undoCount = 0;

    int redoCount = 0;

    History history;

    GIVEN("the user calls the undo action")
    {
        WHEN("the undo list is empty")
        {
            THEN("nothing happens")
            {
                history.undo(editor);

                REQUIRE(undoCount == 0);
                REQUIRE(history.undoSize() == 0);
            }
        }

        WHEN("the undo list is not empty")
        {
            history.add(std::make_shared<TestUndoable>(undoCount, redoCount));

            THEN("undo is called and undoable is moved into redo list")
            {

                REQUIRE(history.undoSize() == 1);

                history.undo(editor);

                REQUIRE(undoCount == 1);
                REQUIRE(history.undoSize() == 0);
                REQUIRE(history.redoSize() == 1);
            }
        }
    }

    GIVEN("the user calls the redo action")
    {
        WHEN("the redo list is empty")
        {
            THEN("nothing happends")
            {
                history.redo(editor);

                REQUIRE(redoCount == 0);
                REQUIRE(history.redoSize() == 0);
            }
        }

        WHEN("the redo list is not empty")
        {

            THEN("redo is called and undoable is moved into undo list")
            {
                history.add(std::make_shared<TestUndoable>(undoCount, redoCount));
                history.undo(editor);
                history.redo(editor);

                REQUIRE(redoCount == 1);
                REQUIRE(history.undoSize() == 1);
                REQUIRE(history.redoSize() == 0);
            }
        }
    }
}
