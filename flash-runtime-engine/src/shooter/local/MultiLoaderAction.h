#ifndef SHOOTER_LOCAL_MULTI_LOADER_ACTION_H
#define SHOOTER_LOCAL_MULTI_LOADER_ACTION_H

#include <flash/core/Core.h>

namespace shooter::local {
    class MultiLoaderAction : public Object {
        public:
            bool binary;
            String path;
            MultiLoaderAction();
            MultiLoaderAction *MultiLoaderActionConstruct(String path, bool binary = true);
            virtual ~MultiLoaderAction() override;
    };
}

#endif

