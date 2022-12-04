#include <flash/runtime/Sound.h>
#include <flash/media/Sound.h>
#include <flash/network/URLLoaderDataFormat.h>
#include <flash/events/IOErrorEvent.h>

using flash::network::URLLoader;
using flash::network::URLRequest;
using flash::network::URLLoaderDataFormat;
using flash::events::Event;
using flash::events::IOErrorEvent;
using flash::utils::ByteArray;

namespace flash::media {
    const sInt Sound::INTERNAL_COMPLETE_EVENT   = 0;
    const sInt Sound::INTERNAL_ERROR_EVENT      = 1;

    Sound::Sound(const Pointer<URLRequest> &request) {
        _soundID = runtime::Sound::createSound(
            (void *)Sound::globalEventCallback,
            this
        );

        _source = nullptr;
        _loader = nullptr;

        load(request);
    }

    Sound::~Sound() {
        runtime::Sound::deleteSound(
            _soundID
        );
    }

    void Sound::load(const Pointer<URLRequest> &request) {
        if (_source != nullptr || _loader != nullptr) {
            return;
        }

        if (request != nullptr) {
            _loader = new network::URLLoader();
            _loader->dataFormat = URLLoaderDataFormat::BINARY;
            _loader->addEventListener(Event::COMPLETE, Bindings::bind(&Sound::soundLoadedHandler, this));
            _loader->load(request);
        }
    }

    void Sound::loadCompressedDataFromByteArray(const Pointer<ByteArray> &source) {
        if (_source != nullptr || _loader != nullptr) {
            return;
        }

        if (source != nullptr) {
            _source = source;

            // TODO: manually increased ref counter while binding
            ++_refCount;

            runtime::Sound::bindSoundSource(
                _soundID,
                _source->source(),
                _source->length()
            );
        }
    }

    Pointer<SoundChannel> Sound::play(uInt start, uInt loops, const Pointer<SoundTransform> &transform) {
        if (_source != nullptr) {
            return new SoundChannel(this, start, loops, transform);
        } else {
            return nullptr;
        }
    }

    void Sound::globalEventCallback(Sound *sound, sInt event, heap first, heap second) {
        sound->localEventCallback(event, first, second);
    }

    void Sound::localEventCallback(sInt event, heap first, heap second) {
        switch (event) {
            case INTERNAL_COMPLETE_EVENT: {
                dispatchEvent(new Event(Event::COMPLETE));

                // TODO: manually decreased ref counter after binding
                if (--_refCount == 0) {
                    delete this;
                }

                break;
            }

            case INTERNAL_ERROR_EVENT: {
                dispatchEvent(new IOErrorEvent(IOErrorEvent::IO_ERROR));

                // TODO: manually decreased ref counter after binding
                if (--_refCount == 0) {
                    delete this;
                }

                break;
            }
        }
    }

    void Sound::soundLoadedHandler(const Pointer<Event> &event) {
        _source = (ByteArray *)_loader->data.object();
        _loader = nullptr;

        // TODO: manually increased ref counter while binding
        ++_refCount;

        runtime::Sound::bindSoundSource(
            _soundID,
            _source->source(),
            _source->length()
        );
    }
}
