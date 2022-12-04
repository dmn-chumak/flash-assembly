#ifndef FLASH_RUNTIME_NETWORK_H
#define FLASH_RUNTIME_NETWORK_H

#include <flash/core/External.h>
#include <flash/core/Type.h>
#include <flash/network/URLLoader.h>

namespace flash::runtime::Network {
    imports sInt createLoader(const void *callback, const void *instance);
    imports void deleteLoader(const sInt loaderID);
    imports void startLoadingSource(const sInt loaderID, const sChar *source, const heap length);
    imports void stopLoadingSource(const sInt loaderID);
    imports void bindLoadedData(const sInt loaderID, const sByte *buffer, const heap length);

    imports sInt createSocket(const void *callback, const void *instance);
    imports void deleteSocket(const sInt socketID);
    imports void openSocketConnection(const sInt socketID, const sChar *source, const heap length, const sInt port);
    imports void sendSocketData(const sInt socketID, const sByte *buffer, const heap length);
    imports void closeSocketConnection(const sInt socketID);
    imports void bindSocketData(const sInt socketID, const sByte *buffer, const heap length);
}

#endif
