#include "pan_tool.h"

namespace spright
{
namespace editor
{
    PanTool::PanTool(DocumentStore *documentStore) : m_DocumentStore(documentStore), Tool("pan")
    {
    }

    void PanTool::pointerMove(const ToolContext &context)
    {
        if (context.pointer.isDown)
        {
            Camera *camera = m_DocumentStore->getActiveDocument().getBackgroundCanvas().getCamera();
            Camera2d *camera2d = dynamic_cast<Camera2d *>(camera);

            camera2d->translate2D(context.pointer.prev - context.pointer.curr);
        }
    }
} // namespace editor
} // namespace spright
