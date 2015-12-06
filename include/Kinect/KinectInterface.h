#ifndef KINECTINTERFACE_H
#define KINECTINTERFACE_H

#include "Kinect/KinectGraphNav.h"
#include "Kinect/KinectMouseCtrl.h"
#include "Kinect/KinectViewer.h"

#include "Kinect/KinectThread.h"

namespace Kinect {

class KinectInterface
{

public:
	KinectInterface();
	~KinectInterface();

	void start();
private:
	KinectGraphNav* graphNav;
	KinectMouseCtrl* mouseCtrl;
	KinectViewer* viewer;

	KinectThread* kinectThread;
};
}

#endif // KINECTINTERFACE_H
