#pragma once

#include "../../engine/graphics/renderable/rect2d.h"
#include "tool.h"
#include "../../maths/vec2.h"
#include "../../maths/vec3.h"
#include "../service/services.h"
#include "../document/document_store.h"
#include "../document/drawing.h"

namespace spright { namespace editor {

	using namespace ::spright::engine;

	class RectangleTool : public Tool {
	private:
		DocumentStore* m_DocumentStore;
		Services* m_Services;
		float m_Size = 10;
		Rect2D* m_Rect = nullptr;

	public:
		RectangleTool(DocumentStore* documentStore, Services* services);
		void pointerDown(PointerInfo& pointerInfo, Drawing* activeDrawing) override;
		void pointerUp(PointerInfo& pointerInfo, Drawing* activeDrawing) override;
		void pointerMove(PointerInfo& pointerInfo, Drawing* activeDrawing) override;
	};
}}
