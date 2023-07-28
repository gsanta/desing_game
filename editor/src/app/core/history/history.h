#pragma once;

#include "../editor/abstract_editor.h"
#include "undoable.h"
#include <vector>

namespace spright {
    namespace editor {
        class History {

        public:
            void add(const Undoable& undoable);

            void undo(AbstractEditor& editor);

            size_t undoSize();

            // void redo(AbstractEditor& editor);

        private:
            std::vector<Undoable> undoList;
        };
    }
}
