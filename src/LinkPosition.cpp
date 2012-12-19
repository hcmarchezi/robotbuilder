// LinkPosition.cpp: implementation of the LinkPosition class.
//
//////////////////////////////////////////////////////////////////////

#include "LinkPosition.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::LinkPosition::LinkPosition(Link * link)
{
    m_link = link;
    m_next_linkposition = NULL;
    m_trajectory = NULL;
}

PDC::LinkPosition::~LinkPosition()
{
    if (m_trajectory != NULL)
        delete m_trajectory;
}

void PDC::LinkPosition::CaptureLinkPosition()
{
    m_link_position = m_link->GetVariableLinkParam();
}

void PDC::LinkPosition::MoveLink(double time)
{
    m_link->SetVariableLinkParam(m_trajectory->CalculateValue(time));
}


void PDC::LinkPosition::SetNextLinkPosition(LinkPosition *linkposition)
{
    m_next_linkposition = linkposition;
}

void PDC::LinkPosition::CalculateLinkTrajectory(double initialtime, double finaltime)
{
    // Pega as posições iniciais e finais do Link
    double initialposition = GetLinkPositionMov();
    double finalposition   = m_next_linkposition->GetLinkPositionMov();
    double initialvelocity = GetLinkVelocity();
    double finalvelocity   = m_next_linkposition->GetLinkVelocity();
    
    
    /*
    if (finalposition < initialposition)
        m_next_linkposition->SetLinkVelocity(-fabs(finalvelocity));    
    else
        m_next_linkposition->SetLinkVelocity(fabs(finalvelocity));
    */

    if (m_trajectory != NULL)
        delete m_trajectory;
    
    Trajectory * trajectory = new Trajectory;
    trajectory->CalculateTrajectory(initialtime,finaltime,initialposition,finalposition,initialvelocity,finalvelocity);

    m_trajectory = trajectory;
}

bool PDC::LinkPosition::IsTrajectoryCalculated()
{
    return (m_trajectory != NULL);
}

double PDC::LinkPosition::GetLinkPositionMov()
{
    return m_link_position;
}

void PDC::LinkPosition::SetLinkPositionMov(double movement)
{
    m_link_position = movement;
}

double PDC::LinkPosition::GetLinkVelocity()
{
    return m_link_velocity;
}

void PDC::LinkPosition::SetLinkVelocity(double velocity)
{
    m_link_velocity = velocity;
}
