#ifndef FLASH_MEDIA_SOUND_H
#define FLASH_MEDIA_SOUND_H

namespace flash::media {
    class Sound;
}

#include <flash/events/EventDispatcher.h>
#include <flash/network/URLLoader.h>
#include <flash/network/URLRequest.h>
#include <flash/media/SoundTransform.h>
#include <flash/media/SoundChannel.h>
#include <flash/utils/ByteArray.h>
#include <flash/core/Core.h>

namespace flash::media {
    class Sound : public events::EventDispatcher {
        private:
            static const sInt INTERNAL_COMPLETE_EVENT;
            static const sInt INTERNAL_ERROR_EVENT;

        private:
            Pointer<utils::ByteArray> _source;
            Pointer<network::URLLoader> _loader;
            sInt _soundID;

        private:
            static void globalEventCallback(Sound *sound, sInt event = 0, heap first = 0, heap second = 0);
            void localEventCallback(sInt event = 0, heap first = 0, heap second = 0);
            void soundLoadedHandler(const Pointer<events::Event> &event);

        public:
            Sound(const Pointer<network::URLRequest> &request = nullptr);
           ~Sound() override;

        public:
            void load(const Pointer<network::URLRequest> &request);
            void loadCompressedDataFromByteArray(const Pointer<utils::ByteArray> &source);
            Pointer<SoundChannel> play(uInt start = 0, uInt loops = 0, const Pointer<SoundTransform> &transform = nullptr);

        private:
            friend class SoundChannel;
    };
}

#endif
