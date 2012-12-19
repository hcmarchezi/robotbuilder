// Robot.h: interface for the Robot class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ROBOT_H
#define ROBOT_H

#include "Link.h"
#include "RobotPosition.h"
#include "PersistentRobot.h"

using namespace PDC;
using namespace DMC;
using namespace std;

namespace PDC
{

class Robot : public GraphicObject
{
public:
  // Robot Sombra
    PersistentRobot * m_persistentrobot;

	Robot();
        virtual ~Robot();

        // Metodos que manipulam a posicao do Robo que coincide com a posicao
        // da sua base e o nome do robo
        void SetBasePosition(double frame[4][4]);
        void GetBasePosition(double (* frame)[4][4]);
        string GetRobotName();
        void SetRobotName(string name);

        void AddLink(Link * newlink);
        void AddLinkFirstPosition(Link * newlink);
        void AddLinkLastPosition(Link * newlink);
        void ChangeLinkNumber(long newnumber,Link * selectedlink);
        void RemoveLink (Link * selectedlink);
        long SizeLink();
        Link * GetLink(long linknumber);
        bool IsValidLinkNumber(Link * newlink);

        bool AddRobotPosition(RobotPosition * newrobotposition);
	bool UpdateRobotPosition(RobotPosition * selectedrobotposition);
	void RemoveRobotPosition(RobotPosition * selectedrobotposition);
        RobotPosition * GetRobotPosition(long order);
        long SizeRobotPosition();
        RobotPosition * CaptureRobotPosition();

	double GetFinalTime();
	double GetInitialTime();
	bool IsTherePath();
	bool IsTrajectoryCalculated();
        bool CalculateTrajectories();

        void Draw();

	void MoveRobotLinks(double time);

	bool SaveRobot();
	bool LoadRobot(string name);

private:
        // Vetor de double que na verdade representa uma matriz de 4x4 do frame da
        // posicao da base do robo
        double * m_base_position;
        // nome do robo
	string m_name;
        // Posicoes do Robo
	vector<RobotPosition *> m_robotpositions;
        // Links que compoem o Robo
	vector<Link *> m_links;
};

}

#endif
