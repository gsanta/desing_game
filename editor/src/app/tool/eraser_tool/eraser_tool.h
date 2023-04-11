#pragma once

#include <vector>
#include <memory>
#include "../../../engine/graphics/renderable/rect2d.h"
#include "../../../engine/graphics/renderable/renderable2d.h"
#include "../../document/document_store.h"
#include "../tool/tool.h"
#include "../tool/tool_context.h"
#include "../helper/layer_provider.h"
#include "eraser.h"
#include "eraser_stroke.h"
#include "../../document/drawing.h"

namespace spright { namespace editor {
	using namespace spright::maths;
	using namespace spright::engine;

	class EraserTool : public Tool {
	private:
		DocumentStore* m_documentStore;

		Eraser m_Eraser;
		EraserStroke m_EraserStroke;

		int m_Size = 3;

		float m_DashSize = 0.2f;
		bool m_IsMoveSelection = false;

		float m_NoMovementTolerance = 0.1f;

	public:
		EraserTool(int eraserSize);
		void pointerDown(ToolContext &) override;
		void pointerMove(ToolContext &) override;
		void deactivate(ToolContext &) override;
		void setOptions(std::string json) override;
		std::string getOptions() override;
	};
}}
