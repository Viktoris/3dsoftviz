#include "Kinect/KinectInterface.h"
#include "Core/Core.h"

Kinect::KinectInterface::KinectInterface(){
	graphNav = new Kinect::KinectGraphNav();
	mouseCtrl = new Kinect::KinectMouseCtrl();
	viewer = new Kinect::KinectViewer(AppCore::Core::getInstance()->getCoreWindow()->GetViewerQt());

	//TODO resolve config bs ..
	kinectThread = new Kinect::KinectThread(mouseCtrl,viewer,graphNav, Util::ApplicationConfig::get()->_map, NULL);
}

Kinect::KinectInterface::~KinectInterface(){
	delete(graphNav);
	delete(mouseCtrl);
	delete(viewer);

	if ( kinectThread != NULL ) {
		kinectThread->setCancel( true );
		kinectThread->setImageSend( false );

		kinectThread->wait();
		kinectThread->deleteLater();
	}
}

void Kinect::KinectInterface::start(){
	if (kinectThread != NULL){
		kinectThread->inicializeKinect();
	}
}


