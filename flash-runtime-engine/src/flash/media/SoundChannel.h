#ifndef FLASH_MEDIA_SOUND_CHANNEL_H
#define FLASH_MEDIA_SOUND_CHANNEL_H

namespace flash::media {
    class SoundChannel;
}

#include <flash/events/EventDispatcher.h>
#include <flash/media/Sound.h>
#include <flash/media/SoundTransform.h>
#include <flash/core/Core.h>

namespace flash::media {
    class SoundChannel : public events::EventDispatcher {
        private:
            static const sInt INTERNAL_COMPLETE_EVENT;

        private:
            Pointer<Sound> _sound;
            Pointer<SoundTransform> _transform;
            float _position;
            sInt _channelID;

        private:
            static void globalEventCallback(SoundChannel *channel, sInt event = 0, heap first = 0, heap second = 0);
            void localEventCallback(sInt event = 0, heap first = 0, heap second = 0);

        public:
            SoundChannel(const Pointer<Sound> &sound, uInt start, uInt loops, const Pointer<SoundTransform> &transform);
           ~SoundChannel() override;

        public:
            Pointer<SoundTransform> getSoundTransform();
            void setSoundTransform(const Pointer<SoundTransform> &transform);
            float getPosition();
            void play();
            void stop();
    };
}

#endif
