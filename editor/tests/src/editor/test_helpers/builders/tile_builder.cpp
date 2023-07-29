#include "./tile_builder.h"

TileBuilder::TileBuilder(TileLayer &tileLayer): m_TileLayer(tileLayer)
{
}

void TileBuilder::withPos(Vec2Int pos)
{
    m_Pos = pos;
}

void TileBuilder::withColor(int color)
{
    m_Color = color;
}

Rect2D TileBuilder::build()
{

    Brush brush;

    brush.paint(m_TileLayer, m_Pos, m_Color);

    int tileIndex = tileLayer.getTileIndex(tilePos.x, tilePos.y);
}
