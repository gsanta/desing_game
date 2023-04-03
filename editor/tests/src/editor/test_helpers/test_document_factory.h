#pragma once
#include <vector>
#include "../src/engine/graphics/layer/tileLayer.h"
#include "../src/engine/graphics/renderable/bounds.h"
#include "../src/app/document/document.h"
#include "../src/engine/graphics/impl/headless/headless_renderer2d.h"
#include "../src/app/document/document_store.h"
#include "../src/app/document/document_factory.h"
#include "test_event_emitter.h"

using namespace ::spright::engine;
using namespace ::spright::editor;

class TestDocumentFactory {
public:
	static TestEventEmitter eventEmitter;
	static std::vector<TileLayer> createTileLayers(size_t num);
	static TileLayer createTileLayer(size_t index, float tileSize = TileLayer::defaultTileSize, Bounds bounds = Bounds::createWithPositions(-3.0f, 3.0f, -3.0f, 3.0f));
	//static Drawing createDrawing(CreateDrawingProps props);
	//static DocumentStore createDocumentStore(CreateDocumentStoreProps props);
	static DocumentFactory createDocumentFactory(Container& windowContainer);
};

class TileLayerBuilder {
private:
	size_t m_Index;
	float m_TileSize = TileLayer::defaultTileSize;
	Bounds m_Bounds = Bounds::createWithPositions(-3.0f, 3.0f, -3.0f, 3.0f);
public:
	inline TileLayerBuilder& withBounds(Bounds bounds) {
		m_Bounds = bounds;

		return *this;
	}

	inline TileLayerBuilder& withIndex(size_t index) {
		m_Index = index;

		return *this;
	}

	inline TileLayerBuilder& withTileSize(float tileSize) {
		m_TileSize = tileSize;

		return *this;
	}

	inline TileLayer build() {
		TileLayer layer("layer_" + std::to_string(m_Index), Group<Rect2D>(new HeadlessRenderer2D()), m_Bounds, m_TileSize);

		return layer;
	}

	static TileLayerBuilder TileLayerBuilder::create() {
		return TileLayerBuilder();
	}
};

struct DrawingBuilder {
	Bounds m_Bounds;
	vector<TileLayerBuilder> m_TileLayers;

	inline DrawingBuilder& withBounds(Bounds bounds) {
		m_Bounds = bounds;

		return *this;
	}

	inline DrawingBuilder& withTileLayer(TileLayerBuilder props) {
		m_TileLayers.push_back(props);

		return *this;
	}

	inline DrawingBuilder& withTileLayer() {
		TileLayerBuilder builder;
		m_TileLayers.push_back(builder);

		return *this;
	}

	inline Drawing build() {
		Drawing drawing(m_Bounds, &TestDocumentFactory::eventEmitter);

		FrameImpl frame(0);

		TileLayer foregroundLayer("", Group<Rect2D>(new HeadlessRenderer2D()), m_Bounds);
		TileLayer backgroundLayer("", Group<Rect2D>(new HeadlessRenderer2D()), m_Bounds, 2.0f);

		drawing.getFrameStore().addFrame(frame);
		drawing.getActiveFrame().addBackgroundLayer(backgroundLayer);
		drawing.getActiveFrame().addForegroundLayer(foregroundLayer);

		for (TileLayerBuilder& builder : m_TileLayers) {
			TileLayer layer = builder.build();
			drawing.addLayer(layer);
		}

		return drawing;
	}
};

struct DocumentStoreBuilder {
	vector<DrawingBuilder> m_Drawings;
	Bounds m_DocumentBounds = Bounds::createWithPositions(-32.0f / 2.0f, 32.0f / 2.0f, -32.0f / 2.0f, 32.0f / 2.0f);
	int m_WindowSize = 500;

	inline DocumentStoreBuilder& withWindowSize(int windowSize) {
		m_WindowSize = windowSize;

		return *this;
	}

	inline DocumentStoreBuilder& withDocumentBounds(Bounds bounds) {
		m_DocumentBounds = bounds;

		return *this;
	}

	inline DocumentStoreBuilder& withDrawing(DrawingBuilder builder) {
		m_Drawings.push_back(builder);

		return *this;
	}

	inline DocumentStoreBuilder& withDrawing() {
		DrawingBuilder builder;
		m_Drawings.push_back(builder);

		return *this;
	}

	inline DocumentStore build() {
		Camera camera(m_WindowSize, m_WindowSize, m_DocumentBounds, -1.0f, 1.0f);

		Document* document = new Document(m_DocumentBounds, camera, DrawingBuilder().withBounds(m_DocumentBounds).build());

		for (DrawingBuilder builder : m_Drawings) {
			document->addDrawing(builder.build());
		}

		DocumentStore documentStore;
		documentStore.setActiveDocument(document);

		return documentStore;
	}
};
