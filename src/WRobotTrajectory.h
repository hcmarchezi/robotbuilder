// WRobotTrajectory.h: interface for the WRobotTrajectory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WROBOTTRAJECTORY_H
#define WROBOTTRAJECTORY_H

#include "WView.h"
#include <vector>
#include "QHSpinBox.h"
#include <qlabel.h>
//Added by qt3to4:
#include <QFocusEvent>
#include <Q3VBoxLayout>
#include "GLLink.h"
#include "GLObject.h"

namespace HIC
{

class WRobotTrajectory : public WView  
{
    Q_OBJECT

public:
    // Cria os botões (widgets) da janela
    QPushButton * m_bt_addposition;
    QPushButton * m_bt_updateposition;
    QPushButton * m_bt_excludeposition;
    QPushButton * m_bt_calculate;
    QPushButton * m_bt_animate;

	WRobotTrajectory(QWidget * parent,const char * name);
	virtual ~WRobotTrajectory();
  /** Atualiza os controles das juntas da janela de acordo com o robo que foi construido. */
  void UpdateRobotControls( );
  
public slots:

private: 
    Q3VBoxLayout * m_layout_controls;

    // Veotr de controles de juntas
    vector<QHSpinBox *>        m_spbx_joint_list;
    vector<QLabel *>           m_lb_joint_list;
    vector<GLLink *>           m_gllink_list;
    QLabel*                    m_labeltitle;

protected:
	void focusInEvent(QFocusEvent * focus);
};

}

#endif

