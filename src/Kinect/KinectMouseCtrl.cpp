#include "Kinect/KinectMouseCtrl.h"

Kinect::KinectMouseCtrl::KinectMouseCtrl(){
	mouse = new Vwr::MouseControl();
}
Kinect::KinectMouseCtrl::~KinectMouseCtrl(){
	delete(mouse);
}

void Kinect::KinectMouseCtrl::setSpeedUpMoving(double speed){
	mouse->setSpeedUpMoving(speed);
}

void Kinect::KinectMouseCtrl::moveCursorWorldCoordinates(float positionX,float positionY, bool isClick){
	mouse->moveCursorWorldCoordinates(positionX,positionY, isClick);
}

void Kinect::KinectMouseCtrl::clickMouseLeftButton(){
	mouse->clickMouseLeftButton();
}
