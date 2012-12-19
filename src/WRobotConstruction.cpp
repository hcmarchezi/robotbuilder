// WRobotConstruction.cpp: implementation of the WRobotConstruction class.
//
//////////////////////////////////////////////////////////////////////

#include "WRobotConstruction.h"

#include <qpushbutton.h>
//Added by qt3to4:
#include <Q3VBoxLayout>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HIC::WRobotConstruction::WRobotConstruction(QWidget * parent,const char * name,Robot * robot):WView(parent,name,robot)
{
    // Cria os bot�es (widgets) da janela 
    m_bt_createrobot     = new QPushButton("New Robot",this,"bt_createrobot");
    m_bt_updaterobot     = new QPushButton("Update Robot",this,"bt_updaterobot");
    m_bt_excluderobot    = new QPushButton("Remove Robot",this,"bt_excluderobot");
    m_bt_loadrobot       = new QPushButton("Load Robot",this,"bt_loadrobot");
    m_bt_saverobot       = new QPushButton("Save Robot",this,"bt_saverobot");

    m_bt_addlink         = new QPushButton("Add Link",this,"bt_addlink");
    m_bt_updatelink      = new QPushButton("Modify Link Position",this,"bt_updatelink");
    m_bt_removelink      = new QPushButton("Remove Link",this,"bt_removelink");

    // Layout dos bot�es em vertical
    m_layout_button = new Q3VBoxLayout (10,"layout_button");
    m_layout_button->addWidget(m_bt_createrobot);
    m_layout_button->addWidget(m_bt_updaterobot);
    m_layout_button->addWidget(m_bt_excluderobot);
    m_layout_button->addWidget(m_bt_loadrobot);
    m_layout_button->addWidget(m_bt_saverobot);
    m_layout_button->addWidget(m_bt_addlink);
    m_layout_button->addWidget(m_bt_updatelink);
    m_layout_button->addWidget(m_bt_removelink);

    // Organiza com o layout da janela
    m_layout_window->addLayout(m_layout_button);

}

HIC::WRobotConstruction::~WRobotConstruction()
{

}
