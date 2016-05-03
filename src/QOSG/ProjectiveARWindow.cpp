#include "QOSG/ProjectiveARWindow.h"
#include "QOSG/ProjectiveARViewer.h"
#include "QOSG/ProjectiveAREventHandler.h"

#include "QOSG/ViewerQT.h"

#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFormLayout>
#include <QCloseEvent>
#include <QDebug>

#include "Util/ApplicationConfig.h"

QOSG::ProjectiveARWindow::ProjectiveARWindow( QWidget* parent, ViewerQT* sourceViewer, QApplication* app ) : QDialog( parent )
{
    this->app = app;
    viewerWidget = new ProjectiveARViewer( this, 0, 0, 0, sourceViewer );
    viewerWidget->addEventHandler(new ProjectiveAREventHandler(this));
    createLeftToolBar();

    setModal( false );
    setWindowTitle( tr( "Projector View Window" ) );

    QHBoxLayout* mainLayout		= new QHBoxLayout;
    //set layout
    mainLayout->addWidget( toolBar, Qt::AlignLeft );
    mainLayout->addWidget( viewerWidget, Qt::AlignCenter );
    mainLayout->setSizeConstraint( QLayout::SetMinimumSize );
    mainLayout->setMargin(0);
    setLayout( mainLayout );
    adjustSize();

    resize(1024, 764);

}

void QOSG::ProjectiveARWindow::toggleToolBars()
{
    if(toolBar->isHidden())
    {
        toolBar->show();
    }
    else
    {
        toolBar->hide();
    }
}

void QOSG::ProjectiveARWindow::createLeftToolBar()
{
    QFrame* line = NULL;

    QWidget* wScene = createSceneTab( line );

    toolBox = new QToolBox();
    toolBox->setSizePolicy( QSizePolicy( QSizePolicy::Maximum, QSizePolicy::Maximum ) );
    toolBox->setMinimumWidth( 163 );
    toolBox->addItem( wScene, tr( "Scene" ) );
    toolBar = new QToolBar( "Tools",this );

    QFrame* frame = createHorizontalFrame();
    frame->layout()->addWidget( toolBox );
    frame->layout()->setMargin(0);
    toolBar->addWidget( frame );

    toolBar->setMaximumWidth( 200 );
    //toolBar->setContentsMargins(0,0,0,0);
    //toolBar->setSizePolicy( QSizePolicy( QSizePolicy::Maximum, QSizePolicy:: ) );
    toolBar->setMovable( false );
}

