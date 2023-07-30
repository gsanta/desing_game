#include "test_editor.h"

TestEditor::TestEditor(Document document) : m_Document(document)
{
}

TestEditor::~TestEditor()
{
}


Document &TestEditor::getActiveDocument()
{
    return m_Document;
}

void TestEditor::setDocument(const Document &document) {
    m_Document = document;
}
