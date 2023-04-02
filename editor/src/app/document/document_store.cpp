#include "document_store.h"

namespace spright { namespace editor {

	DocumentStore::DocumentStore() {
	}

	DocumentStore::~DocumentStore() {
	
		if (m_ActiveDocument) {
			delete m_ActiveDocument;
		}
	}

	Document* DocumentStore::getActiveDocument() const {
		return m_ActiveDocument;
	}

	void DocumentStore::setActiveDocument(Document* document)
	{
		m_ActiveDocument = document;
	}

	bool DocumentStore::hasActiveDocument() const {
		return m_ActiveDocument != nullptr;
	}
}}