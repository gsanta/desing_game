#include "document_history.h"

namespace spright
{
namespace editing
{

    void DocumentHistory::add(std::shared_ptr<Undoable> undoable)
    {

        m_UndoList.push_back(undoable);
    }

    void DocumentHistory::undo(Document &document)
    {
        if (m_UndoList.size() > 0)
        {
            m_UndoList.back()->undo(document);
            m_RedoList.push_back(m_UndoList.back());
            m_UndoList.pop_back();
        }
    }

    void DocumentHistory::redo(Document &document)
    {
        if (m_RedoList.size() > 0)
        {
            m_RedoList.back()->redo(document);
            m_UndoList.push_back(m_RedoList.back());
            m_RedoList.pop_back();
        }
    }

    Undoable *DocumentHistory::peek()
    {
        return m_UndoList.back().get();
    }

    void DocumentHistory::pop()
    {
        m_UndoList.pop_back();
    }

    size_t DocumentHistory::undoSize()
    {
        return m_UndoList.size();
    }

    size_t DocumentHistory::redoSize()
    {
        return m_RedoList.size();
    }
} // namespace editing
} // namespace spright
