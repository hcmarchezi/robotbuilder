// RobotPosition.cpp: implementation of the RobotPosition class.
//
//////////////////////////////////////////////////////////////////////

#include "RobotPosition.h"

using namespace PDC;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::RobotPosition::RobotPosition()
{

}

PDC::RobotPosition::~RobotPosition()
{
    unsigned long i;

    for (i=0;i < m_linkpositions.size();i++)
        delete m_linkpositions[i];
}

double PDC::RobotPosition::GetInstantTime()
{
    return m_time_instant;
}

void PDC::RobotPosition::SetInstantTime(double time)
{
    m_time_instant = time;
}


void PDC::RobotPosition::AddLinkPosition(LinkPosition * linkposition)
{
    m_linkpositions.push_back(linkposition);
}

bool PDC::RobotPosition::IsTrajectoryCalculated()
{
    return (m_linkpositions[0]->IsTrajectoryCalculated());
}

void PDC::RobotPosition::MoveRobotLinks(double time)
{
    // Erro: Tempo informado esta fora do padrao
    //if (time < m_time_instant)
        //return;

    unsigned long i = 0;

    for (i=0;i<m_linkpositions.size();i++)
        m_linkpositions[i]->MoveLink(time);
}

bool PDC::RobotPosition::operator<(RobotPosition * position)
{
    return (this->GetInstantTime() < position->GetInstantTime());
}



LinkPosition * PDC::RobotPosition::GetLinkPosition(long linknumber)
{
    return m_linkpositions[linknumber];
}

void PDC::RobotPosition::CalculateRobotTrajectory()
{
    unsigned long i;

    double initialtime      = GetInstantTime();
    double finaltime        = m_next_robotposition->GetInstantTime();
    
    for (i = 0;i < m_linkpositions.size();i++)
       m_linkpositions[i]->CalculateLinkTrajectory(initialtime,finaltime);
}

void PDC::RobotPosition::SetNextRobotPosition(RobotPosition *robotposition)
{
    m_next_robotposition = robotposition;
}
