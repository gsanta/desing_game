#pragma once

#include "../../document/document.h"

namespace spright {
    namespace editor
    {
        using namespace ::spright::engine;

        class AbstractEditor {

            virtual Document &getActiveDocument() = 0;
        };
    }
}
