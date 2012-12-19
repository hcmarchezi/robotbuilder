// WMain.h: interface for the WMain class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WMAIN_H
#define WMAIN_H

#include <qworkspace.h>
#include <qmenubar.h>
//Added by qt3to4:
#include <QMenu>
#include <vector>
#include <qwidget.h>
#include <QMainWindow>
#include "LinkType.h"
#include "WLinkTypeView.h"
#include "WRobotConstruction.h"
#include "WRobotTrajectory.h"

using namespace std;
using namespace PDC;

namespace HIC
{

class WMain : public Q3MainWindow
{
    Q_OBJECT

public:
	WMain(const char * name);
//    QWorkspace * GetWorkspace();

//private:
    
    QMenuBar   * m_menubar;
    Q3PopupMenu * m_menu_link;
    Q3PopupMenu * m_menu_robot;
    Q3PopupMenu * m_menu_trajectory;
    Q3PopupMenu * m_menu_window;
    QWorkspace * m_workspace;

public slots:

};

}

#endif


