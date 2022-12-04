#include <flash/runtime/Sound.h>
#include <flash/media/SoundChannel.h>

using flash::events::Event;

namespace flash::media {
    const sInt SoundChannel::INTERNAL_COMPLETE_EVENT = 0;

    SoundChannel::SoundChannel(const Pointer<Sound> &sound, uInt start, uInt loops, const Pointer<SoundTransform> &transform) {
        _channelID = runtime::Sound::createSoundChannel(
            sound->_soundID,
            (void *)SoundChannel::globalEventCallback,
            this
        );

        if (transform == nullptr) {
            _transform = new SoundTransform();
        } else {
            _transform = transform;
        }

        _sound = sound;
        _position = 0;

        play();
    }

    SoundChannel::~SoundChannel() {
        runtime::Sound::deleteSoundChannel(
            _channelID
        );
    }

    Pointer<SoundTransform> SoundChannel::getSoundTransform() {
        return _transform;
    }

    void SoundChannel::setSoundTransform(const Pointer<SoundTransform> &transform) {
        if (transform != nullptr) {
            _transform = transform;

            runtime::Sound::changeChannelTransform(
                _channelID,
                _transform->volume,
                _transform->pan
            );
        }
    }

    float SoundChannel::getPosition() {
        return _position;
    }

    void SoundChannel::play() {
        // TODO: manually increased ref counter while playing
        ++_refCount;

        runtime::Sound::playSoundChannel(_channelID, 0);
        runtime::Sound::changeChannelTransform(
            _channelID,
            _transform->volume,
            _transform->pan
        );
    }

    void SoundChannel::stop() {
        runtime::Sound::stopSoundChannel(_channelID);

        // TODO: manually decreased ref counter after playing
        if (--_refCount == 0) {
            delete this;
        }
    }

    void SoundChannel::globalEventCallback(SoundChannel *channel, sInt event, heap first, heap second) {
        channel->localEventCallback(event, first, second);
    }

    void SoundChannel::localEventCallback(sInt event, heap first, heap second) {
        switch (event) {
            case INTERNAL_COMPLETE_EVENT: {
                dispatchEvent(new Event(Event::SOUND_COMPLETE));

                // TODO: manually decreased ref counter after playing
                if (--_refCount == 0) {
                    delete this;
                }

                break;
            }
        }
    }
}
