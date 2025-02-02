#pragma once
#include "../src/editing/history/document_history.h"
#include "../src/engine/scene/cameras/camera2d.h"
#include "../src/engine/system/utils/uuid_generator.h"
#include "../src/engine/system/window/impl/headless/headless_window.h"
#include "../src/maths/data/bounds.h"
#include "drawing_builder.h"

#include <memory>
#include <vector>

class DocumentBuilder
{
public:
    DocumentBuilder();

    DocumentBuilder &withEmptyDocument();

    DocumentBuilder &withDrawing(const DrawingBuilder &drawing);

    Document build();

private:
    Bounds m_DocumentBounds = Bounds::createWithPositions(-32.0f / 2.0f, -32.0f / 2.0f, 32.0f / 2.0f, 32.0f / 2.0f);

    HeadlessWindow m_Window;

    bool m_IsEmptyDocument = false;

    std::vector<DrawingBuilder> m_Drawings;
};
