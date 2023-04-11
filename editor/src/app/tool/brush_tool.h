#pragma once
#include <vector>
#include "tool/tool.h"
#include "tool/tool_context.h"
#include "colorable.h"
#include "../../engine/graphics/renderable/rect2d.h"
#include "../../engine/graphics/renderable/renderable2d.h"
#include "../editor_config.h"
#include "../document/document_store.h"
#include "../document/drawing.h"
#include "brush.h"

namespace spright { namespace editor {
	using namespace ::spright::engine;
	using namespace spright::maths;

	class BrushTool : public Tool, public Colorable
	{
	private:
		DocumentStore *m_documentStore;
		int m_Size = 1;
		Rect2D *sprite;
		Brush brush;

	public:
		BrushTool(DocumentStore* documentStore);

		void setSize(int size);
		void pointerMove(ToolContext &) override;
		void pointerDown(ToolContext &) override;
	private:
		void paint(PointerInfo& pointerInfo);
	};
}}
