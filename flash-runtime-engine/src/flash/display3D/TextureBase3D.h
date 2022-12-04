#ifndef FLASH_DISPLAY_3D_TEXTURE_BASE_3D_H
#define FLASH_DISPLAY_3D_TEXTURE_BASE_3D_H

#include <flash/events/EventDispatcher.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class TextureBase3D : public events::EventDispatcher {
        public:
            TextureBase3D();
           ~TextureBase3D() override;
    };
}

#endif
