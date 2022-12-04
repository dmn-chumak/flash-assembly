#include <shooter/Main.h>
#include <flash/utils/Math.h>
#include <shooter/render/DisplayObjectRegion.h>

namespace shooter {
    void Main::loaderCompleteHandler(const Pointer<Event> &_event_) {
        Pointer<MultiLoaderEvent> event = (MultiLoaderEvent *)_event_.object();

        Pointer<BitmapData> bitmap = nullptr;
        Pointer<GpuTexture> region = nullptr;
        Pointer<Animation> animation = nullptr;
        Pointer<Skeleton> skeleton = nullptr;
        Pointer<SkeletonBody> body = nullptr;
        sInt i = 0;
        Pointer<SkeletonBone> bone = nullptr;
        bitmap = event->images->obtainAt(uInt(0));
        region = _renderer->createTexture(bitmap, event->bytes->obtainAt(uInt(0)));



        Pointer<shooter::render::DisplayObjectRegion> reg = new shooter::render::DisplayObjectRegion();

        reg->regionSetter(region->obtainRegion("earth_1"));
        reg->scaleXSetter(10);
        reg->scaleYSetter(10);
        _renderer->appendChild(reg);


        animation = AnimationBuilder::create(event->bytes->obtainAt(uInt(1)));
        skeleton = SkeletonBuilder::create(event->bytes->obtainAt(uInt(2)));
        body = (new SkeletonBody())->SkeletonBodyConstruct();
        for (i = sInt(0); i < skeleton->parts->length(); i++) {
            bone = (new SkeletonBone())->SkeletonBoneConstruct();
            bone->regionSetter(region->obtainRegion(skeleton->parts->obtainAt(i)->texture));
            body->appendBone(skeleton->parts->obtainAt(i)->name, bone);
        }
        body->animationSetter(animation);
        body->play();
        body->xSetter(Double(300));
        body->ySetter(Double(100));
        _renderer->appendChild(body);

        animation = AnimationBuilder::create(event->bytes->obtainAt(uInt(3)));
        skeleton = SkeletonBuilder::create(event->bytes->obtainAt(uInt(4)));

        body = (new SkeletonBody())->SkeletonBodyConstruct();
        for (i = sInt(0); i < skeleton->parts->length(); i++) {
            bone = (new SkeletonBone())->SkeletonBoneConstruct();
            bone->regionSetter(region->obtainRegion(skeleton->parts->obtainAt(i)->texture));
            body->appendBone(skeleton->parts->obtainAt(i)->name, bone);
        }
        body->animationSetter(animation);
        body->play();
        body->xSetter(Double(500));
        body->ySetter(Double(100));
        body->rotationSetter(45.0 / 180.0 * flash::utils::Math::PI);
        _renderer->appendChild(body);

        animation = AnimationBuilder::create(event->bytes->obtainAt(uInt(5)));
        skeleton = SkeletonBuilder::create(event->bytes->obtainAt(uInt(6)));

        body = (new SkeletonBody())->SkeletonBodyConstruct();
        for (i = sInt(0); i < skeleton->parts->length(); i++) {
            bone = (new SkeletonBone())->SkeletonBoneConstruct();
            bone->regionSetter(region->obtainRegion(skeleton->parts->obtainAt(i)->texture));
            body->appendBone(skeleton->parts->obtainAt(i)->name, bone);
        }
        body->animationSetter(animation);
        body->play();
        body->xSetter(Double(400));
        body->ySetter(Double(300));
        body->rotationSetter(-135.0 / 180.0 * flash::utils::Math::PI);
        _renderer->appendChild(body);

        _renderer->update(0);
        _renderer->present();

        _active = true;
    }

    Main::Main() {
        Pointer<Array<MultiLoaderAction>> actions = new Array<MultiLoaderAction>();

        actions->insertLast((new MultiLoaderAction)->MultiLoaderActionConstruct("./res/items.png", false));
        actions->insertLast((new MultiLoaderAction)->MultiLoaderActionConstruct("./res/items.bin"));
        actions->insertLast((new MultiLoaderAction)->MultiLoaderActionConstruct("./res/animation/human_attack.bin"));
        actions->insertLast((new MultiLoaderAction)->MultiLoaderActionConstruct("./res/skeleton/human.bin"));
        actions->insertLast((new MultiLoaderAction)->MultiLoaderActionConstruct("./res/animation/legs_walk.bin"));
        actions->insertLast((new MultiLoaderAction)->MultiLoaderActionConstruct("./res/skeleton/legs.bin"));
        actions->insertLast((new MultiLoaderAction)->MultiLoaderActionConstruct("./res/animation/zombie_walk.bin"));
        actions->insertLast((new MultiLoaderAction)->MultiLoaderActionConstruct("./res/skeleton/zombie.bin"));

        _renderer = (new GpuRenderer())->GpuRendererConstruct();
        _renderer->requestContext(uInt(800), uInt(600));
        _loader = (new MultiLoader())->MultiLoaderConstruct();
        _loader->addEventListener(Event::COMPLETE, Bindings::bind(&Main::loaderCompleteHandler, this));
        _loader->load(actions);

        _active = false;
    }

    void Main::render() {
        if (_active) {
            _renderer->update(0);
            _renderer->present();
        }
    }

}

