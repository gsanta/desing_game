#pragma once

#include <vector>
#include "../../../engine/graphics/renderable/rect2d.h"
#include "../../document/document_store.h"
#include "../tool.h"
#include "../common/document_info.h"
#include "../common/selection_box.h"
#include "../../document/drawing.h"

namespace spright { namespace editor {
	using namespace ::spright::maths;
	using namespace ::spright::engine;
	using namespace editor;

	class SelectTool : public Tool {
	private:
		DocumentStore* m_DocumentStore;
		SelectionBox m_SelectionBox;

		vector<Rect2D*> m_Data;
		vector<Vec2> m_OrigPositions;

		float m_NoMovementTolerance = 0.1f;
		bool m_IsMove = false;

	public:
		SelectTool(DocumentStore* documentHandler);
		void pointerDown(PointerInfo& pointerInfo, DocumentInfo& documentInfo) override;
		void pointerUp(PointerInfo& pointerInfo, DocumentInfo& documentInfo) override;
		void pointerMove(PointerInfo& pointerInfo, DocumentInfo& documentInfo) override;
	private:
		void makeSelection(PointerInfo& pointerInfo, Drawing* activeDrawing);
		void makePointSelection(PointerInfo& pointerInfo, Drawing* activeDrawing);
		void moveSelection(Vec2 tileDelta, Drawing* activeDrawing);
	};
}}