QWidget* QOSG::ProjectiveARWindow::createSceneTab( QFrame* line )
{
    QWidget* wScene = new QWidget();
    QFormLayout* lScene = new QFormLayout( wScene );
    lScene->setContentsMargins( 1,1,1,1 );
    lScene->setSpacing( 2 );

    osg::Vec3d projectorPos = viewerWidget->getProjectorPos();
    osg::Vec3d projectorDir = viewerWidget->getProjectorDir();
    double projectorFOV = viewerWidget->getProjectorFOV();

    osg::Vec3d viewerPos = viewerWidget->getViewerPos();
    osg::Vec3d viewerDir = viewerWidget->getViewerDir();
    double viewerFOV = viewerWidget->getViewerFOV();

    // init options
    dsb_projectorFOV = new QDoubleSpinBox();
    dsb_projectorFOV->setRange(0, 360);
    dsb_projectorFOV->setValue(projectorFOV);
    dsb_projectorFOV->setToolTip("Projector field of view");
    dsb_projectorFOV->setSuffix(" °");
    dsb_projectorPosX = createCoordSpinBox(projectorPos.x(), "Projector X position");
    dsb_projectorPosY = createCoordSpinBox(projectorPos.y(), "Projector Y position");
    dsb_projectorPosZ = createCoordSpinBox(projectorPos.z(), "Projector Z position");
    dsb_projectorDirX = createCoordSpinBox(projectorDir.x(), "Projector X direction");
    dsb_projectorDirY = createCoordSpinBox(projectorDir.y(), "Projector Y direction");
    dsb_projectorDirZ = createCoordSpinBox(projectorDir.z(), "Projector Z direction");
    /*
    dsb_projectorPosX = new QDoubleSpinBox();
    dsb_projectorPosX->setRange(-20, 20);
    dsb_projectorPosX->setDecimals(3);
    dsb_projectorPosX->setSingleStep(0.01);
    dsb_projectorPosX->setValue(projectorPos.x());
    dsb_projectorPosX->setToolTip("Projector X position");
    dsb_projectorPosX->setSuffix(" m");
    dsb_projectorPosY = new QDoubleSpinBox();
    dsb_projectorPosY->setRange(-20, 20);
    dsb_projectorPosX->setDecimals(3);
    dsb_projectorPosX->setSingleStep(0.01);
    dsb_projectorPosY->setValue(projectorPos.y());
    dsb_projectorPosY->setToolTip("Projector Y position");
    dsb_projectorPosY->setSuffix(" m");
    dsb_projectorPosZ = new QDoubleSpinBox();
    dsb_projectorPosZ->setRange(-20, 20);
    dsb_projectorPosZ->setDecimals(3);
    dsb_projectorPosZ->setSingleStep(0.01);
    dsb_projectorPosZ->setValue(projectorPos.z());
    dsb_projectorPosZ->setToolTip("Projector Z position");
    dsb_projectorPosZ->setSuffix(" m");
    dsb_projectorDirX = new QDoubleSpinBox();
    dsb_projectorDirX->setRange(-20, 20);
    dsb_projectorDirX->setDecimals(3);
    dsb_projectorDirX->setSingleStep(0.01);
    dsb_projectorDirX->setValue(projectorDir.x());
    dsb_projectorDirX->setToolTip("Projector X direction");
    dsb_projectorDirX->setSuffix(" m");
    dsb_projectorDirY = new QDoubleSpinBox();
    dsb_projectorDirY->setRange(-20, 20);
    dsb_projectorDirY->setDecimals(3);
    dsb_projectorDirY->setSingleStep(0.01);
    dsb_projectorDirY->setValue(projectorDir.y());
    dsb_projectorDirY->setToolTip("Projector Y direction");
    dsb_projectorDirY->setSuffix(" m");
    dsb_projectorDirZ = new QDoubleSpinBox();
    dsb_projectorDirZ->setRange(-20, 20);
    dsb_projectorDirZ->setValue(projectorDir.z());
    dsb_projectorDirZ->setToolTip("Projector Z direction");
    dsb_projectorDirZ->setSuffix(" m");*/

    dsb_viewerFOV = new QDoubleSpinBox();
    dsb_viewerFOV->setRange(0, 360);
    dsb_viewerFOV->setValue(viewerFOV);
    dsb_viewerFOV->setToolTip("Viewer field of view");
    dsb_viewerFOV->setSuffix(" °");
    dsb_viewerPosX = createCoordSpinBox(viewerPos.x(), "Viewer X position");
    dsb_viewerPosY = createCoordSpinBox(viewerPos.y(), "Viewer Y position");
    dsb_viewerPosZ = createCoordSpinBox(viewerPos.z(), "Viewer Z position");
    dsb_viewerDirX = createCoordSpinBox(viewerDir.x(), "Viewer X direction");
    dsb_viewerDirY = createCoordSpinBox(viewerDir.y(), "Viewer Y direction");
    dsb_viewerDirZ = createCoordSpinBox(viewerDir.z(), "Viewer Z direction");
    /*dsb_viewerPosX = new QDoubleSpinBox();
    dsb_viewerPosX->setRange(-20, 20);
    dsb_viewerPosX->setValue(viewerPos.x());
    dsb_viewerPosX->setToolTip("Viewer X position");
    dsb_viewerPosX->setSuffix(" m");
    dsb_viewerPosY = new QDoubleSpinBox();
    dsb_viewerPosY->setRange(-20, 20);
    dsb_viewerPosY->setValue(viewerPos.y());
    dsb_viewerPosY->setToolTip("Viewer Y position");
    dsb_viewerPosY->setSuffix(" m");
    dsb_viewerPosZ = new QDoubleSpinBox();
    dsb_viewerPosZ->setRange(-20, 20);
    dsb_viewerPosZ->setValue(viewerPos.z());
    dsb_viewerPosZ->setToolTip("Viewer Z position");
    dsb_viewerPosZ->setSuffix(" m");
    dsb_viewerDirX = new QDoubleSpinBox();
    dsb_viewerDirX->setRange(-20, 20);
    dsb_viewerDirX->setValue(viewerDir.x());
    dsb_viewerDirX->setToolTip("Viewer X direction");
    dsb_viewerDirX->setSuffix(" m");
    dsb_viewerDirY = new QDoubleSpinBox();
    dsb_viewerDirY->setRange(-20, 20);
    dsb_viewerDirY->setValue(viewerDir.y());
    dsb_viewerDirY->setToolTip("Viewer Y direction");
    dsb_viewerDirY->setSuffix(" m");
    dsb_viewerDirZ = new QDoubleSpinBox();
    dsb_viewerDirZ->setRange(-20, 20);
    dsb_viewerDirZ->setValue(viewerDir.z());
    dsb_viewerDirZ->setToolTip("Viewer Z direction");
    dsb_viewerDirZ->setSuffix(" m");*/

    // init options
    /*dsb_projectorFOV = new QDoubleSpinBox();
    dsb_projectorFOV->setRange(0, 360);
    dsb_projectorFOV->setValue(projectorFOV);
    dsb_projectorFOV->setToolTip("Projector field of view");
    dsb_projectorFOV->setSuffix("°");
    dsb_projectorPosX = createCoordSpinBox(projectorPos.x(), "Projector X position");
    dsb_projectorPosY = createCoordSpinBox(projectorPos.y(), "Projector Y position");
    dsb_projectorPosZ = createCoordSpinBox(projectorPos.z(), "Projector Z position");
    dsb_projectorDirX = createCoordSpinBox(projectorDir.x(), "Projector X direction");
    dsb_projectorDirX = createCoordSpinBox(projectorDir.y(), "Projector Y direction");
    dsb_projectorDirZ = createCoordSpinBox(projectorDir.z(), "Projector Z direction");

    dsb_viewerFOV = new QDoubleSpinBox();
    dsb_viewerFOV->setRange(0, 360);
    dsb_viewerFOV->setValue(viewerFOV);
    dsb_viewerFOV->setToolTip("Viewer field of view");
    //dsb_viewerFOV->setSuffix("°");

    dsb_viewerPosX = createCoordSpinBox(viewerPos.x(), "Viewer X position");
    dsb_viewerPosY = createCoordSpinBox(viewerPos.y(), "Viewer Y position");
    dsb_viewerPosZ = createCoordSpinBox(viewerPos.z(), "Viewer Z position");
    dsb_viewerDirX = createCoordSpinBox(viewerDir.x(), "Viewer X direction");
    dsb_viewerDirY = createCoordSpinBox(viewerDir.y(), "Viewer Y direction");
    dsb_viewerDirZ = createCoordSpinBox(viewerDir.z(), "Viewer Z direction");*/


    b_applyScene = new QPushButton(tr("Apply scene"));


    // set tab layout
    lScene->addRow( new QLabel( "Projector" ) );
    dsb_projectorFOV->setMaximumWidth(80);
    lScene->addRow( new QLabel( "FOV:" ), dsb_projectorFOV );
    dsb_projectorPosX->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Pos X:" ), dsb_projectorPosX );
    dsb_projectorPosY->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Pos Y:" ), dsb_projectorPosY );
    dsb_projectorPosZ->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Pos Z:" ), dsb_projectorPosZ );
    dsb_projectorDirX->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Dir X:" ), dsb_projectorDirX );
    dsb_projectorDirY->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Dir Y:" ), dsb_projectorDirY );
    dsb_projectorDirZ->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Dir Z:" ), dsb_projectorDirZ );
    lScene->addRow(createLine());

    lScene->addRow( new QLabel( "Viewer" ) );
    dsb_viewerFOV->setMaximumWidth(80);
    lScene->addRow( new QLabel( "FOV:" ), dsb_viewerFOV );
    dsb_viewerPosX->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Pos X:" ), dsb_viewerPosX );
    dsb_viewerPosY->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Pos Y:" ), dsb_viewerPosY );
    dsb_viewerPosZ->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Pos Z:" ), dsb_viewerPosZ );
    dsb_viewerDirX->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Dir X:" ), dsb_viewerDirX );
    dsb_viewerDirY->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Dir Y:" ), dsb_viewerDirY );
    dsb_viewerDirZ->setMaximumWidth(80);
    lScene->addRow( new QLabel( "Dir Z:" ), dsb_viewerDirZ );
    lScene->addRow(createLine());

    lScene->addRow(b_applyScene);
    connect( b_applyScene, SIGNAL( clicked() ), this, SLOT( applySceneSettings() ) );

    wScene->setLayout(lScene);

    return wScene;
}

