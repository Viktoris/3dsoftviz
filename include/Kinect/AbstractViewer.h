#ifndef ABSTRACTVIEWER_H
#define ABSTRACTVIEWER_H

#include "osgGA/GUIEventAdapter"

namespace Kinect {

class AbstractViewer
{

public:
	virtual ~AbstractViewer( void ) {}

	virtual void typeKey(osgGA::GUIEventAdapter::KeySymbol key) = 0;
	virtual void mouseScroll2D(float x,float y, double time) = 0;

private:

};
}

#endif // ABSTRACTVIEWER_H
