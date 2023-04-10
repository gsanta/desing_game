#include "select_tool.h"

namespace spright { namespace editor {

	SelectTool::SelectTool(DocumentStore* documentStore) : m_DocumentStore(documentStore), Tool("select")
	{
	}

	void SelectTool::pointerDown(PointerInfo& pointerInfo, DocumentInfo& documentInfo)
	{
		if (documentInfo.hasActiveDrawing()) {
			m_SelectionBox.setTileLayer(documentInfo.activeDrawing->getForegroundLayer());
			m_IsMove = m_SelectionBox.isInsideSelection(pointerInfo.curr);

			if (!m_IsMove) {
				m_SelectionBox.start(pointerInfo.curr);
			}
		}
	}

	void SelectTool::pointerUp(PointerInfo& pointerInfo, DocumentInfo& documentInfo)
	{
		if (!documentInfo.hasActiveDrawing()) {
			return;
		}

		if (Vec2::distance(pointerInfo.down, pointerInfo.curr) < m_NoMovementTolerance) {
			makePointSelection(pointerInfo, documentInfo.activeDrawing);
		}
		else {
			makeSelection(pointerInfo, documentInfo.activeDrawing);
		}

		m_IsMove = false;
	}

	void SelectTool::pointerMove(PointerInfo& pointerInfo, DocumentInfo& documentInfo)
	{
		if (!pointerInfo.isLeftButtonDown()) {
			return;
		}

		if (m_IsMove) {
			Vec2 delta = m_SelectionBox.move(pointerInfo.curr - pointerInfo.prev);
			moveSelection(delta, documentInfo.activeDrawing);
		}
		else {
			m_SelectionBox.setPosition(pointerInfo.curr);
		}
	}

	void SelectTool::makeSelection(PointerInfo& pointerInfo, Drawing* activeDrawing) {
		m_Data.clear();
		m_OrigPositions.clear();

		if (activeDrawing == nullptr) {
			return;
		}

		Vec2 down = pointerInfo.down;
		Vec2 curr = pointerInfo.curr;

		float startX = down.x < curr.x ? down.x : curr.x;
		float endX = down.x < curr.x ? curr.x : down.x;
		float startY = down.y < curr.y ? down.y : curr.y;
		float endY = down.y < curr.y ? curr.y : down.y;
		Bounds selectionBounds = Bounds::createWithPositions(startX, endX, startY, endY);

		TileLayer& layer = activeDrawing->getActiveLayer();

		auto it = layer.getRenderables().begin();
		while (it != layer.getRenderables().end()) {
			Vec2 pos = (*it)->getCenterPosition2d();

			if (selectionBounds.contains(pos.x, pos.y)) {
				Rect2D* sprite = static_cast<Rect2D*>(*it);
				m_Data.push_back(sprite);
				m_OrigPositions.push_back(Vec2(sprite->getPosition().x, sprite->getPosition().y));
			}
			++it;
		}
	}

	void SelectTool::moveSelection(Vec2 tileDelta, Drawing* activeDrawing) {
		if (activeDrawing == nullptr) {
			return;
		}

		TileLayer& tileLayer = activeDrawing->getActiveLayer();

		for (int i = 0; i < m_Data.size(); i++) {
			Rect2D* sprite = m_Data[i];

			sprite->translate(tileDelta);
		}

		for (Rect2D* sprite : m_Data) {
			Vec2Int tilePos = tileLayer.getTilePos(sprite->getPosition2d());
			int newTileIndex = tileLayer.getTileIndex(tilePos.x, tilePos.y);
			tileLayer.updateTileIndex(sprite, newTileIndex);
		}
	}

	void SelectTool::makePointSelection(PointerInfo& pointerInfo, Drawing* activeDrawing) {
		if (activeDrawing == nullptr) {
			return;
		}
		TileLayer& tileLayer = activeDrawing->getActiveLayer();
		Camera& camera = m_DocumentStore->getActiveDocument().getCamera();
		Vec2 model = camera.screenToModel(pointerInfo.curr);

		Vec2Int tilePos = tileLayer.getTilePos(model);
		int tileIndex = tileLayer.getTileIndex(tilePos.x, tilePos.y);
		Renderable2D* renderable = tileLayer.getAtTileIndex(tileIndex);

		if (renderable != nullptr) {
			Rect2D* sprite = static_cast<Rect2D*>(renderable);
			m_Data.push_back(sprite);
			m_OrigPositions.push_back(Vec2(sprite->getPosition().x, sprite->getPosition().y));

			Vec2 spritePos = sprite->getPosition2d();
			float tileSize = tileLayer.getTileSize();
		}
	}
}}
