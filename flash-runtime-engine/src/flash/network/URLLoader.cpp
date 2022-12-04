#include <flash/network/URLLoader.h>
#include <flash/network/URLLoaderDataFormat.h>
#include <flash/runtime/Network.h>
#include <flash/utils/ByteArray.h>
#include <flash/events/HTTPStatusEvent.h>
#include <flash/events/IOErrorEvent.h>
#include <flash/events/ProgressEvent.h>
#include <flash/events/SecurityErrorEvent.h>

using flash::events::Event;
using flash::events::HTTPStatusEvent;
using flash::events::IOErrorEvent;
using flash::events::ProgressEvent;
using flash::events::SecurityErrorEvent;
using flash::utils::ByteArray;

namespace flash::network {
    const sInt URLLoader::INTERNAL_HTTP_STATUS_EVENT    = 0;
    const sInt URLLoader::INTERNAL_OPEN_EVENT           = 1;
    const sInt URLLoader::INTERNAL_IO_ERROR_EVENT       = 2;
    const sInt URLLoader::INTERNAL_COMPLETE_EVENT       = 3;
    const sInt URLLoader::INTERNAL_PROGRESS_EVENT       = 4;
    const sInt URLLoader::INTERNAL_SECURITY_ERROR_EVENT = 5;
    
    URLLoader::URLLoader(const Pointer<URLRequest> &request) {
        _loaderID = runtime::Network::createLoader(
            (void *)URLLoader::globalEventCallback,
            this
        );

        dataFormat = URLLoaderDataFormat::TEXT;
        bytesLoaded = 0;
        bytesTotal = 0;
        _isLoading = false;

        load(request);
    }

    URLLoader::~URLLoader() {
        runtime::Network::deleteLoader(
            _loaderID
        );
    }

    void URLLoader::load(const Pointer<URLRequest> &request) {
        if (_isLoading == false && request != nullptr) {
            _isLoading = true;
            _request = request;

            bytesLoaded = 0;
            bytesTotal = 0;

            // TODO: manually increased ref counter while loading
            ++_refCount;

            runtime::Network::startLoadingSource(
                _loaderID,
                _request->url.source(),
                _request->url.length()
            );
        }
    }

    void URLLoader::close() {
        if (_isLoading) {
            runtime::Network::stopLoadingSource(_loaderID);
            _isLoading = false;

            // TODO: manually decreased ref counter after loading
            if (--_refCount == 0) {
                delete this;
            }
        }
    }

    void URLLoader::globalEventCallback(URLLoader *loader, sInt event, heap first, heap second) {
        loader->localEventCallback(event, first, second);
    }

    void URLLoader::localEventCallback(sInt event, heap first, heap second) {
        switch (event) {
            case INTERNAL_HTTP_STATUS_EVENT: {
                dispatchEvent(new HTTPStatusEvent(HTTPStatusEvent::HTTP_STATUS, false, false, first, second != 0));
                break;
            }

            case INTERNAL_OPEN_EVENT: {
                dispatchEvent(new Event(Event::OPEN));
                break;
            }

            case INTERNAL_IO_ERROR_EVENT: {
                _isLoading = false;

                dispatchEvent(new IOErrorEvent(IOErrorEvent::IO_ERROR));

                // TODO: manually decreased ref counter after loading
                if (--_refCount == 0) {
                    delete this;
                }

                break;
            }

            case INTERNAL_COMPLETE_EVENT: {
                _isLoading = false;

                RawArrPtr<sByte> buffer = new sByte[bytesTotal];
                runtime::Network::bindLoadedData(_loaderID, buffer.get(), bytesTotal);

                if (dataFormat == URLLoaderDataFormat::BINARY) {
                    data = new ByteArray(Utils::move(buffer), bytesTotal);
                } else if (dataFormat == URLLoaderDataFormat::TEXT) {
                    data = new String(buffer.get(), bytesTotal);
                } else {
                    // TODO: implement variables format
                }

                dispatchEvent(new Event(Event::COMPLETE));

                // TODO: manually decreased ref counter after loading
                if (--_refCount == 0) {
                    delete this;
                }

                break;
            }

            case INTERNAL_PROGRESS_EVENT: {
                bytesLoaded = first;
                bytesTotal = second;
                dispatchEvent(new ProgressEvent(ProgressEvent::PROGRESS, false, false, first, second));
                break;
            }

            case INTERNAL_SECURITY_ERROR_EVENT: {
                _isLoading = false;

                dispatchEvent(new SecurityErrorEvent(SecurityErrorEvent::SECURITY_ERROR));

                // TODO: manually decreased ref counter after loading
                if (--_refCount == 0) {
                    delete this;
                }

                break;
            }
        }
    }
}
