#pragma once

#include "frame_listener.h"
#include <vector>;

namespace my_app_engine { namespace system {

	class FrameHandler {
	private:
		std::vector<FrameListener*> m_Listeners;
	public:
		void emitUpdate(float deltaTime);
		void registerListener(FrameListener* listener);
		void unRegisterListener(FrameListener* listener);
	};
}}