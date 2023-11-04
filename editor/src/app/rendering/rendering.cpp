#include "rendering.h"

namespace spright
{
Rendering::Rendering(Window *window, DocumentStore *documentStore) : m_Window(window), m_DocumentStore(documentStore)
{
    m_ScreenTargetRenderer = ScreenTargetRenderer(documentStore);
    m_ImageTargetRenderer = ImageTargetRenderer(documentStore, window);

    m_ScreenTargetRenderer.enable();
}

void Rendering::render()
{
    m_Window->beforeRender();

    Document &document = m_DocumentStore->getActiveDocument();

    renderer.begin();

    renderer.getShader().setUniformMat4("pr_matrix", document.getCamera().getProjectionMatrix());

    renderer.push(document.getCamera().getViewMatrix());

    if (m_RenderingTarget == Rendering::Target::SCREEN)
    {
        for (std::unique_ptr<Canvas> &canvas : document.getCanvases())
        {
            canvas->render(document.getCamera(), Canvas::Screen);
        }
    }
    else
    {
        Drawing *activeDrawing = document.getActiveDrawing();
        if (activeDrawing != nullptr)
        {
            activeDrawing->render(document.getCamera(), Canvas::Image);
        }
    }

    m_Window->afterRender();
}

void Rendering::enableImageTarget()
{
    if (m_RenderingTarget != Rendering::Target::IMAGE)
    {
        m_ScreenTargetRenderer.disable();
        m_ImageTargetRenderer.enable();
        m_RenderingTarget = Rendering::Target::IMAGE;
    }
}

void Rendering::enableScreenTarget()
{
    if (m_RenderingTarget != Rendering::Target::SCREEN)
    {
        m_ImageTargetRenderer.disable();
        m_ScreenTargetRenderer.enable();
        m_RenderingTarget = Rendering::Target::SCREEN;
    }
}
} // namespace spright
