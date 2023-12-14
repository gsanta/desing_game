#pragma once

#include "../../../../maths/data/bounds3.h"
#include "../../../../maths/vec3.h"
#include "../../colors.h"
#include "../../renderer/renderer2d.h"

#include <algorithm>

namespace spright
{
namespace engine
{
    using namespace maths;

    class Mesh
    {
    public:
        Mesh(int vertexCount);

        Mesh(int vertexCount, const Vec3 *positions);

        Mesh(int vertexCount, const Vec3 *positions, const unsigned int *colors);

        Mesh(const Mesh &other);

        virtual Mesh &operator=(const Mesh &other);

        virtual ~Mesh();

        const Vec3 *getPositions() const;

        const Bounds3 &getBounds3() const;

        virtual void submit(Renderer2D &renderer) const;

        virtual inline bool isEqual(const Mesh &obj) const
        {
            return false;
        }

        virtual bool operator==(const Mesh &rhs);

        virtual bool operator!=(const Mesh &rhs);

        virtual Mesh *clone() const;

        /**
         * Name can be set and get by the user and be used as a reference to the mesh
        */
        void setName(const std::string &name);

        const std::string &getName() const;

    private:
        void calcNormals();

        void createArrays(int positionCount);

    protected:
        void calcBounds();

    protected:
        Vec3 m_Position;

        Vec3 *m_Positions = nullptr;

        Vec3 *m_Normals = nullptr;

        int *m_Colors = nullptr;

        int m_VertexCount = 0;

        Bounds3 m_Bounds;

        std::string m_Name;
    };
} // namespace engine
} // namespace spright
