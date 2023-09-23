#pragma once

#include "document_info.h"
#include "pointer_info.h"
#include "tool_info.h"

#include <utility>

namespace spright
{
namespace editor
{

    struct ToolContext
    {
        PointerInfo pointer;

        DocumentInfo doc;

        ToolInfo tool;
    };
} // namespace editor
} // namespace spright
