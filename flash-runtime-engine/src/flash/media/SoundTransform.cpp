#include <flash/media/SoundTransform.h>

namespace flash::media {
    SoundTransform::SoundTransform(const float volume, const float pan)
    : volume(volume), pan(pan) {
        // empty
    }

    SoundTransform::~SoundTransform() {
        // empty
    }
}
