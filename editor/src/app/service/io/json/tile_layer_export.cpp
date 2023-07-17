#include "tile_layer_export.h"

namespace spright
{
namespace editor
{
    TileLayerExport::TileLayerExport(DocumentFactory *documentFactory) : m_DocumentFactory(documentFactory)
    {
    }

    nlohmann::json TileLayerExport::exportLayer(const TileLayer &layer)
    {
        nlohmann::json json;

        json["layerType"] = "tile";
        json["tileW"] = layer.getTileBounds().getWidth();
        json["tileH"] = layer.getTileBounds().getHeight();
        json["name"] = layer.getName();
        json["index"] = layer.getIndex();
        for (int i = 0; i < layer.getIndexSize(); i++)
        {
            if (layer.getAtTileIndex(i) != nullptr)
            {
                unsigned int color = layer.getAtTileIndex(i)->getColor();
                json["tiles"] += {{"i", i}, {"c", color}};
            }
        }

        std::string string = json.dump();
        return json;
    }


    void TileLayerExport::importLayer(Document &document, nlohmann::json json)
    {
        std::string string = json.dump();

        m_DocumentFactory->createUserLayer(document.getActiveDrawing(), json["name"]);
        TileLayer &layer = document.getActiveFrame().getLayers().back();

        int tileCount = json["tiles"].size();

        for (int i = 0; i < tileCount; i++)
        {
            nlohmann::json tile = json["tiles"][i];

            Vec2 bottomLeftPos = layer.getCenterPos(tile["i"]);
            float tileSize = layer.getTileSize();
            layer.add(Rect2D(bottomLeftPos.x, bottomLeftPos.y, tileSize, tileSize, tile["c"]));
        }
    }
} // namespace editor
} // namespace spright
