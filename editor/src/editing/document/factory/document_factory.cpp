#include "document_factory.h"

namespace spright
{
namespace editing
{

    DocumentFactory::DocumentFactory(Window *window, RendererProvider *rendererProvider)
        : m_Window(window), m_RendererProvider(rendererProvider)
    {
    }

    DocumentFactory::DocumentFactory(const DocumentFactory &other) : m_Window(other.m_Window)
    {
        m_RendererProvider = other.m_RendererProvider->clone();
    }

    DocumentFactory::~DocumentFactory()
    {
        delete m_RendererProvider;
    }

    TileLayer DocumentFactory::createUserLayer(const Bounds &bounds, std::string name, float tileSize) const
    {
        return TileLayer(name, Group<Rect2D>(), bounds, tileSize);
    }

    TileLayer DocumentFactory::createTileLayer(std::string name, const Bounds &bounds, float tileSize) const
    {
        TileLayer tileLayer("", Group<Rect2D>(), bounds, tileSize, m_TileLayerZPos);

        return tileLayer;
    }


    TileLayer DocumentFactory::createBackgroundLayer(const Bounds &bounds, float tileSize) const
    {
        TileLayer backgroundLayer("", Group<Rect2D>(), bounds, tileSize, m_BackgroundZPos);

        Checkerboard checkerboard;
        checkerboard.create(backgroundLayer);

        return backgroundLayer;
    }

    TileLayer DocumentFactory::createTempLayer(const Bounds &bounds, float tileSize) const
    {
        return TileLayer("", Group<Rect2D>(), bounds, tileSize, m_TileLayerZPos, true);
    }

    TileLayer DocumentFactory::createToolLayer(const Bounds &bounds, float tileSize) const
    {
        return TileLayer("", Group<Rect2D>(), bounds, tileSize, m_ToolLayerZPos, true);
    }

    TileLayer DocumentFactory::createCursorLayer(const Bounds &bounds, float tileSize) const
    {
        return TileLayer("", Group<Rect2D>(), bounds, tileSize, m_CursorLayerZPos, true);
    }

    void DocumentFactory::createFrame(Document &document)
    {
        Frame frame(0);

        Frame &activeFrame = get_active_tile_canvas(document).getFrame(0);

        std::vector<TileLayer> layers;

        for (TileLayer &layer : activeFrame.getLayers())
        {
            layers.push_back(layer);
        }

        get_active_tile_canvas(document).addFrame(layers);
    }

    Canvas3d DocumentFactory::createDrawing3d(const Bounds &bounds) const
    {
        Canvas3d drawing =
            Canvas3d(UuidGenerator::getInstance().generate(), bounds, *m_RendererProvider->createRenderer2D());

        drawing.getGroup().add(Rect2D(bounds.getBottomLeft().x,
                                      bounds.getBottomLeft().y,
                                      bounds.getWidth(),
                                      bounds.getHeight(),
                                      COLOR_RED));

        drawing.getGroup().add(CylinderBuilder()
                                   .setHeight(10)
                                   .setDiameterTop(4)
                                   .setDiameterBottom(8)
                                   .setTessellation(9)
                                   .setColor(COLOR_RED)
                                   .build());

        drawing.getGroup().add(BoxBuilder()
                                   .setWidth(10)
                                   .setHeight(5)
                                   .setDepth(5)
                                   .setColor(COLOR_BLUE)
                                   .setFaceColor(Box::Face::top, COLOR_GREEN)
                                   .setFaceColor(Box::Face::left, COLOR_RED)
                                   .build());

        return drawing;
    }


    TileCanvas DocumentFactory::createDrawing(const CreateDrawingProps &props) const
    {
        const Bounds &bounds = props.bounds;
        float backgroundLayerTileSize = props.backgroundLayerTileSize;
        float tileSize = props.tileSize;
        size_t layerCount = props.layerCount;
        bool hasCheckerBoard = props.hasCheckerBoard;

        TileCanvas drawing(UuidGenerator::getInstance().generate(),
                           bounds,
                           *m_RendererProvider->createRenderer2D(),
                           createBackgroundLayer(bounds, backgroundLayerTileSize),
                           createTempLayer(bounds, tileSize),
                           createToolLayer(bounds, tileSize),
                           createCursorLayer(bounds, tileSize));

        if (layerCount > 0)
        {
            std::vector<TileLayer> layers;

            for (size_t i = 0; i < layerCount; i++)
            {
                TileLayer layer("layer" + std::to_string(i + 1), Group<Rect2D>(), bounds, tileSize, m_TileLayerZPos);

                layers.push_back(layer);
            }

            drawing.addFrame(layers);
        }

        if (hasCheckerBoard)
        {
            m_Checkerboard.create(drawing.getBackgroundLayer());
        }

        return drawing;
    }

    Document DocumentFactory::createEmptyDocument() const
    {
        float pixelCount = 32.0f;
        Bounds drawingBounds(-pixelCount / 2.0f, -pixelCount / 2.0f, pixelCount / 2.0f, pixelCount / 2.0f);

#ifdef INIT_WITH_3D_CANVAS
        ArcRotateCamera camera(BoundsInt(0, 0, m_Window->getWidth(), m_Window->getHeight()));
#else
        Camera2d camera(BoundsInt(0, 0, m_Window->getWidth(), m_Window->getHeight()));
#endif
        Canvas2d documentCanvas(UuidGenerator::getInstance().generate(),
                                drawingBounds,
                                *m_RendererProvider->createRenderer2D());

        documentCanvas.setCamera(camera);

        Document document(drawingBounds, documentCanvas, std::make_shared<DocumentHistory>());

        return document;
    }

    Document DocumentFactory::createDocument()
    {
        float pixelCount = 32.0f;

        Document document = createEmptyDocument();

        TileCanvas canvas = createDrawing(
            CreateDrawingProps(Bounds::createWithPositions(-16.0f, -pixelCount / 2.0f, 16.0f, pixelCount / 2.0f)));

        Vec2Int minWindow = document.getBackgroundCanvas().getCamera()->worldToScreenPos(canvas.getBounds().minX,
                                                                                         canvas.getBounds().minY);
        Vec2Int maxWindow = document.getBackgroundCanvas().getCamera()->worldToScreenPos(canvas.getBounds().maxX,
                                                                                         canvas.getBounds().maxY);
#ifdef INIT_WITH_3D_CANVAS
        Canvas3d canvas3d = createDrawing3d(Bounds(18.0, -5.0, 28.0, 5.0));
        document.addCanvas(canvas3d);
#else
        document.addCanvas(canvas);
#endif


        return document;
    }
} // namespace editing
} // namespace spright
