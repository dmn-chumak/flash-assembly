#ifndef SHOOTER_MAIN_H
#define SHOOTER_MAIN_H

#include <flash/display/BitmapData.h>
#include <flash/display/StageAlign.h>
#include <flash/display/StageQuality.h>
#include <flash/display/StageScaleMode.h>
#include <flash/events/Event.h>
#include <shooter/local/MultiLoader.h>
#include <shooter/local/MultiLoaderAction.h>
#include <shooter/local/MultiLoaderEvent.h>
#include <shooter/render/GpuRenderer.h>
#include <shooter/render/SkeletonBody.h>
#include <shooter/render/SkeletonBone.h>
#include <shooter/render/animation/Animation.h>
#include <shooter/render/animation/Skeleton.h>
#include <shooter/render/builder/AnimationBuilder.h>
#include <shooter/render/builder/SkeletonBuilder.h>
#include <shooter/render/common/GpuTexture.h>
#include <flash/core/Core.h>

using flash::display::BitmapData;
using flash::display::StageAlign;
using flash::display::StageQuality;
using flash::display::StageScaleMode;
using flash::events::Event;
using shooter::local::MultiLoader;
using shooter::local::MultiLoaderAction;
using shooter::local::MultiLoaderEvent;
using shooter::render::GpuRenderer;
using shooter::render::SkeletonBody;
using shooter::render::SkeletonBone;
using shooter::render::animation::Animation;
using shooter::render::animation::Skeleton;
using shooter::render::builder::AnimationBuilder;
using shooter::render::builder::SkeletonBuilder;
using shooter::render::common::GpuTexture;

namespace shooter {
    class Main {
        private:
            Pointer<GpuRenderer> _renderer;
            Pointer<MultiLoader> _loader;
            void loaderCompleteHandler(const Pointer<Event> &event);
        protected:
        public:
            bool _active;

            Main();

            void render();
    };
}

#endif

