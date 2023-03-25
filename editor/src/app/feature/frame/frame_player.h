#pragma once

#include <iostream>
#include "../../core/run_loop/timed.h"

namespace spright { namespace editor {

	class FramePlayer : public Timed {
	private:
		double m_Elapsed;
	public:
		FramePlayer();
		void update(double elapsed) override;
	};
}}
