#include "document_store_builder.h"

DocumentStoreBuilder &DocumentStoreBuilder::withWindowSize(int windowSize)
{
    m_WindowSize = windowSize;

    return *this;
}

DocumentStoreBuilder &DocumentStoreBuilder::withDocumentBounds(Bounds bounds)
{
    m_DocumentBounds = bounds;

    return *this;
}

DocumentStoreBuilder &DocumentStoreBuilder::withDrawing(DrawingBuilder builder)
{
    m_Drawings.push_back(builder);

    return *this;
}

DocumentStoreBuilder &DocumentStoreBuilder::withDrawing()
{
    DrawingBuilder builder;
    m_Drawings.push_back(builder.withTileLayer());

    return *this;
}

DocumentStore DocumentStoreBuilder::build()
{
    Camera camera(m_WindowSize, m_WindowSize, m_DocumentBounds, -1.0f, 1.0f);

    Document document(m_DocumentBounds, camera, DrawingBuilder().withBounds(m_DocumentBounds).build());

    if (m_Drawings.size() == 0)
    {
        m_Drawings.push_back(DrawingBuilder().withBounds(m_DocumentBounds));
    }

    for (DrawingBuilder builder : m_Drawings)
    {
        document.addDrawing(builder.build());
    }

    DocumentStore documentStore;
    documentStore.addDocument(document);

    return documentStore;
}
