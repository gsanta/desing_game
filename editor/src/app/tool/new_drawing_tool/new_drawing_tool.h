#pragma once

#include "../tool.h"

namespace spright { namespace editor {

	class NewDrawingTool : public Tool {

	public:
		void pointerDown(PointerInfo& pointerInfo) override;
		void pointerUp(PointerInfo& pointerInfo) override;
		void pointerMove(PointerInfo& pointerInfo) override;
	};
}}