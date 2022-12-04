#include <shooter/local/MultiLoader.h>
#include <flash/system/Console.h>

using namespace flash::system;

namespace shooter::local {
    void MultiLoader::imgLoaderCompleteHandler(const Pointer<Event> &event) {
        Pointer<ByteArray> bytes = (ByteArray *)_imgLoader->data.object();

        Pointer<BitmapData> bitmapData = new BitmapData(512, 256);
        bitmapData->bytes = bytes;

        _loadedImages->insertLast(bitmapData);
        loadNext();
    }

    void MultiLoader::urlLoaderCompleteHandler(const Pointer<Event> &event) {
        _loadedBytes->insertLast((ByteArray *)_urlLoader->data.object());
        loadNext();
    }

    void MultiLoader::loadNext() {
        Pointer<MultiLoaderAction> action = nullptr;
        Pointer<URLRequest> request = nullptr;

        if (_actions->length() > 0) {
            action = _actions->removeFirst();
            request = new URLRequest(action->path);

            Console::logMessage("loading:" + action->path);

            if (action->binary) {
                _urlLoader = new URLLoader();
                _urlLoader->addEventListener(Event::COMPLETE, Bindings::bind(&MultiLoader::urlLoaderCompleteHandler, this));
                _urlLoader->dataFormat = URLLoaderDataFormat::BINARY;
                _urlLoader->load(request);
            } else {
                _imgLoader->load(request);
            }
        } else {
            dispatchEvent((new MultiLoaderEvent())->MultiLoaderEventConstruct(Event::COMPLETE, _loadedImages, _loadedBytes));
        }
    }

    MultiLoader::MultiLoader() {
        _loadedImages = nullptr;
        _loadedBytes = nullptr;
        _actions = nullptr;
        _urlLoader = nullptr;
        _imgLoader = nullptr;
    }

    MultiLoader *MultiLoader::MultiLoaderConstruct() {
        _loadedImages = new Array<BitmapData>();
        _loadedBytes = new Array<ByteArray>();

        _imgLoader = new URLLoader();
        _imgLoader->dataFormat = URLLoaderDataFormat::BINARY;
        _imgLoader->addEventListener(Event::COMPLETE, Bindings::bind(&MultiLoader::imgLoaderCompleteHandler, this));

        _urlLoader = new URLLoader();
        _urlLoader->addEventListener(Event::COMPLETE, Bindings::bind(&MultiLoader::urlLoaderCompleteHandler, this));
        _urlLoader->dataFormat = URLLoaderDataFormat::BINARY;

        return this;
    }

    void MultiLoader::load(Pointer<Array<MultiLoaderAction>> actions) {
        _actions = actions;
        loadNext();
    }

    MultiLoader::~MultiLoader() {
    }
}

