#include "history.h"

namespace spright {
    namespace editor {

        void History::add(const Undoable &undoable) {
            undoList.push_back(undoable);
        }

        void History::undo(AbstractEditor &editor) {
            undoList.back().undo(editor);
            undoList.pop_back();
        }

        size_t History::undoSize() {
            return undoList.size();
        }
    }
}
