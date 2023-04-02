#include "test_document_factory.h"

TestEventEmitter TestDocumentFactory::eventEmitter;

std::vector<TileLayer> TestDocumentFactory::createTileLayers(size_t num) {
	std::vector<TileLayer> layers;
	
	for (int i = 0; i < num; i++) {
		TileLayer layer("layer_" + std::to_string(i), Group<Rect2D>(new HeadlessRenderer2D()), Bounds::createWithPositions(-3.0f, 3.0f, -3.0f, 3.0f), 1.0f);

		layers.push_back(layer);
	}

	return layers;
}

TileLayer TestDocumentFactory::createTileLayer(size_t index, float tileSize, Bounds bounds) {
	TileLayer layer("layer_" + std::to_string(index), Group<Rect2D>(new HeadlessRenderer2D()), bounds, tileSize);

	return layer;
}

Drawing TestDocumentFactory::createDrawing(Bounds bounds) {
	return Drawing(bounds, &eventEmitter);
}


DocumentStore TestDocumentFactory::createDocumentStore() {
	float documentSize = 32.0f;
	float windowSize = 500.0f;
	Bounds documentBounds = Bounds::createWithPositions(-documentSize / 2.0f, documentSize / 2.0f, -documentSize / 2.0f, documentSize / 2.0f);
	Camera camera(windowSize, windowSize, documentBounds, -1.0f, 1.0f);

	Document* document = new Document(documentBounds, camera, createDrawing(documentBounds));

	DocumentStore documentStore;
	documentStore.setActiveDocument(document);

	return documentStore;
}

DocumentFactory TestDocumentFactory::createDocumentFactory(Container& windowContainer) {
	return DocumentFactory(&windowContainer, &eventEmitter);
}

