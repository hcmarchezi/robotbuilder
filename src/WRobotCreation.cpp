/****************************************************************************
** Form implementation generated from reading ui file 'WRobotCreation.ui'
**
** Created: Mon Nov 1 13:59:49 2004
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "WRobotCreation.h"

#include <q3groupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <q3table.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <q3whatsthis.h>

/* 
 *  Constructs a WRobotCreation which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
HIC::WRobotCreation::WRobotCreation( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "WRobotCreation" );
    resize( 484, 222 ); 
    setProperty( "caption", tr( QString::fromUtf8( "Robot Information" ) ) );
	//setMininumSize( 484, 222 );
	setMaximumSize( 484, 222 );

    m_lb_name = new QLabel( this, "m_lb_name" );
    m_lb_name->setGeometry( QRect( 10, 10, 53, 20 ) ); 
    m_lb_name->setProperty( "text", tr( "Name" ) );

    m_edt_name = new QLineEdit( this, "m_edt_name" );
    m_edt_name->setGeometry( QRect( 60, 10, 230, 22 ) ); 

    m_grp_base = new Q3GroupBox( this, "m_grp_base" );
    m_grp_base->setGeometry( QRect( 10, 40, 460, 140 ) ); 
    m_grp_base->setProperty( "title", tr( QString::fromUtf8( "Base Position and Orientation" ) ) );

    m_tab_base = new Q3Table( m_grp_base, "m_tab_base" );
    m_tab_base->setGeometry( QRect( 10, 20, 440, 104 ) ); 
    m_tab_base->setProperty( "numRows", 4 );
    m_tab_base->setProperty( "numCols", 4 );
	m_tab_base->setText(0,0,"1");
	m_tab_base->setText(0,1,"0");
	m_tab_base->setText(0,2,"0");
	m_tab_base->setText(0,3,"0");
	m_tab_base->setText(1,0,"0");
	m_tab_base->setText(1,1,"1");
	m_tab_base->setText(1,2,"0");
	m_tab_base->setText(1,3,"0");
	m_tab_base->setText(2,0,"0");
	m_tab_base->setText(2,1,"0");
	m_tab_base->setText(2,2,"1");
	m_tab_base->setText(2,3,"0");
	m_tab_base->setText(3,0,"0");
	m_tab_base->setText(3,1,"0");
	m_tab_base->setText(3,2,"0");
	m_tab_base->setText(3,3,"1");

    m_bt_save = new QPushButton( this, "m_bt_save" );
    m_bt_save->setGeometry( QRect( 270, 190, 93, 26 ) ); 
    m_bt_save->setProperty( "text", tr( "Ok" ) );

    m_bt_cancel = new QPushButton( this, "m_bt_cancel" );
    m_bt_cancel->setGeometry( QRect( 370, 190, 93, 26 ) ); 
    m_bt_cancel->setProperty( "text", tr( "Cancel" ) );

	QObject::connect(this->m_bt_save,  SIGNAL(clicked()),this,SLOT(bt_save_clicked())   );
	QObject::connect(this->m_bt_cancel,SIGNAL(clicked()),this,SLOT(bt_cancel_clicked()) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
HIC::WRobotCreation::~WRobotCreation()
{
    // no need to delete child widgets, Qt does it all for us
}

// Verifica se o botao de salvar foi pressionado ou nao
bool HIC::WRobotCreation::IsSaved()
{
	return this->bSalved;
}

// Ao clicar no botao save, fecha a janela e sinaliza o salvamento
void HIC::WRobotCreation::bt_save_clicked()
{
	this->bSalved = true;
	this->close();
}

// Ao clicar no botao cancel fecha a janela e nao sinaliza salvamneto
void HIC::WRobotCreation::bt_cancel_clicked()
{
	this->bSalved = false;
	this->close();
}
