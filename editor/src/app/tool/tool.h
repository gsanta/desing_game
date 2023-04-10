#pragma once
#include <string>
#include "pointer_info.h"
#include "../document/drawing.h"

namespace spright { namespace editor {
	using namespace std;

	class Tool {
	private:
		string name;
	public:
		Tool(string name);
		inline virtual void pointerDown(PointerInfo& pointerInfo, Drawing* activeDrawing) {}
		inline virtual void pointerUp(PointerInfo& pointerInfo, Drawing* activeDrawing) {}
		inline virtual void pointerMove(PointerInfo& pointerInfo, Drawing* activeDrawing) {}
		inline virtual void scroll(PointerInfo& pointerInfo) {}
		inline virtual void activate() {}
		inline virtual void deactivate() {}
		inline virtual void setOptions(std::string json) {}
		inline virtual std::string getOptions() { return "{}"; }
		inline virtual std::string getData() { return ""; }

		inline string getName() const {
			return this->name;
		}
	};
}}
