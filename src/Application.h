// Application.h: interface for the Application class.
//
//////////////////////////////////////////////////////////////////////


#ifndef APPLICATION_H
#define APPLICATION_H

#include <qobject.h>
#include "WMain.h"	
#include "LinkApp.h"
#include "TrajectoryApp.h"
#include "RobotApp.h"

namespace TMC
{

class Application : public QObject
{
    Q_OBJECT
public:
	int Exec (int argc,char ** argv);
	Application();
	virtual ~Application();

public slots:
	void CallTrajectoryApp();
	void CallRobotApp();
	void CallLinkApp();

private:
    vector<LinkType *> m_linktypes;
    Robot * m_robot;
    LinkType * m_linktype;

    WMain * m_mainwindow;

    QApplication * m_qtapp;

    // Remaining apps
    LinkApp       * m_linktypeapplication;
    RobotApp      * m_robotapplication;
    TrajectoryApp * m_trajectoryapplication;

};

}

#endif

