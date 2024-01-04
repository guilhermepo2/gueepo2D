#pragma once
#include <gueepo2d.h>

//
// Target is a 2D buffer that can be drawn to.
// It holds a single texture that is drawn to
//
// Even though the inspiration for this has 5 textures, 4 for colors and 1 for depth/stencil
// I don't even know what is depth/stencil so let's keep it simple and change it as needed.
// https://github.com/NoelFB/blah/blob/master/include/blah_graphics.h
//

namespace gueepo {
    class Texture;

    class Target {
    public:
        static Target* Create(int _width, int _height);

        virtual uint32_t GetWidth();
        virtual uint32_t GetHeight();

        virtual Texture* GetTexture() = 0;
        virtual void Clear(gueepo::Color _color) = 0;
    };
}