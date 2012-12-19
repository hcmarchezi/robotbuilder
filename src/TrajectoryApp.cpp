// TrajectoryApp.cpp: implementation of the TrajectoryApp class.
//
//////////////////////////////////////////////////////////////////////

#include "TrajectoryApp.h"

#include <qinputdialog.h>
#include <qstring.h>
#include <qpushbutton.h>
#include "Robot.h"
#include <time.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include <stdio.h>
//#include "GLRobot.h"
//#include "GLLink.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMC::TrajectoryApp::TrajectoryApp(QWidget * parent, Robot * robot)
{
    bAnimation = false;
    m_robot = robot;
    m_robottrajectorywindow = new WRobotTrajectory(parent,"Trajectory");

    QObject::connect( m_robottrajectorywindow->m_bt_addposition,SIGNAL(clicked()),this,SLOT(AddRobotPosition()) );
    QObject::connect( m_robottrajectorywindow->m_bt_updateposition,SIGNAL(clicked()),this,SLOT(UpdateRobotPosition()) );
    QObject::connect( m_robottrajectorywindow->m_bt_excludeposition,SIGNAL(clicked()),this,SLOT(ExcludeRobotPosition()) );
    //QObject::connect( m_robottrajectorywindow->m_bt_calculate,SIGNAL(clicked()),this,SLOT(CalculateTrajectory()) );
    QObject::connect( m_robottrajectorywindow->m_bt_animate,SIGNAL(clicked()),this,SLOT(AnimateRobot()) );
}

TMC::TrajectoryApp::~TrajectoryApp()
{

}

void TMC::TrajectoryApp::AddRobotPosition()
{
	if (m_robot == NULL)
	{
		m_robot = (Robot*)this->m_robottrajectorywindow->m_globjectwidget->GetGraphicObject();
	}

	if (m_robot == NULL) return;

   RobotPosition * robotposition = m_robot->CaptureRobotPosition();
   bool ok = false;
   double instant;
   double velocity;

   // Solicita o instante de tempo da Posi�o de Rob
   instant = QInputDialog::getDouble("Robot Position","Inform robot position time instant",0.0,  0.0,  100.0  ,2,  &ok,  m_robottrajectorywindow,"double1");

   if (!ok) return;

   robotposition->SetInstantTime(instant);
    // Solicita que a velocidade de cada junta do rob
   for (long i = 0; i < m_robot->SizeLink()-1; i++)
   {
       ok = false;
       char * caption = new char[30];
       sprintf (caption,"Link Position %li ",i);
       velocity = QInputDialog::getDouble(caption,"Inform joint velocity", 0, 0, 1000, 2, &ok, m_robottrajectorywindow, "double2" );
       delete caption;

       if (!ok)
       {
           delete robotposition;
           return;
       }

       // Seta a velocidade da posi�o de Link
       robotposition->GetLinkPosition(i)->SetLinkVelocity(velocity);
   }
   // Adiciona a posicao de robo ao caminho
   m_robot->AddRobotPosition(robotposition);
   // Atualiza a trajetoria do robo
   m_robot->CalculateTrajectories();

}

void TMC::TrajectoryApp::UpdateRobotPosition()
{
	if (m_robot == NULL)
	{
		m_robot = (Robot*)this->m_robottrajectorywindow->m_globjectwidget->GetGraphicObject();
	}

	if (m_robot == NULL) return;

    QStringList lst;
    QString     res;
    long        i;

    for (i = 0;i < m_robot->SizeRobotPosition();i++)
    {
        QString item;
        item = QString::number(i) + "      time = ";
        item = item + QString::number(m_robot->GetRobotPosition(i)->GetInstantTime());

        lst << item;
    }

    if (i == 0) return;

    bool ok = false;
    /* Especialista seleciona uma posi�o de rob para ser exclu�a */
    res = QInputDialog::getItem("Robot Position Update","Select Robot Position", lst, 0, FALSE, &ok, m_robottrajectorywindow );

    if (!ok) return;

    // Extrai o nmero da Posi�o selecionada
    double num = ( (res.mid(0,3) ).stripWhiteSpace() ).toDouble(&ok);

    // Atualiza a descricao do Path
    m_robot->UpdateRobotPosition(m_robot->GetRobotPosition((long) num));
    // Atualiza a trajetoria do robo
    m_robot->CalculateTrajectories();
}

void TMC::TrajectoryApp::ExcludeRobotPosition()
{
	if (m_robot == NULL)
	{
		m_robot = (Robot*)this->m_robottrajectorywindow->m_globjectwidget->GetGraphicObject();
	}

	if (m_robot == NULL) return;

    QStringList lst;
   QString     res;
   long        i;

    for (i = 0;i < m_robot->SizeRobotPosition();i++)
    {
        QString item;
        item = QString::number(i) + "      time = ";
        item = item + QString::number(m_robot->GetRobotPosition(i)->GetInstantTime());
        lst << item;
    }

    if (i == 0) return;

    bool ok = false;

     /* Especialista seleciona uma posi�o de rob para ser exclu�a */
    res = QInputDialog::getItem("Remove Robot Position","Select Robot Position", lst, 0, FALSE, &ok, m_robottrajectorywindow );

    if (!ok) return;

    // Extrai o nmero da Posi�o selecionada
    double num = ( (res.mid(0,3) ).stripWhiteSpace() ).toDouble(&ok);

    // Remove uma posicao do Path do Robo
    m_robot->RemoveRobotPosition(m_robot->GetRobotPosition((long) num));
    // Calcula a trajetoria do Robo
    m_robot->CalculateTrajectories();

}

//void TrajectoryApp::CalculateTrajectory()
//{
//    m_robot->CalculateTrajectories();
//}

void TMC::TrajectoryApp::AnimateRobot()
{
	if (m_robot == NULL)
	{
		m_robot = (Robot*)this->m_robottrajectorywindow->m_globjectwidget->GetGraphicObject();
	}

	if (m_robot == NULL) return;

    counter = m_robot->GetInitialTime();

    for (counter = m_robot->GetInitialTime();counter < m_robot->GetFinalTime(); counter = counter + 0.1)
    {
        m_robot->MoveRobotLinks(counter);
        Wait();
        m_robottrajectorywindow->m_globjectwidget->updateGL();
    }
    return;
    bAnimation = true;
}

int TMC::TrajectoryApp::Exec()
{
    m_robottrajectorywindow->UpdateRobotControls();
    m_robottrajectorywindow->show();
    m_robottrajectorywindow->setFocus();
    return 0;
}

void TMC::TrajectoryApp::Wait()
{
  clock_t ticks1, ticks2;

  ticks1=clock();
  ticks2=ticks1;
  while((500.0*ticks2/CLOCKS_PER_SEC-500.0*ticks1/CLOCKS_PER_SEC)<1)
    ticks2=clock();
}

WRobotTrajectory * TMC::TrajectoryApp::getTrajectoryWindow()
{
	return this->m_robottrajectorywindow;
}
