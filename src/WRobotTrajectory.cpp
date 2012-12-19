// WRobotTrajectory.cpp: implementation of the WRobotTrajectory class.
//
//////////////////////////////////////////////////////////////////////

#include "WRobotTrajectory.h"

#include <qpushbutton.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <QFocusEvent>
#include <QLabel>
#include "Robot.h"
//#include <qinputdialog.h>
//#include <time.h>
//#include <qmessagebox.h>
#include <stdio.h>

//#include "GLRobot.h"

#include "QHSpinBox.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HIC::WRobotTrajectory::WRobotTrajectory(QWidget * parent,const char * name):WView(parent,name,NULL)
{
    //m_robot = robot;
    int i; //contador de loop
    char str_label[20]; // label do controle

   // Cria os bot�es (widgets) da janela
    m_bt_addposition     = new QPushButton("Add Position",this,"bt_addposition");
    m_bt_updateposition  = new QPushButton("Modify Position",this,"bt_updateposition");
    m_bt_excludeposition = new QPushButton("Remove Position",this,"bt_excludeposition");
    m_bt_animate         = new QPushButton("Animate Robot",this,"bt_animate");

    m_labeltitle = new QLabel("Robot Joints",this,"labeltitle");

    // Layout dos bot�es em vertical
    m_layout_controls = new Q3VBoxLayout (10,"layout_controls_2");
    m_layout_controls->addWidget(m_labeltitle);

    // O numero de spinboxes ira ate um maximo de 20 links
	// entretanto inicialmente eles estarai invisiveis na tela ate que 
	// algum link seja adicionado, dai o seu correspondente spinbox 
	// aparecera na tela tamb�m
	for (i=0; i < 100; i++)
	{
		sprintf(str_label,"teta %i (Radian)",i);
        m_lb_joint_list.push_back(new QLabel (str_label,this));
		m_layout_controls->addWidget(m_lb_joint_list[i]);
		m_lb_joint_list[i]->hide();

        sprintf(str_label,"spinjoint%i",i);
        m_spbx_joint_list.push_back(new QHSpinBox (-3.14,3.14,0.0,0.1,this,str_label));
		m_layout_controls->addWidget(m_spbx_joint_list[i]);
		m_spbx_joint_list[i]->hide();			
	}

	//if (robot != NULL)
	//{
	//
	//	for (i=0;i < robot->SizeLink() - 1; i++) 
	//	{
	//		m_lb_joint_list[i]->show();
	//		m_spbx_joint_list[i]->show();
	//		QObject::connect(m_spbx_joint_list[i],SIGNAL(valueChanged(double)),m_gllink_list[i],SLOT(setLinkMovement(double)) );
	//	}
	//
	//}

    m_layout_controls->addWidget(m_bt_addposition);
    m_layout_controls->addWidget(m_bt_updateposition);
    m_layout_controls->addWidget(m_bt_excludeposition);
    m_layout_controls->addWidget(m_bt_animate);
   	
	// Organiza com o layout da janela
    m_layout_window->addLayout(m_layout_controls);	
}

HIC::WRobotTrajectory::~WRobotTrajectory()
{
}

/** Atualiza os controles das juntas da janela de acordo com o robo que foi construido. */
void HIC::WRobotTrajectory::UpdateRobotControls( )
{
	Robot * robot = (Robot*)this->m_globjectwidget->GetGraphicObject();

	if (robot != NULL)
	{
		int i = robot->SizeLink() - 2;

		for (int k=0; k < 100; k++)
		{
			QObject::disconnect(m_spbx_joint_list[k],0,0,0);
		}

		for (int k=0; k < i+1; k++)
		{
			m_lb_joint_list[k]->show();
			m_spbx_joint_list[k]->show();
			GLLink * glLink = new GLLink(robot->GetLink(k),m_globjectwidget);
			m_gllink_list.push_back(glLink);
			QObject::connect(m_spbx_joint_list[k],SIGNAL(valueChanged(double)),m_gllink_list[k],SLOT(setLinkMovement(double)) );
			m_spbx_joint_list[k]->setValue(robot->GetLink(k)->GetVariableLinkParam());
		}		
    }
}

void HIC::WRobotTrajectory::focusInEvent(QFocusEvent * focus)
{
	this->UpdateRobotControls();
}


