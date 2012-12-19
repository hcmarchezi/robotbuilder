// Trajectory.h: interface for the Trajectory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TRAJECTORY_H
#define TRAJECTORY_H

namespace PDC

{

class Trajectory
{
private:
// A Trajetoria e descrita por meio de um polinomio de 3o grau, na forma seguinte:
// p(t) = a0 + a1 t + a2 t^2 + a3 t^3
// Dado um tempo t, o polinomio retorna a posicao do Link naquele tempo
// Entretanto essa trajetoria so e valida entre uma Posicao de Link ate a outra
	double m_a0;
	double m_a1;
	double m_a2;
	double m_a3;

public:
	Trajectory();
	virtual ~Trajectory();

	double CalculateValue(double variable);
        void CalculateTrajectory (double initialtime,double finaltime,double initialposition,double finalposition,double initialvelocity,double finalvelocity);
};

}

#endif
