#include "./renderer2d.h"

namespace spright { namespace engine {

	void Renderer2D::push(const Mat4& matrix, bool override) {
		if (override) {
			m_TransformationStack.push_back(matrix);
		}
		else {
			m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
		}
		m_TransformationBack = &m_TransformationStack.back();
	}

	void Renderer2D::pop() {
		if (m_TransformationStack.size() > 1) {
			m_TransformationStack.pop_back();
		}

		m_TransformationBack = &m_TransformationStack.back();
	}

	const spright::maths::Mat4* Renderer2D::getTransformation() {
		return m_TransformationBack;
	}
}}