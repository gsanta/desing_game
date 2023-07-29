#include "history.h"

namespace spright
{
namespace editor
{

    void History::add(std::shared_ptr<Undoable> undoable)
    {

        m_UndoList.push_back(undoable);
    }

    void History::undo(AbstractEditor &editor)
    {
        if (m_UndoList.size() > 0)
        {
            m_UndoList.back()->undo(editor);
            m_RedoList.push_back(m_UndoList.back());
            m_UndoList.pop_back();
        }
    }

    void History::redo(AbstractEditor &editor)
    {
        if (m_RedoList.size() > 0)
        {
            m_RedoList.back()->redo(editor);
            m_UndoList.push_back(m_RedoList.back());
            m_RedoList.pop_back();
        }
    }

    size_t History::undoSize()
    {
        return m_UndoList.size();
    }

    size_t History::redoSize()
    {
        return m_RedoList.size();
    }
} // namespace editor
} // namespace spright
