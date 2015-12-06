#ifndef KINECTGRAPHNAV_H
#define KINECTGRAPHNAV_H

#include "Kinect/AbstractGraphNav.h"
#include "Viewer/GraphNavigation.h"

namespace Kinect {

class KinectGraphNav : public AbstractGraphNav
{
public:
	KinectGraphNav();
	~KinectGraphNav();

	bool isNavEnabled();
	void selectNearestNode();
	void removeLastSelectedNode();
	void navigate();
private:
	Vwr::GraphNavigation* nav;
};
}

#endif // KINECTGRAPHNAV_H
