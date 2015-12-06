#ifndef KINECTMOUSECTRL_H
#define KINECTMOUSECTRL_H

#include "Kinect/AbstractMouseCtrl.h"
#include "Viewer/MouseControl.h"

namespace Kinect {

class KinectMouseCtrl : Kinect::AbstractMouseCtrl
{
public:
	KinectMouseCtrl();
	~KinectMouseCtrl();
	void setSpeedUpMoving(double speed);
	void moveCursorWorldCoordinates(float depthX,float depthY, bool flag);
	void clickMouseLeftButton();

private:
	Vwr::MouseControl* mouse;
};
}

#endif // KINECTMOUSECTRL_H
