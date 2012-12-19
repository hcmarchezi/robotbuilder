// WRobotConstruction.h: interface for the WRobotConstruction class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WROBOTCONSTRUCTION_H
#define WROBOTCONSTRUCTION_H


#include "WView.h"
#include <qpushbutton.h>
//Added by qt3to4:
#include <Q3VBoxLayout>

namespace HIC
{

class WRobotConstruction : public WView  
{
    Q_OBJECT

public:
    // Botões (widgets) da janela
    QPushButton * m_bt_createrobot;
    QPushButton * m_bt_updaterobot;
    QPushButton * m_bt_excluderobot;
    QPushButton * m_bt_loadrobot;
    QPushButton * m_bt_saverobot;
    QPushButton * m_bt_addlink;
    QPushButton * m_bt_updatelink;
    QPushButton * m_bt_removelink ;
    // Layout dos botões em vertical
    Q3VBoxLayout * m_layout_button;

	WRobotConstruction(QWidget * parent,const char * name,Robot * robot);
	virtual ~WRobotConstruction();

public slots:

private:

};

}

#endif

