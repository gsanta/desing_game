#pragma once
#include "../../document/drawing.h"
#include "../../document/document_store.h"

namespace spright { namespace editor {

    struct DocumentInfo {
        Drawing *prevDrawing = nullptr;
        Drawing *activeDrawing = nullptr;
        bool isLeavingDrawing = false;

        bool hasActiveDrawing();
        bool hasPrevDrawing();
    };
}}
