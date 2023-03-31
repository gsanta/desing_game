#pragma once

#include "../tool.h"
#include "../common/selection_box.h"
#include "../../document/document_store.h"

namespace spright { namespace editor {

	class NewDrawingTool : public Tool {
	private:
		SelectionBox m_SelectionBox;
		DocumentStore* m_DocumentStore;
	public:
		NewDrawingTool(DocumentStore* documentStore);
		void pointerDown(PointerInfo& pointerInfo) override;
		void pointerUp(PointerInfo& pointerInfo) override;
		void pointerMove(PointerInfo& pointerInfo) override;
	};
}}