#ifndef FLASH_RUNTIME_SOUND_H
#define FLASH_RUNTIME_SOUND_H

#include <flash/core/External.h>
#include <flash/core/Type.h>

namespace flash::runtime::Sound {
    imports sInt createSound(const void *callback, const void *instance);
    imports void deleteSound(const sInt soundID);
    imports void bindSoundSource(const sInt soundID, const sByte *bufferPtr, const heap bufferLen);

    imports sInt createSoundChannel(const sInt soundID, const void *callback, const void *instance);
    imports void deleteSoundChannel(const sInt channelID);
    imports void changeChannelTransform(const sInt channelID, const double gaining, const double panning);
    imports void playSoundChannel(const sInt channelID, const sInt offset);
    imports void stopSoundChannel(const sInt channelID);

    imports void changeMixerTransform(const double gaining, const double panning);
}

#endif
