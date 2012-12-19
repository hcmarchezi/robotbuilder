// LinkPosition.h: interface for the LinkPosition class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LINKPOSITION_H
#define LINKPOSITION_H

#include "Link.h"
#include "Trajectory.h"

namespace PDC
{

class LinkPosition
{
public:
	LinkPosition(Link * link);
	virtual ~LinkPosition();

        void SetLinkVelocity(double velocity);
	double GetLinkVelocity();
	void SetLinkPositionMov(double movement);
	double GetLinkPositionMov();

        bool IsTrajectoryCalculated();
	void CalculateLinkTrajectory(double initialtime,double finaltime);
	void SetNextLinkPosition (LinkPosition * linkposition);

	void MoveLink(double time);
	void CaptureLinkPosition();

private:
        // Trajetoria da Posicao de Link (LinkPosition)
        Trajectory * m_trajectory;
        // Toda Posicao de Link controla um determinado Link que eh o do
        // atributi abaixo
        Link   * m_link;
        // Posicao do Link no instante que o LinkPosition ocorre
        double m_link_position;
        // Velocidade do Link no instante que o LinkPosition ocorre
        double m_link_velocity;
        // Referencia a proxima posicao de Link
        LinkPosition * m_next_linkposition;
};

}

#endif
