#pragma once

#include "../../engine/graphics/renderable/rect2d.h"
#include "tool.h"
#include "common/document_info.h"
#include "../../maths/vec2.h"
#include "../../maths/vec3.h"
#include "../service/services.h"
#include "../document/document_store.h"

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
		void pointerDown(PointerInfo& pointerInfo, DocumentInfo& documentInfo) override;
		void pointerUp(PointerInfo& pointerInfo, DocumentInfo& documentInfo) override;
		void pointerMove(PointerInfo& pointerInfo, DocumentInfo& documentInfo) override;
	};
}}
