#pragma once

#include "tool/tool.h"
#include "tool/tool_context.h"
#include "../../engine/graphics/camera/ortho_projection_info.h"

namespace spright { namespace editor {
	using namespace ::spright::engine;

	class PanTool : public Tool
	{
	private:
		DocumentStore* m_DocumentStore;
		float m_ZoomFactor = 1.0f;

	public:
		PanTool(DocumentStore* documentStore);
	private:
		void pointerMove(ToolContext&) override;
	};
}}
