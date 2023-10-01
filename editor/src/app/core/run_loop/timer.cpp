#include "timer.h"

#ifdef SPARKY_EMSCRIPTEN
#include "ems_timer.h"
#elif _WIN32
#include "win_timer.h"
#else
#include "unix_timer.h"
#endif

namespace spright
{
namespace editor
{
    Timer *Timer::getTimer()
    {
#ifdef SPARKY_EMSCRIPTEN
        return new EmsTimer();
#elif _WIN32
        return new WinTimer();
#else
        return new UnixTimer();
#endif
    }
} // namespace editor
} // namespace spright
