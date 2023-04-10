#include "new_drawing_tool.h"

namespace spright { namespace editor {
	NewDrawingTool::NewDrawingTool(DocumentStore* documentStore, DocumentFactory* documentFactory) : m_DocumentStore(documentStore), m_DocumentFactory(documentFactory), Tool("new_drawing") {

	}

	void NewDrawingTool::pointerDown(PointerInfo& pointerInfo, DocumentInfo& documentInfo) {
		m_SelectionBox.setTileLayer(m_DocumentStore->getActiveDocument().getCanvas().getForegroundLayer());
		m_SelectionBox.start(pointerInfo.curr);
	}

	void NewDrawingTool::pointerUp(PointerInfo& pointerInfo, DocumentInfo& documentInfo) {
		Drawing drawing = m_DocumentFactory->createDrawing(m_SelectionBox.getBounds());
		m_DocumentStore->getActiveDocument().addDrawing(drawing);
		m_SelectionBox.clear();
	}

	void NewDrawingTool::pointerMove(PointerInfo& pointerInfo, DocumentInfo& documentInfo) {
		if (pointerInfo.isDown) {
			m_SelectionBox.setPosition(pointerInfo.curr);
		}
	}
}}
