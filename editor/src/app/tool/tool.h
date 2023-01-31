#pragma once
#include <string>
#include "pointer_info.h"

namespace spright { namespace tool {
	using namespace std;

	class Tool {
	private:
		string name;
	public:
		Tool(string name);
		inline virtual void pointerDown(PointerInfo& pointerInfo) {}
		inline virtual void pointerUp(PointerInfo& pointerInfo) {}
		inline virtual void pointerMove(PointerInfo& pointerInfo) {}
		inline virtual void scroll(PointerInfo& pointerInfo) {}
		inline virtual void activate() {}
		inline virtual void deactivate() {}
	
		inline string getName() const {
			return this->name;
		}
	};
}}