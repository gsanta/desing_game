#include "paint_bucket_tool.h"
#include "paint_bucket_tool.h"

namespace spright { namespace editor {

	PaintBucketTool::PaintBucketTool(DocumentStore* documentStore, Services* services) : m_DocumentStore(documentStore), m_Services(services), Tool("paint_bucket")
	{
	}

	void PaintBucketTool::pointerUp(PointerInfo& pointerInfo, DocumentInfo& documentInfo)
	{
		if (!documentInfo.hasActiveDrawing()) {
			return;
		}

		TileLayer& tileLayer = documentInfo.activeDrawing->getActiveLayer();
		Vec2Int tilePos = tileLayer.getTilePos(pointerInfo.curr);

		m_FloodFill.floodFill(tileLayer, tilePos.x, tilePos.y, m_Services->getColorPalette()->color);
	}
}}
