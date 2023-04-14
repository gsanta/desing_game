#include "pointer_info.h"

namespace spright
{
namespace editor
{

    PointerInfo::PointerInfo() : buttons{false, false, false}
    {
    }

    inline bool PointerInfo::isLeftButtonDown() const
    {
        return buttons[0];
    }

    inline bool PointerInfo::isRightButtonDown() const
    {
        return buttons[1];
    }

    inline bool PointerInfo::isMiddleButtonDown() const
    {
        return buttons[2];
    }

} // namespace editor
} // namespace spright
