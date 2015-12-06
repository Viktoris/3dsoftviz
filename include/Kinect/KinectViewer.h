#ifndef KINECTVIEWER_H
#define KINECTVIEWER_H

#include "Kinect/AbstractViewer.h"
#include "QOSG/ViewerQT.h"

namespace Kinect {

class KinectViewer : Kinect::AbstractViewer
{
public:
	KinectViewer(QOSG::ViewerQT *vwr);

	void typeKey(osgGA::GUIEventAdapter::KeySymbol key);
	void mouseScroll2D(float x,float y, double time);
private:
	QOSG::ViewerQT* viewer;
};
}

#endif // KINECTVIEWER_H
