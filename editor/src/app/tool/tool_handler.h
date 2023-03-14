#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "tool.h"
#include "brush_tool.h"
#include "rectangle_tool.h"
#include "eraser_tool/eraser_tool.h"
#include "../service/services.h"
#include "../../engine/system/window/window.h"
#include "../../engine/system/window/input_listener.h"
#include "../../engine/graphics/layer/dimensions.h"
#include "../../engine/graphics/camera/camera.h"
#include "../../engine/graphics/camera/ortho_projection_info.h"
#include "../editor_config.h"
#include "../service/services.h"
#include "../service/io/image_export.h"

namespace spright { namespace editor {

	using namespace std;
	using namespace ::spright::engine;

	class ToolHandler : public InputListener {
	private:
		Window* m_Window;
		vector<Tool*> m_Tools;
		vector<Tool*>* m_ActiveTools;
		Tool* m_SelectedTool = nullptr;
		PointerInfo m_pointerInfo;
		Services* m_Services;
		DocumentStore* m_DocumentStore;
		Camera* m_Camera;
		ImageExport* m_ImageExport;
	public:
		ToolHandler();
		ToolHandler(Window* window, DocumentStore* documentStore, Services* services, Camera* camera, ImageExport* imageExport);
		~ToolHandler();

		ToolHandler& operator=(const ToolHandler& toolHandler);

		// TODO: destructor
		virtual void onMouseUp(bool buttons[3]) override;
		virtual void onMouseDown(bool buttons[3]) override;
		virtual void onMouseMove(double x, double y) override;
		virtual void onScroll(double x, double y) override;
		virtual void onKeyChange(int key, bool isPressed) override;

		void addTool(Tool* tool);

		Tool* getTool(string name) const;

		vector<Colorable*> getColorableTools();

		inline vector<Tool*>* getActiveTool() const {
			return m_ActiveTools;
		}

		Tool* getSelectedTool();
		void setSelectedTool(string name);

		inline void addActiveTool(string name) {
			m_ActiveTools->push_back(getTool(name));
		}

		inline void removeActiveTool(string name) {
			auto it = find(m_ActiveTools->begin(), m_ActiveTools->end(), getTool(name));

			if (it != m_ActiveTools->end()) {
				m_ActiveTools->erase(it);
			}
		}

		bool isActiveTool(string name);
	};
} }
