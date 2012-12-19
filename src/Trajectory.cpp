// Trajectory.cpp: implementation of the Trajectory class.
//
//////////////////////////////////////////////////////////////////////

#include "Trajectory.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::Trajectory::Trajectory()
{

}

PDC::Trajectory::~Trajectory()
{

}

double PDC::Trajectory::CalculateValue(double variable)
{
    return m_a0 + m_a1*variable + m_a2*pow(variable,2.0) + m_a3*pow(variable,3.0);
}

void PDC::Trajectory::CalculateTrajectory(double initialtime, double finaltime, double initialposition, double finalposition, double initialvelocity, double finalvelocity)
{
    // ERRO: tempo inicial = tempo final retorna para evitar erro na fórmula
    if (initialtime == finaltime) 
    {
        m_a0 = m_a1 = m_a2 = m_a3 = 0;
        return;
    }
        
    m_a0 = initialposition;
    m_a1 = initialvelocity;
    m_a2 = (3.0)/pow((finaltime - initialtime),2.0)*(finalposition - initialposition) - (2.0)/(finaltime - initialtime)*initialvelocity - (1.0)/(finaltime - initialtime)*finalvelocity;
    m_a3 = -(2.0)/pow((finaltime - initialtime),3.0)*(finalposition - initialposition) + (1.0)/pow((finaltime - initialtime),2.0)*(finalvelocity + initialvelocity);

    //m_a2 = (3.0)/pow((finaltime),2.0)*(finalposition - initialposition) - (2.0)/(finaltime)*initialvelocity - (1.0)/(finaltime)*finalvelocity;
    //m_a3 = -(2.0)/pow((finaltime),3.0)*(finalposition - initialposition) + (1.0)/pow((finaltime),2.0)*(finalvelocity - initialvelocity);

}