QDoubleSpinBox* QOSG::ProjectiveARWindow::createCoordSpinBox(double value, const QString& text)
{
    QDoubleSpinBox* dsb = new QDoubleSpinBox();
    dsb->setRange(-20, 20);
    dsb->setDecimals(3);
    dsb->setSingleStep(0.01);
    dsb->setValue(value);
    dsb->setToolTip(text);
    dsb->setSuffix(" m");
    return dsb;
}

/*
QGroupBox* QOSG::ProjectiveARWindow::createProjectorGroupBox()
{
    QGroupBox* group = createGroupBox( tr( "Radial layout" ) );
    QFormLayout* layoutGroup = createGroupLayout();
    b_SetRestriction_RadialLayout->setMinimumWidth( 68 );



    group->setLayout( layoutGroup );

    return group;
}*/

QFrame* QOSG::ProjectiveARWindow::createLine()
{
    QFrame* line = new QFrame();
    line->setFrameShape( QFrame::HLine );
    line->setFrameShadow( QFrame::Sunken );
    line->setMinimumHeight( 15 );
    line->setMaximumWidth( 138 );

    return line;
}

QFrame* QOSG::ProjectiveARWindow::createHorizontalFrame()
{
    QFrame* frame = new QFrame();
    QHBoxLayout* layout = new QHBoxLayout();
    frame->setLayout( layout );
    layout->setMargin( 0 );
    layout->setSpacing( 0 );

    return frame;
}

