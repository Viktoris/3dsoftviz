#include "Kinect/KinectGraphNav.h"

Kinect::KinectGraphNav::KinectGraphNav(){
	nav = new Vwr::GraphNavigation();
}

Kinect::KinectGraphNav::~KinectGraphNav(){
	delete(nav);
}

bool Kinect::KinectGraphNav::isNavEnabled(){
	return nav->isNavEnabled;
}

void Kinect::KinectGraphNav::selectNearestNode(){
	nav->selectNearestNode();
}

void Kinect::KinectGraphNav::removeLastSelectedNode(){
	nav->removeLastSelectedNode();
}

void Kinect::KinectGraphNav::navigate(){
	nav->navigate();
}
