#include <shooter/local/MultiLoaderAction.h>

namespace shooter::local {
    MultiLoaderAction::MultiLoaderAction() {
        binary = false;
        path = nullptr;
    }

    MultiLoaderAction *MultiLoaderAction::MultiLoaderActionConstruct(String path, bool binary) {
        this->binary = binary;
        this->path = path;
        return this;
    }

    MultiLoaderAction::~MultiLoaderAction() {
    }
}

