/****************************************************************************
** Form implementation generated from reading ui file 'WLinkTypeSelection.ui'
**
** Created: Wed Nov 3 12:34:16 2004
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "WLinkTypeSelection.h"

#include <q3groupbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
#include <q3filedialog.h>

/* 
 *  Constructs a WLinkTypeSelection which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
HIC::WLinkTypeSelection::WLinkTypeSelection( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "WLinkTypeSelection" );
    resize( 429, 141 ); 
    setProperty( "caption", tr( "Select a link type" ) );
	setMinimumSize( 429, 141 );

    m_grp_filename = new Q3GroupBox( this, "m_grp_filename" );
    m_grp_filename->setGeometry( QRect( 10, 0, 410, 80 ) ); 
    m_grp_filename->setProperty( "title", tr( "Select a link type file" ) );

    m_edt_filename = new QLineEdit( m_grp_filename, "m_edt_filename" );
    m_edt_filename->setGeometry( QRect( 10, 20, 390, 22 ) ); 

    m_bt_load = new QPushButton( m_grp_filename, "m_bt_load" );
    m_bt_load->setGeometry( QRect( 290, 50, 110, 26 ) ); 
    m_bt_load->setProperty( "text", tr( "Search file" ) );

    m_bt_cancel = new QPushButton( this, "m_bt_cancel" );
    m_bt_cancel->setGeometry( QRect( 320, 100, 93, 26 ) ); 
    m_bt_cancel->setProperty( "text", tr( "Cancel" ) );

    m_bt_add = new QPushButton( this, "m_bt_add" );
    m_bt_add->setGeometry( QRect( 220, 100, 93, 26 ) ); 
    m_bt_add->setProperty( "text", tr( "Add" ) );

    m_grp_linknumber = new Q3GroupBox( this, "m_grp_linknumber" );
    m_grp_linknumber->setGeometry( QRect( 10, 80, 190, 50 ) ); 
    m_grp_linknumber->setProperty( "title", tr( QString::fromUtf8( "Link position in robot" ) ) );

    m_edt_numlink = new QLineEdit( m_grp_linknumber, "m_edt_numlink" );
    m_edt_numlink->setGeometry( QRect( 10, 20, 70, 22 ) ); 
	m_edt_numlink->setText("0");

	// Liga o sinal dos botoes aos seus respectivo eventos
	QObject::connect(m_bt_add,   SIGNAL(clicked()), this,SLOT(bt_add_clicked()));
	QObject::connect(m_bt_cancel,SIGNAL(clicked()), this,SLOT(bt_add_clicked()));
	QObject::connect(m_bt_load,  SIGNAL(clicked()), this,SLOT(bt_load_clicked()));
}

/*  
 *  Destroys the object and frees any allocated resources
 */
HIC::WLinkTypeSelection::~WLinkTypeSelection()
{
    // no need to delete child widgets, Qt does it all for us
}

// Verifica se o botao adicionar foi pressionado
bool HIC::WLinkTypeSelection::IsAdded()
{
	return this->m_b_added;
}

// Trata o evento do botao adicionar ser pressionado
void HIC::WLinkTypeSelection::bt_add_clicked()
{
	this->m_b_added = true;
	this->close();
}

// Trata o evento do botao cancelar ser pressioando
void HIC::WLinkTypeSelection::bt_cancel_clicked()
{
	this->m_b_added = false;
	this->close();
}

// Trata do evento de selecionar um arquifvo de tipo de link para carregar
void HIC::WLinkTypeSelection::bt_load_clicked()
{
	QStringList lstFileName = Q3FileDialog::getOpenFileNames ( "*.linktype", ".", this, "Link type selection", "Select a link type file" );
	QStringList::Iterator it = lstFileName.begin()++;    
	if (it != lstFileName.end())
	{
		this->m_edt_filename->setText( (*it).latin1() );
	}
}


