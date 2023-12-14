#include "../../../../engine/graphics/mesh/meshes/box.h"
#include "../../../../engine/scene/cameras/arc_rotate_camera.h"
#include "../../../utils/conversions.h"
#include "../../pixel_tool.h"

#include <vector>

namespace spright
{
namespace editing
{
    using namespace engine;

    class MeshCreationTool : public PixelTool
    {
    public:
        MeshCreationTool();

        void pointerUp(ToolContext &context) override;
    };
} // namespace editing
} // namespace spright
