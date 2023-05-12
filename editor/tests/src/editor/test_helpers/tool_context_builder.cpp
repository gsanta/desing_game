#include "tool_context_builder.h"


ToolContextBuilder &ToolContextBuilder::withDocumentInfo(DocumentInfoBuilder builder)
{
    m_DocInfo = builder;
    return *this;
}

ToolContextBuilder &ToolContextBuilder::withPointerInfo(PointerInfoBuilder builder)
{
    m_PointerInfo = builder;
    return *this;
}

ToolContext ToolContextBuilder::build()
{
    ToolContext toolContext(std::make_shared<EditorState>());

    PointerInfo pointer = m_PointerInfo.build();
    DocumentInfo doc = m_DocInfo.build();

    toolContext.pointer = pointer;
    toolContext.doc = doc;

    return toolContext;
}
