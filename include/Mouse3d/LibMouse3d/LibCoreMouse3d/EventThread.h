#ifndef EVEBTTHREAH_H
#define EVEBTTHREAH_H


#include <si.h>
#include <siapp.h>
#include <QThread>
#include "DeviceHandle.h"

//using namespace System::Windows::Forms;

namespace LibMouse3d{
namespace LibCoreMouse3d{


/**
*@author Michal Fasanek
*@date 23.11.2015
*@brief LibCore class responsible for catching device activity.
*/
class EventThread : public QThread{

    Q_OBJECT

public:

    //constructor
    EventThread(QObject* parent=0);

    //destructor
    ~EventThread(void);

    void run();

private:
    //received message -unsigned integer-
    UINT msg;

    //storage of received data - platform dependent - probably front
    const std::shared_ptr<SiGetEventData> eData;

    //message windows-specific parameters
    WPARAM wParam;
    LPARAM lParam;

    //incoming mouse event
    std::shared_ptr<SiSpwEvent> siEvent;
};

}
}
#endif
