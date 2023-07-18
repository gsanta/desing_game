#include "tile_layer_export.h"

namespace spright
{
namespace editor
{
    TileLayerExport::TileLayerExport(DocumentFactory *documentFactory) : m_DocumentFactory(documentFactory)
    {
    }

    nlohmann::json TileLayerExport::exportLayer(const TileLayer &layer) const
    {
        nlohmann::json json;

        json["layerType"] = "tile";
        json["bounds"] = layer.getBounds().toArray();
        json["name"] = layer.getName();
        json["index"] = layer.getIndex();
        for (int i = 0; i < layer.getIndexSize(); i++)
        {
            if (layer.getAtTileIndex(i) != nullptr)
            {
                unsigned int color = layer.getAtTileIndex(i)->getColor();
                json["tiles"] += color;
            } else {
                json["tiles"] += -1;
            }
        }

        std::string string = json.dump();
        return json;
    }


    TileLayer TileLayerExport::importLayer(nlohmann::json json) const
    {
        nlohmann::json b = json["bounds"];
        Bounds bounds = Bounds::createWithPositions(b[0].get<float>(), b[1].get<float>(), b[2].get<float>(), b[3].get<float>());

        TileLayer layer = m_DocumentFactory->createUserLayer(bounds, json["name"]);

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
