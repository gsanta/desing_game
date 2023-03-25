#include "frame_player.h"

namespace spright { namespace editor {

	FramePlayer::FramePlayer(): m_Elapsed(0) {

	}

	void FramePlayer::update(double elapsed) {
		m_Elapsed += elapsed;

		if (m_Elapsed > 1000.0) {
			std::cout << "1 sec" << std::endl;
			m_Elapsed = 0;
		}
	}
}}
