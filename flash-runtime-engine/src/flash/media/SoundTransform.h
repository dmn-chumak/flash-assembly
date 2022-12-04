#ifndef FLASH_SOUND_SOUND_TRANSFORM_H
#define FLASH_SOUND_SOUND_TRANSFORM_H

#include <flash/core/Core.h>

namespace flash::media {
    class SoundTransform : public Object {
        public:
            float volume;
            float pan;

        public:
            SoundTransform(const float volume = 1, const float pan = 0);
           ~SoundTransform() override;
    };
}

#endif
