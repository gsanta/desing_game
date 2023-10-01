
#pragma once

#include "../src/app/core/run_loop/timer.h"

using namespace spright::editor;

class MockTimer : public Timer {
public:
	inline void reset() override {

	}

	inline long elapsed() override {
		return 0;
	}
};
