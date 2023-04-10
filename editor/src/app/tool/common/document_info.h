
#include "../../document/drawing.h"
#include "../../document/document_store.h"

namespace spright { namespace editor {

    struct DocumentInfo {
        DocumentStore *m_DocumentStore;
        Drawing *m_ActiveDrawing = nullptr;
    public:
        DocumentInfo(DocumentStore* documentStore);
        Drawing *getActiveDrawing();
    };
}}
