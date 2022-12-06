#include "bounds.h"

namespace spright_engine { namespace graphics {

    maths::Vec2 Bounds::getCenter() const
    {
        return maths::Vec2(minX + (maxX - minX) / 2.0, minY + (maxY - minY) / 2.0);
    }

}}
