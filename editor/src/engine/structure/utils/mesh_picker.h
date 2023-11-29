#pragma once

#include "picked_mesh_info.h"
#include "../drawing3d.h"
#include "../../../maths/data/ray3.h"
#include "../../../maths/vec3.h"
#include "../../../maths/vec2.h"

namespace spright
{
namespace engine
{
    class MeshPicker
    {
    public:
        PickedMeshInfo pickWithScreenPos(Drawing3d drawing, Vec2 screenPos);
    };
} // namespace engine
} // namespace spright
