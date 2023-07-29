#pragma once
#include "../src/app/core/editor/abstract_editor.h"
#include "../src/app/document/document.h"

using namespace spright::editor;

class TestEditor : public AbstractEditor
{
public:
    TestEditor(Document document);

    ~TestEditor();

    Document &getActiveDocument() override;

private:
    Document m_Document;
};
