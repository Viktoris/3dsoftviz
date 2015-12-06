#ifndef ABSTRACTMOUSECTRL_H
#define ABSTRACTMOUSECTRL_H

namespace Kinect {

class AbstractMouseCtrl
{

public:
	virtual ~AbstractMouseCtrl( void ) {}

	virtual void setSpeedUpMoving(double speed) = 0;
	virtual void moveCursorWorldCoordinates(float depthX,float depthY, bool flag) = 0;
	virtual void clickMouseLeftButton() = 0;
private:

};
}

#endif // ABSTRACTMOUSECTRL_H
