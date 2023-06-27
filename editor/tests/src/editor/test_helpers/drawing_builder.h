#pragma once
#include "../src/engine/graphics/renderable/bounds.h"
#include "frame_builder.h"
#include "test_document_factory.h"
#include "tile_layer_builder.h"

#include <vector>

using namespace ::spright::engine;

class DrawingBuilder
{
public:
    DrawingBuilder &withBounds(Bounds bounds);

    DrawingBuilder &withTileSize(float tileSize);

    DrawingBuilder &withTileLayer(TileLayerBuilder);

    DrawingBuilder &withTileLayer();

    DrawingBuilder &withFrame(FrameBuilder);

    DrawingBuilder &withFrame(FrameBuilder, size_t repeat);

    Drawing build();

private:
    Drawing buildFromFrames();

    Drawing buildFromLayers();

private:
    Bounds m_Bounds = Bounds::createWithPositions(-3.0f, 3.0f, -3.0f, 3.0f);

    vector<TileLayerBuilder> m_TileLayers;

    vector<FrameBuilder> m_Frames;

    float m_TileSize = 0.5f;
};
