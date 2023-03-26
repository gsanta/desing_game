#include "drawing.h"

namespace spright { namespace editor {

	Drawing::Drawing(Bounds bounds, Camera* camera, EventEmitter* eventEmitter) : Container(bounds), m_Camera(camera), m_EventEmitter(eventEmitter)
	{
		m_FramePlayer = std::make_unique<FramePlayer>(m_FrameStore, eventEmitter);
	}

	Drawing::~Drawing() {
		std::vector<Group<Rect2D>*>::iterator it;

		delete m_Camera;
	}

	FrameStore& Drawing::getFrameStore() {
		return m_FrameStore;
	}

	ActiveFrame& Drawing::getActiveFrame() {
		return m_FrameStore.getActiveFrame();
	}


	TileLayer& Drawing::getActiveLayer() {
		return getFrameStore().getActiveFrame().getActiveLayer();
	}


	std::string Drawing::getJson()
	{
		nlohmann::json json = m_FrameStore.getActiveFrame().getActiveLayer().getJson();

		return json.dump();
	}

	void Drawing::render()
	{
		for (TileLayer& layer : getActiveFrame().getBackgroundLayers()) {
			layer.render(m_Camera);
		}

		for (TileLayer& layer : getActiveFrame().getLayers()) {
			layer.render(m_Camera);
		}

		for (TileLayer& layer : getActiveFrame().getForegroundLayers()) {
			layer.render(m_Camera);
		}
	}

	FramePlayer& Drawing::getFramePlayer() {
		return *m_FramePlayer;
	}
}}
