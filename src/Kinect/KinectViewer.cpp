#include "Kinect/KinectViewer.h"

Kinect::KinectViewer::KinectViewer(QOSG::ViewerQT* vwr){
	viewer = vwr;
}

void Kinect::KinectViewer::typeKey(osgGA::GUIEventAdapter::KeySymbol key){
	viewer->getEventQueue()->keyPress( key );
}

void Kinect::KinectViewer::mouseScroll2D(float x,float y, double time){
	viewer->getEventQueue()->mouseScroll2D(x,y,time);
}
