#pragma once

#include "../../../../maths/data/bounds.h"
#include "../../../../maths/vec2.h"
#include "../../../../maths/vec3.h"
#include "../../../../maths/vec4.h"
#include "../../buffer/buffer.h"
#include "../../buffer/indexBuffer.h"
#include "../../buffer/vertexArray.h"
#include "../../colors.h"
#include "../../renderer/renderer2d.h"
#include "../../renderer/vertex_data.h"
#include "../../shader/shader.h"
#include "mesh.h"

#include <nlohmann/json.hpp>
#include <string.h>
namespace spright
{
namespace engine
{
    class Renderable2D : public Mesh
    {
    public:
        Renderable2D(int vertexCount);

        Renderable2D(int vertexCount, const Vec3 *positions, const unsigned int *colors);

        Renderable2D(const Renderable2D &other);

        friend bool operator==(const Renderable2D &, const Renderable2D &);

        friend bool operator!=(const Renderable2D &, const Renderable2D &);

        virtual bool isEqual(const Renderable2D &obj) const;

        const Bounds getBounds() const;

        virtual nlohmann::json getJson() = 0;

        static std::shared_ptr<Renderable2D> create(double width, double height);

        virtual Renderable2D *clone() const = 0;

    protected:
    };
} // namespace engine
} // namespace spright
