// TrajectoryApp.h: interface for the TrajectoryApp class.
//
//////////////////////////////////////////////////////////////////////

#include <qobject.h>
#include "WRobotTrajectory.h"
#include "Robot.h"

using namespace HIC;

namespace TMC
{

class TrajectoryApp : public QObject
{
    Q_OBJECT
public:
	int Exec();
	TrajectoryApp(QWidget * parent, Robot * robot);
	virtual ~TrajectoryApp();
	WRobotTrajectory * getTrajectoryWindow();

public slots:
  	void AnimateRobot();
//	void CalculateTrajectory();
	void ExcludeRobotPosition();
	void UpdateRobotPosition ();
	void AddRobotPosition();

private:
    WRobotTrajectory * m_robottrajectorywindow;
    Robot * m_robot;
	double counter;
    bool   bAnimation;
   void Wait();
};

}


