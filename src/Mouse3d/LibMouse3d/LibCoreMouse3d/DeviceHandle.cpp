
#include <string.h>
#include <QDebug>
#include "Mouse3d/LibMouse3d/LibCoreMouse3d/DeviceHandle.h"

LibMouse3d::LibCoreMouse3d::DeviceHandle* LibMouse3d::LibCoreMouse3d::DeviceHandle::device;

LibMouse3d::LibCoreMouse3d::DeviceHandle::DeviceHandle() {

    device = this;
    this->InitDevice();
}

LibMouse3d::LibCoreMouse3d::DeviceHandle::~DeviceHandle() {

}

/**
*@author Michal Fasanek
*@date 23.11.2015
*@brief DeviceHandle method responsible for binding device to running thread.
*/
LibMouse3d::LibCoreMouse3d::DeviceHandle* LibMouse3d::LibCoreMouse3d::DeviceHandle::getInstance(){

    if(LibMouse3d::LibCoreMouse3d::DeviceHandle::device == NULL){

        //trying pass constructor into shared pointer
        LibMouse3d::LibCoreMouse3d::DeviceHandle::device = new LibMouse3d::LibCoreMouse3d::DeviceHandle();
    }

    return LibMouse3d::LibCoreMouse3d::DeviceHandle::device;
}

void LibMouse3d::LibCoreMouse3d::DeviceHandle::TerminateDevice(SiHdl device){

    SiClose (device);
    SiTerminate();

}

/**
 * @brief LibMouse3d::LibCoreMouse3d::DeviceHandle::InitDevice
 * @param windowHandleId
 * @param appName
 * @author Michal Fasanek
 * @brief creates a connection to the hardware device using SI functions that should be passed to thread receiving events
 */
void LibMouse3d::LibCoreMouse3d::DeviceHandle::InitDevice(){


    SiInitialize();
    if((deviceRef = SiOpen("3dSoftviz", SI_ANY_DEVICE, SI_NO_MASK, SI_EVENT, initData.get())) == SI_NO_HANDLE)

        qDebug() << "Failed to open 3DxWare device";

    else

        qDebug() << "Success opening 3DxWare device";
}

bool LibMouse3d::LibCoreMouse3d::DeviceHandle::isInitialized(){
    if(deviceRef != NULL)
        return true;

    else
        return false;
}

SiHdl LibMouse3d::LibCoreMouse3d::DeviceHandle::getDeviceRef(){
        return this->deviceRef;
}
