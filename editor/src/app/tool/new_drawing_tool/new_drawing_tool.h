#pragma once

#include "../tool/tool.h"
#include "../tool/tool_context.h"
#include "../common/selection_box.h"
#include "../../document/document_store.h"
#include "../../document/drawing.h"
#include "../../document/factory/document_factory.h"

namespace spright { namespace editor {

	class NewDrawingTool : public Tool {
	private:
		SelectionBox m_SelectionBox;
		DocumentStore* m_DocumentStore;
		DocumentFactory* m_DocumentFactory;
	public:
		NewDrawingTool(DocumentStore* documentStore, DocumentFactory* documentFactory);
		void pointerDown(ToolContext &) override;
		void pointerUp(ToolContext &) override;
		void pointerMove(ToolContext &) override;
	};
}}
