#include "test_document_factory.h"

std::vector<TileLayer> TestDocumentFactory::createTileLayers(size_t num)
{
    std::vector<TileLayer> layers;

    Bounds bounds = Bounds::createWithPositions(-3.0f, -3.0f, 3.0f, 3.0f);
    for (int i = 0; i < num; i++)
    {
        TileLayer layer("layer_" + std::to_string(i), Group<Rect2D>(bounds.getCenter()), bounds, 1.0f);

        layers.push_back(layer);
    }

    return layers;
}

TileLayer TestDocumentFactory::createTileLayer(size_t index, float tileSize, Bounds bounds)
{
    TileLayer layer("layer_" + std::to_string(index), Group<Rect2D>(bounds.getCenter()), bounds, tileSize);

    return layer;
}

DocumentFactory TestDocumentFactory::createDocumentFactory(Window &window)
{
    return DocumentFactory(&window, new HeadlessRendererProvider());
}
