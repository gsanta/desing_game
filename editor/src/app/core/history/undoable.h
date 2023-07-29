#pragma once

#include "../editor/abstract_editor.h"

#include <memory>

namespace spright
{
namespace editor
{
    class Undoable
    {
    public:
        virtual void undo(AbstractEditor &editor) const = 0;

        virtual void redo(AbstractEditor &editor) const = 0;
    };
} // namespace editor
} // namespace sprightß
