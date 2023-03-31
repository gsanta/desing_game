#include "new_drawing_tool.h"

namespace spright { namespace editor {
	NewDrawingTool::NewDrawingTool(DocumentStore* documentStore) : m_DocumentStore(documentStore), Tool("new-drawing") {

	}

	void NewDrawingTool::pointerDown(PointerInfo& pointerInfo) {
		m_SelectionBox.setTileLayer(m_DocumentStore->getActiveDocument()->getDrawing(2)->getForegroundLayer());
		m_SelectionBox.start(pointerInfo.curr);
	}

	void NewDrawingTool::pointerUp(PointerInfo& pointerInfo) {

	}

	void NewDrawingTool::pointerMove(PointerInfo& pointerInfo) {
		if (pointerInfo.isDown) {
			m_SelectionBox.setPosition(pointerInfo.curr);
		}
	}
}}