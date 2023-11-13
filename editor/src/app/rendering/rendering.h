#pragma once

#include "../../engine/system/window/window.h"
#include "../document/document_store.h"

namespace spright
{
using namespace ::spright::engine;
using namespace ::spright::editor;

class Rendering
{

public:
    Rendering(Window *window, DocumentStore *documentStore);

    void render();

    void enableImageTarget();

    void enableScreenTarget();

private:
    enum Target
    {
        SCREEN,
        IMAGE
    };

    Window *m_Window;

    DocumentStore *m_DocumentStore;

    Target m_RenderingTarget = Rendering::Target::SCREEN;
};
} // namespace spright
