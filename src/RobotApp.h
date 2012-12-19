// RobotApp.h: interface for the RobotApp class.
//
//////////////////////////////////////////////////////////////////////

#include <qobject.h>
#include "WRobotConstruction.h"
#include "WRobotTrajectory.h"
#include "Robot.h"
#include <vector>

using namespace std;
using namespace HIC;

namespace TMC
{

class RobotApp : public QObject
{
    Q_OBJECT
public:
	RobotApp(QWidget * parent, Robot * robot);
	virtual ~RobotApp();
	void SetTrajectoryWindow(WRobotTrajectory * robotTrajectoryWindow);

public slots:
	int Exec();
	void SelectRobotLink();
	void InformLinkNumber();
	void SelectNewLinkType();
	void ExcludeLinkRobot();
	void UpdatePositionLinkRobot();
	void InsertNewLinkRobot();
	void LoadRobot ();
	void SaveRobot();
	void ExcludeRobot();
	void UpdateRobot();
	void CreateRobot();

private:
    // Janela para a construcao de robo
    WRobotConstruction * m_robotconstructionwindow;
    // Robo da aplicacao
    Robot * m_robot;
    // Array de tipos de link
    vector<LinkType *> m_linktypes;

	// Referencia para a janela de trajatoria para
	// a atualizacao de controles de link para cada
	// link removido ou adicionado na construcao
	WRobotTrajectory * m_robottrajectorywindow;
};

}


