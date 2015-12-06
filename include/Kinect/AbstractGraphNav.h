#ifndef ABSTRACTGRAPHNAV_H
#define ABSTRACTGRAPHNAV_H

namespace Kinect {

class AbstractGraphNav
{

public:
	virtual ~AbstractGraphNav( void ) {}

	virtual bool isNavEnabled() = 0;
	virtual void selectNearestNode() = 0;
	virtual void removeLastSelectedNode() = 0;
	virtual void navigate() = 0;

private:

};
}

#endif // ABSTRACTGRAPHNAV_H
