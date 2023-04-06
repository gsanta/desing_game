#include "unix_timer.h"

namespace spright { namespace editor {

	void UnixTimer::start() {
		m_Previous = getTime();
	}

	float UnixTimer::elapsed() {
    // double current = getTime();
    // float elapsed = current - m_Previous;
		// m_Previous = current;
		// return elapsed;
    return 1.1f;
	}

  // double UnixTimer::getTime() {
  //   // return time(NULL);
  //   return 1;
  // }
}}
