#pragma once

#include "../graphics/camera/arc_rotate_camera.h"
#include "../graphics/layer/group.h"
#include "../graphics/mesh/meshes/mesh.h"
#include "canvas.h"

namespace spright
{
namespace engine
{
    class Drawing3d : public Canvas
    {
    public:
        Drawing3d(const std::string &uuid, const Bounds &bounds, const Renderer2D &renderer);

        Drawing3d(const Drawing3d &drawing);

        ~Drawing3d() override = default;

        Drawing3d &operator=(const Drawing3d &other);

        Mesh &add(const Mesh &renderable);

        Group<Mesh> &getGroup();

        Group<Mesh> &getGizmoGroup();

        Drawing3d *clone() const override;

        void render(const Camera &camera, Canvas::RenderTarget target) override;

        void setCamera(const ArcRotateCamera &camera);

        ArcRotateCamera *getCamera() override;

    private:
        std::unique_ptr<ArcRotateCamera> m_Camera;

        Group<Mesh> m_Group;

        Group<Mesh> m_GizmoGroup;
    };
} // namespace engine
} // namespace spright
