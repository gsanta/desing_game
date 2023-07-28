#pragma once

#include "../editor/abstract_editor.h"

namespace spright
{
namespace editor
{
    class Undoable {
    public:
        void undo(AbstractEditor& editor) const;

        void redo(AbstractEditor& editor) const;
    };
}
} // namespace spright
