// Application.cpp: implementation of the Application class.
//
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif

#include "Application.h"

#include "LinkType.h"
#include <vector>
#include <qapplication.h>
#include <qmenubar.h>


using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMC::Application::Application()
{
    int argc = 1;

    char ** argv = NULL;

    // Connecting main window menu events to application slots

    m_qtapp = new QApplication(argc,argv);
    m_mainwindow = new WMain("An Environment to Build and Animate Manipulator Robots - versao 0.1");
    m_mainwindow->m_menu_window->connectItem(1,this,SLOT(CallLinkApp()));
    m_mainwindow->m_menu_window->connectItem(2,this,SLOT(CallRobotApp()));
    m_mainwindow->m_menu_window->connectItem(3,this,SLOT(CallTrajectoryApp()));

    ///////////////////////////////////////////////////////////////
    // Load all link types
    ///////////////////////////////////////////////////////////////

    /*
    double coord[4][4];
    RevoluteLinkType * basetype;
    RevoluteLinkType * armtype;
    RevoluteLinkType * endeffectortype;

    // Revolute Link Type Construction
    
    coord[0][0]=0.0;  coord[0][1]=0.0; coord[0][2]=1.0; coord[0][3]=330.0;
    coord[1][0]=0.0;  coord[1][1]=1.0; coord[1][2]=0.0; coord[1][3]=-77.0;
    coord[2][0]=-1.0; coord[2][1]=0.0; coord[2][2]=0.0; coord[2][3]=-15.0;
    coord[3][0]=0.0;  coord[3][1]=0.0; coord[3][2]=0.0; coord[3][3]=1.0;
    basetype = new RevoluteLinkType();
    basetype->LoadGeometry("robotarm.3ds","Base");
    basetype->SetCoordinateSystem(coord);
    basetype->SetLinkLength(550.0);
    basetype->SetLinkTwist(0.0);
    basetype->SetLinkOffset(0.0);
    basetype->SetLinkTypeFunction(BASE);
    
    coord[0][0]=0.0;  coord[0][1]=1.0; coord[0][2]=0.0; coord[0][3]=77.0;
    coord[1][0]=0.0;  coord[1][1]=0.0; coord[1][2]=1.0; coord[1][3]=-15.0;
    coord[2][0]=1.0;  coord[2][1]=0.0; coord[2][2]=0.0; coord[2][3]=-330.0;
    coord[3][0]=0.0;  coord[3][1]=0.0; coord[3][2]=0.0; coord[3][3]=1.0;
    basetype = new RevoluteLinkType();
    basetype->LoadGeometry("robotarm.3ds","Base");
    basetype->SetCoordinateSystem(coord);
    basetype->SetLinkLength(0.0);
    basetype->SetLinkTwist(0.0);
    basetype->SetLinkOffset(550.0);
    basetype->SetLinkTypeFunction(BASE);

    // Revolute Link Arm Construction

    coord[0][0]=0.0;  coord[0][1]=0.0; coord[0][2]=1.0; coord[0][3]= 200.0;
    coord[1][0]=0.0;  coord[1][1]=1.0; coord[1][2]=0.0; coord[1][3]= -77.0;
    coord[2][0]=-1.0; coord[2][1]=0.0; coord[2][2]=0.0; coord[2][3]= -15.0;
    coord[3][0]=0.0;  coord[3][1]=0.0; coord[3][2]=0.0; coord[3][3]= 1.0;
    armtype = new RevoluteLinkType();
    armtype->LoadGeometry("robotarm.3ds","V-Shaft");
    armtype->SetCoordinateSystem(coord);
    armtype->SetLinkLength(570.0);
    armtype->SetLinkTwist(0.0);
    armtype->SetLinkOffset(0.0);
    armtype->SetLinkTypeFunction(ACTUATOR);

    // Link Type Construction with a Tool attached

    coord[0][0]=80.0;  coord[0][1]=0.0;  coord[0][2]=0.0;   coord[0][3]= -70.0;
    coord[1][0]=0.0;   coord[1][1]=80.0; coord[1][2]=0.0;   coord[1][3]= -450.0;
    coord[2][0]=0.0;   coord[2][1]=0.0;  coord[2][2]=80.0;  coord[2][3]= 450.0;
    coord[3][0]=0.0;   coord[3][1]=0.0;  coord[3][2]=0.0;   coord[3][3]= 1.0;
    endeffectortype = new RevoluteLinkType();
    endeffectortype->LoadGeometry("TIG.3DS","01");
    endeffectortype->SetCoordinateSystem(coord);
    endeffectortype->SetLinkLength(570.0);
    endeffectortype->SetLinkTwist(0.0);
    endeffectortype->SetLinkOffset(0.0);
    endeffectortype->SetLinkTypeFunction(ACTUATOR);

    // Adding link types in the link types vector

    m_linktypes.push_back(basetype);
    m_linktypes.push_back(armtype);
    m_linktypes.push_back(endeffectortype);

    // Creating the first link (base) with a basetype link type

    Link * base = new Link(basetype);
    base->SetLinkNumber(0);

    // Creating links arm1 and arm2 with link type armtype

    Link * arm1 = new Link(armtype);
    arm1->SetLinkNumber(1);
    Link * arm2 = new Link(armtype);
    arm2->SetLinkNumber(2);
    Link * arm3 = new Link(armtype);
    arm3->SetLinkNumber(3);
    Link * endeffector = new Link(endeffectortype);
    endeffector->SetLinkNumber(4);

    // Adding robot links

    m_robot = new Robot();
    m_robot->AddLink(base);
    m_robot->AddLink(arm1);
    m_robot->AddLink(arm2);
    m_robot->AddLink(arm3);
    m_robot->AddLink(endeffector);    
    m_robot = new Robot();
	*/

    m_robot = NULL;
   
    // Initializing class attributtes
    m_linktypeapplication   = new LinkApp(m_mainwindow->m_workspace,0);
    m_robotapplication      = new RobotApp(m_mainwindow->m_workspace,m_robot);
    m_trajectoryapplication = new TrajectoryApp(m_mainwindow->m_workspace,m_robot);

    // Gets trajectory window reference which will be used for control updates
    m_robotapplication->SetTrajectoryWindow(m_trajectoryapplication->getTrajectoryWindow());
}

TMC::Application::~Application()
{
    unsigned long i;
	
    // Desaloca a lista de linktypes
    for (i=0;i < m_linktypes.size();i++)
        delete m_linktypes[i];

    // Dealloc applications
    delete m_linktypeapplication;
    delete m_robotapplication;
    delete m_trajectoryapplication;

    // Dealloc robot
	if (m_robot != NULL) 
	{
		delete m_robot;
	}
}

void TMC::Application::CallLinkApp()
{
    m_linktypeapplication->Exec();
}

void TMC::Application::CallRobotApp()
{
    m_robotapplication->Exec();
}

void TMC::Application::CallTrajectoryApp()
{
    m_trajectoryapplication->Exec();
}


int TMC::Application::Exec(int argc, char **argv)
{
    //GraphicObject * graphicOb;
    //graphicOb = new GraphicObject();

    // Main Window opening
    m_mainwindow->showMaximized();
    m_qtapp->connect(m_qtapp,SIGNAL(lastWindowClosed()),m_qtapp,SLOT(quit()) );
    return  m_qtapp->exec();
}
