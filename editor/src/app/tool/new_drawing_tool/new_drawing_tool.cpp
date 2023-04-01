#include "new_drawing_tool.h"

namespace spright { namespace editor {
	NewDrawingTool::NewDrawingTool(DocumentStore* documentStore, DocumentFactory* documentFactory) : m_DocumentStore(documentStore), m_DocumentFactory(documentFactory), Tool("new-drawing") {

	}

	void NewDrawingTool::pointerDown(PointerInfo& pointerInfo) {
		m_SelectionBox.setTileLayer(m_DocumentStore->getActiveDocument()->getDrawing(2)->getForegroundLayer());
		m_SelectionBox.start(pointerInfo.curr);
	}

	void NewDrawingTool::pointerUp(PointerInfo& pointerInfo) {
		m_DocumentFactory->createDrawing(m_DocumentStore->getActiveDocument(), m_SelectionBox.getBounds());
		m_SelectionBox.clear();
	}

	void NewDrawingTool::pointerMove(PointerInfo& pointerInfo) {
		if (pointerInfo.isDown) {
			m_SelectionBox.setPosition(pointerInfo.curr);
		}
	}
}}