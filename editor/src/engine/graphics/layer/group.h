#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <algorithm>
#include "../renderable/renderable2d.h"
#include "../renderer/renderer2d.h"
#include "../camera/camera.h"
#include "dimensions.h"

namespace spright { namespace engine {

	class Group
	{
	protected:
		std::vector <Renderable2D*> m_Renderables;
		Renderer2D *m_Renderer;

	public:
		Group(Renderer2D *renderer);
		virtual ~Group();
		virtual void add(Renderable2D *renderable);
		virtual void render(Camera* camera);
		virtual void clear();
		virtual void remove(Renderable2D* renderable);

		inline std::vector<Renderable2D*>& getRenderables() {
			return m_Renderables;
		}
	};
}}