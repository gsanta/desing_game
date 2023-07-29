#pragma once;

#include "../editor/abstract_editor.h"
#include "undoable.h"

#include <memory>
#include <vector>

namespace spright
{
namespace editor
{
    class History
    {

    public:
        void add(std::shared_ptr<Undoable> undoable);

        voidß undo(AbstractEditor &editor);

        void redo(AbstractEditor &editor);

        size_t undoSize();

        size_t redoSize();

    private:
        std::vector<std::shared_ptr<Undoable>> m_UndoList;

        std::vector<std::shared_ptr<Undoable>> m_RedoList;
    };
} // namespace editor
} // namespace spright
