#pragma once
#include "../../../maths/vec2.h"

namespace spright { namespace engine {
	using namespace spright::maths;

	class Bounds {

	public:
		float minX;
		float maxX;
		float minY;
		float maxY;

		Bounds(float bottomLeftX, float bottomLeftY, float width, float height);
		Bounds();

		friend bool operator==(const Bounds&, const Bounds&);
		friend bool operator!=(const Bounds&, const Bounds&);

		Vec2 getCenter() const;

		float getWidth() const;
		float getHeight() const;
	};
}}