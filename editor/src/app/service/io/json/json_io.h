#pragma once
#include <nlohmann/json.hpp>
#include "../../../document/document.h"
#include "../../../../engine/graphics/layer/tileLayer.h"
#include "tile_layer_export.h"
#include "../../../document/factory/document_factory.h"

namespace spright { namespace editor {

	class JsonIO {
	private:
		DocumentFactory* m_DocumentFactory;
		TileLayerExport* m_TileLayerExport;
		int m_i;

	public:
		JsonIO(DocumentFactory* documentHandler);

		~JsonIO();

		nlohmann::json exportDocument(Document& document);
		Document importDocument(std::string string) const;
	};
}}
