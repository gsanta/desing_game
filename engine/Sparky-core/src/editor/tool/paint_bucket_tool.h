#pragma once

#include "tool.h"
#include "../document/document_handler.h"

namespace spright_app { namespace tool {
    class PaintBucketTool : public Tool
    {
    private:
        document::DocumentHandler *m_DocumentHandler;

    public:
        //void pointerUp(PointerInfo &pointerInfo) override;
    };
}}
