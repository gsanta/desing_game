#pragma once
#include "../src/maths/vec2.h"
#include "../src/app/tool/tool/pointer_info.h"

using namespace spright::maths;
using namespace spright::editor;

class PointerInfoBuilder {
    private:
        Vec2 m_Curr;
    public:
        PointerInfoBuilder& withCurr(Vec2 curr);
        PointerInfo build();
};
