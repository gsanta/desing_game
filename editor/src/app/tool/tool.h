#pragma once
#include <string>
#include "pointer_info.h"
#include "common/document_info.h"

namespace spright { namespace editor {
	using namespace std;

	class Tool {
	private:
		string name;
	public:
		Tool(string name);
		inline virtual void pointerDown(PointerInfo& pointerInfo, DocumentInfo& documentInfo) {}
		inline virtual void pointerUp(PointerInfo& pointerInfo, DocumentInfo& documentInfo) {}
		inline virtual void pointerMove(PointerInfo& pointerInfo, DocumentInfo& documentInfo) {}
		inline virtual void scroll(PointerInfo& pointerInfo) {}
		inline virtual void activate() {}
		inline virtual void deactivate(DocumentInfo& documentInfo) {}
		inline virtual void setOptions(std::string json) {}
		inline virtual std::string getOptions() { return "{}"; }
		inline virtual std::string getData() { return ""; }

		inline string getName() const {
			return this->name;
		}
	};
}}
