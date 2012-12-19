// RobotPosition.h: interface for the RobotPosition class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ROBOTPOSITION_H
#define ROBOTPOSITION_H

#include "LinkPosition.h"

namespace PDC
{

class RobotPosition
{
private:
	double  m_time_instant;
	vector<LinkPosition *> m_linkpositions;
    RobotPosition * m_next_robotposition;

public:
	RobotPosition();
	virtual ~RobotPosition();

	void SetNextRobotPosition(RobotPosition * robotposition);
	void CalculateRobotTrajectory();

	LinkPosition * GetLinkPosition (long linknumber);
    	bool operator< (RobotPosition * position);
	void MoveRobotLinks(double time);
	bool IsTrajectoryCalculated();

	void AddLinkPosition (LinkPosition * linkposition);

	double  GetInstantTime();
	void    SetInstantTime(double time);
};

}

#endif
