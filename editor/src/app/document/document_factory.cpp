#include "document_factory.h"

namespace spright { namespace editor {

	DocumentFactory::DocumentFactory(Container* windowContainer, EventEmitter* eventEmitter) : m_WindowContainer(windowContainer), m_EventEmitter(eventEmitter)
	{
	}

	void DocumentFactory::createUserLayer(Drawing& drawing, std::string name)
	{
#ifdef SPARKY_EMSCRIPTEN
		GLShader shaderUnlit("resources/shaders/basic.es3.vert", "resources/shaders/basic_unlit.es3.frag");
#else
		GLShader shaderUnlit("shaders/basic.vert", "shaders/unlit.frag");
#endif
		TileLayer layer(name, Group<Rect2D>(new GLRenderer2D(shaderUnlit)), drawing.getBounds());

		for (Frame& frame : drawing.getFrameStore().getFrames()) {
			frame.addLayer(std::move(layer));
		}
	}

	void DocumentFactory::createFrame(Document* document) {
		FrameImpl frame(0);

		Frame& activeFrame = document->getFrameStore().getActiveFrame();

		for (TileLayer& layer : activeFrame.getLayers()) {
			frame.addLayer(layer);
		}

		document->getFrameStore().addFrame(std::move(frame));
	}

	Drawing DocumentFactory::createDrawing(Bounds bounds, bool checkerboard) {
#ifdef SPARKY_EMSCRIPTEN
		GLShader shaderUnlit("resources/shaders/basic.es3.vert", "resources/shaders/basic_unlit.es3.frag");
#else
		GLShader shaderUnlit("shaders/basic.vert", "shaders/unlit.frag");
#endif
		Drawing drawing(bounds, m_EventEmitter);

		TileLayer tempLayer("", Group<Rect2D>(new GLRenderer2D(shaderUnlit)), bounds);
		TileLayer backgroundLayer("", Group<Rect2D>(new GLRenderer2D(shaderUnlit)), bounds, 2.0f);

		FrameImpl frame(0);

		drawing.getFrameStore().addFrame(frame);
		drawing.getActiveFrame().addBackgroundLayer(backgroundLayer);
		drawing.getActiveFrame().addForegroundLayer(tempLayer);

		createUserLayer(drawing, "layer1");
		createUserLayer(drawing, "layer2");

		if (checkerboard) {
			m_Checkerboard.create(drawing.getBackgroundLayer());
		}

		return drawing;
	}

	Document* DocumentFactory::createDocument()
	{
		float pixelCount = 32.0f;
		Bounds documentBounds = Bounds::createWithPositions(-pixelCount / 2.0f, pixelCount / 2.0f, -pixelCount / 2.0f, pixelCount / 2.0f);

		Camera camera(m_WindowContainer->getBounds().getWidth(), m_WindowContainer->getBounds().getHeight(), documentBounds, -1.0f, 1.0f);

		
		createDrawing(Bounds::createWithPositions(2.0f, pixelCount / 5.0f, -pixelCount / 2.0f, pixelCount / 2.0f));

		Document *document = new Document(documentBounds, camera, createDrawing(documentBounds, false));

		document->addDrawing(createDrawing(Bounds::createWithPositions(-16.0f, -10.0f, -pixelCount / 2.0f, pixelCount / 2.0f)));
		document->addDrawing(createDrawing(Bounds::createWithPositions(2.0f, pixelCount / 5.0f, -pixelCount / 2.0f, pixelCount / 2.0f)));

		return document;
	}
}}
