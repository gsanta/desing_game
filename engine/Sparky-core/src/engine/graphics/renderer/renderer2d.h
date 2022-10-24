#pragma once

//#include "renderable2d.h"
#include <GL/glew.h>
#include "../../maths/mat4.h"
#include <vector>
#include "vertex_data.h"

namespace my_app_engine { namespace graphics {
	class Renderable2D;

	class Renderer2D {
	protected:
		std::vector<my_app_engine::maths::Mat4> m_TransformationStack;
		const my_app_engine::maths::Mat4* m_TransformationBack;

		GLsizei m_IndexCount = 0;

		Renderer2D() {
			m_TransformationStack.push_back(my_app_engine::maths::Mat4::identity());
			m_TransformationBack = &m_TransformationStack.back();
		}
	public:
		void push(const my_app_engine::maths::Mat4& matrix, bool override = false) {
			if (override) {
				m_TransformationStack.push_back(matrix);
			}
			else {
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
			}
			m_TransformationBack = &m_TransformationStack.back();
		}

		void pop() {
			if (m_TransformationStack.size() > 1) {
				m_TransformationStack.pop_back();
			}

			m_TransformationBack = &m_TransformationStack.back();


			// TODO: Add to log!
		}

		const my_app_engine::maths::Mat4* getTransformation() {
			return m_TransformationBack;
		}


		inline GLsizei getIndexCount() {
			return m_IndexCount;
		}

		inline void setIndexCount(GLsizei indexCount) {
			m_IndexCount = indexCount;
		}

		virtual void flush() = 0;
		virtual void begin() {}
		virtual void end() {}
		virtual VertexData*& getBuffer() = 0;
	};
} }