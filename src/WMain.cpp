// WMain.cpp: implementation of the WMain class.
//
//////////////////////////////////////////////////////////////////////

#include "WMain.h"
#include <qapplication.h>
#include <qmenubar.h>
#include <q3vbox.h>
#include <q3frame.h>
//Added by qt3to4:
#include <Q3PopupMenu>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HIC::WMain::WMain(const char * name):Q3MainWindow(0,name,Qt::WDestructiveClose)
{
    // Titulo da Janela
    setCaption(name);

    // Cria uma barra de menu
    m_menubar = new QMenuBar (this);
    m_menubar->setSeparator( QMenuBar::InWindowsStyle );
   
    // Cria o item de menu Link e seus itens
    m_menu_link = new Q3PopupMenu(this);
    m_menu_link->insertItem("New",1,1);
    m_menu_link->insertItem("Open",2,2);
    m_menu_link->insertItem("Save",3,3);
    m_menu_link->insertItem("Update",4,4);
    m_menu_link->insertItem("Exclude",5,5);

    // Cria o item de menu Robo e seus itens
    m_menu_robot = new Q3PopupMenu(this);
    m_menu_robot->insertItem("New",1,1);
    m_menu_robot->insertItem("Open",2,2);
    m_menu_robot->insertItem("Save",3,3);
    m_menu_robot->insertItem("Update",4,4);
    m_menu_robot->insertItem("Exclude",5,5);

    // Cria o item de menu Trajetoria e seus itens
    m_menu_trajectory = new Q3PopupMenu(this);
    m_menu_trajectory->insertItem("Calculate trajectory",1,1);
    m_menu_trajectory->insertItem("Animate robot",2,2);

    // Cria o iterm de menu Janela e seus itens
    m_menu_window = new Q3PopupMenu(this);
    m_menu_window->insertItem("Link Type",1,1);
    m_menu_window->insertItem("Robot Construction",2,2);
    m_menu_window->insertItem("Trajectory",3,3);

    // Insere menus na barra de menus
    m_menubar->insertItem("Link Type",m_menu_link);
    m_menubar->insertItem("Robot Construction",m_menu_robot);
    m_menubar->insertItem("Trajectory",m_menu_trajectory);
    m_menubar->insertItem("Windows",m_menu_window);

    // Cria um workspace onde as janelas de Link, Robo e Trajetoria estar�o
    Q3VBox * box = new Q3VBox(this);
    box->setFrameStyle( Q3Frame::StyledPanel | Q3Frame::Sunken );
    m_workspace = new QWorkspace(box);
    setCentralWidget(box);

}

