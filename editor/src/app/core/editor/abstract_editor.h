#pragma once

#include "../../document/document.h"

namespace spright
{
namespace editor
{
    using namespace ::spright::engine;

    class AbstractEditor
    {
    public:
        virtual Document &getActiveDocument() = 0;
    };
} // namespace editor
} // namespace spright
