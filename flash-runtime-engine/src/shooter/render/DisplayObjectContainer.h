#ifndef SHOOTER_RENDER_DISPLAY_OBJECT_CONTAINER_H
#define SHOOTER_RENDER_DISPLAY_OBJECT_CONTAINER_H

#include <flash/core/Core.h>
#include <shooter/render/DisplayObject.h>

namespace shooter::render {
    class DisplayObjectContainer : public DisplayObject {
        private:
        protected:
            Pointer<Array<DisplayObject>> _children;
        public:
            DisplayObjectContainer();
            DisplayObjectContainer *DisplayObjectContainerConstruct();
            void render(IRender *renderer) override;
            virtual void update(double delta) override;
            void appendChild(Pointer<DisplayObject> object);
            void removeChild(Pointer<DisplayObject> object);
            void removeAllChildren();
            virtual ~DisplayObjectContainer() override;
    };
}

#endif