void QOSG::ProjectiveARWindow::closeEvent( QCloseEvent* event )
{
    qDebug() << "Closing ProjectiveARWindow Window";

	disconnect();

	event->accept();
}


void QOSG::ProjectiveARWindow::applySceneSettings()
{
    qDebug() << "projectorPosX " << dsb_projectorPosX->value() << "\n";
    qDebug() << "projectorPosY " << dsb_projectorPosY->value() << "\n";
    qDebug() << "projectorPosZ " << dsb_projectorPosZ->value() << "\n";
    qDebug() << "projectorDirX " << dsb_projectorDirX->value() << "\n";
    qDebug() << "projectorDirY " << dsb_projectorDirY->value() << "\n";
    qDebug() << "projectorDirZ " << dsb_projectorDirZ->value() << "\n";
    qDebug() << "projectorFOV " << dsb_projectorFOV->value() << "\n\n";
    qDebug() << "viewerPosX " << dsb_viewerPosX->value() << "\n";
    qDebug() << "viewerPosY " << dsb_viewerPosY->value() << "\n";
    qDebug() << "viewerPosZ " << dsb_viewerPosZ->value() << "\n";
    qDebug() << "viewerDirX " << dsb_viewerDirX->value() << "\n";
    qDebug() << "viewerDirY " << dsb_viewerDirY->value() << "\n";
    qDebug() << "viewerDirZ " << dsb_viewerDirZ->value() << "\n";
    qDebug() << "viewerFOV " << dsb_viewerFOV->value() << "\n";

    viewerWidget->setProjectorPos(dsb_projectorPosX->value(),
                                  dsb_projectorPosY->value(),
                                  dsb_projectorPosZ->value());
    viewerWidget->setProjectorDir(dsb_projectorDirX->value(),
                                  dsb_projectorDirY->value(),
                                  dsb_projectorDirZ->value());
    viewerWidget->setProjectorFOV(dsb_projectorFOV->value());

    viewerWidget->setViewerPos(dsb_viewerPosX->value(),
                               dsb_viewerPosY->value(),
                               dsb_viewerPosZ->value());
    viewerWidget->setViewerDir(dsb_viewerDirX->value(),
                               dsb_viewerDirY->value(),
                               dsb_viewerDirZ->value());
    viewerWidget->setViewerFOV(dsb_viewerFOV->value());

    viewerWidget->updateScene();
}