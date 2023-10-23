#include "./sprite_sheet.h"

namespace spright
{
namespace editor
{

    SpriteSheet::SpriteSheet(std::shared_ptr<DocumentFactory> documentFactory, Document *document)
        : m_DocumentFactory(documentFactory), m_Document(document)
    {
    }

    void SpriteSheet::generateSpriteSheet(Drawing &drawing)
    {
        int frameCount = drawing.getFrames().size();

        float startX = drawing.getBounds().maxX + 2.0f;
        float endX = startX + (drawing.getBounds().getWidth() / 2.0f) * frameCount;
        float startY = drawing.getBounds().minY + drawing.getBounds().getHeight() / 2.0;
        float endY = drawing.getBounds().maxY;

        CreateDrawingProps spriteSheetProps(Bounds(startX, startY, endX, endY));
        spriteSheetProps.tileSize = drawing.getActiveLayer().getTileSize() / 2.0f;
        spriteSheetProps.backgroundLayerTileSize = drawing.getBackgroundLayer().getTileSize() / 2.0f;

        Drawing spriteSheet = m_DocumentFactory->createDrawing(spriteSheetProps);

        float layerWidth = drawing.getActiveLayer().getTileBounds().getWidth();

        for (int i = 0; i < drawing.getFrames().size(); i++)
        {
            TileLayer &layer = drawing.getFrames()[i].getLayer(0);
            tile_operation_copy_area(layer,
                                     spriteSheet.getActiveLayer(),
                                     layer.getTileBounds(),
                                     Vec2Int(i * layerWidth, 0));
        }

        // tile_operation_copy_area(drawing.getActiveLayer(),
        //                          spriteSheet.getActiveLayer(),
        //                          drawing.getActiveLayer().getTileBounds(),
        //                          Vec2Int(drawing.getActiveLayer().getTileBounds().getWidth(), 0));


        m_Document->addDrawing(std::make_shared<Drawing>(spriteSheet));
    }
} // namespace editor
} // namespace spright
