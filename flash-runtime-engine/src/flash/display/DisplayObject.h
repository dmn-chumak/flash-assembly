#ifndef FLASH_DISPLAY_DISPLAY_OBJECT_H
#define FLASH_DISPLAY_DISPLAY_OBJECT_H

#include <flash/display/IBitmapDrawable.h>
#include <flash/events/EventDispatcher.h>
#include <flash/core/Core.h>

namespace flash::display {
    class DisplayObject : public IBitmapDrawable, public events::EventDispatcher {
        protected:
            Pointer<DisplayObject> _parent;
            Pointer<DisplayObject> _root;
            String _name;
            double _alpha;
            double _rotation;
            double _scaleX;
            double _scaleY;
            bool _visible;
            double _x;
            double _y;

        public:
            DisplayObject();
           ~DisplayObject() override;
    };
}

#endif
