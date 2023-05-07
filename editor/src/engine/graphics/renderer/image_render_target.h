#pragma once
#include "../../system/window/window.h"
#include "../renderable/bounds_int.h"
#include "render_target.h"

#include <GL/glew.h>
#include <iostream>

namespace spright
{
namespace engine
{

    class ImageRenderTarget : public RenderTarget
    {
    public:
        ImageRenderTarget(Window *window);

        // NOTE: it has to be called before enable to set the bounds to render
        void setImageBounds(BoundsInt);

        void enable();

        void disable();

    private:
        void init();

    private:
        unsigned int m_FrameBuffer;

        unsigned int m_Texture;

        Window *m_Window;

        BoundsInt m_ImageBounds;
    };
} // namespace engine
} // namespace spright