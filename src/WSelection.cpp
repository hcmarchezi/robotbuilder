/****************************************************************************
** Form implementation generated from reading ui file 'wselection.ui'
**
** Created: Sun Nov 9 21:50:53 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.1.1   edited Nov 21 17:40 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "WSelection.h"

#include <qvariant.h>
#include <q3frame.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <q3listbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
#include <qstring.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <iostream>

/* 
 *  Constructs a WSelection as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
HIC::WSelection::WSelection( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )

{
    if ( !name ) 	setName( "WSelection" );
    
    WSelectionLayout = new Q3GridLayout( this, 1, 1, 11, 6, "WSelectionLayout"); 

    m_txt_visual = new QLabel( this, "m_txt_visual" );

    WSelectionLayout->addWidget( m_txt_visual, 0, 2 );

    m_bt_ok = new QPushButton( this, "m_bt_ok" );

    WSelectionLayout->addWidget( m_bt_ok, 2, 0 );

    m_bt_cancel = new QPushButton( this, "m_bt_cancel" );

    WSelectionLayout->addWidget( m_bt_cancel, 2, 1 );

    m_lstbx_linktypes = new Q3ListBox( this, "m_lstbx_linktypes" );

    WSelectionLayout->addMultiCellWidget( m_lstbx_linktypes, 1, 1, 0, 1 );

    m_frame_linktyper = new Q3Frame( this, "m_frame_linktyper" );
    m_frame_linktyper->setFrameShape( Q3Frame::StyledPanel );
    m_frame_linktyper->setFrameShadow( Q3Frame::Raised );

    WSelectionLayout->addMultiCellWidget( m_frame_linktyper, 1, 2, 2, 2 );
    languageChange();
    resize( QSize(728, 345).expandedTo(minimumSizeHint()) );

    
    QObject::connect (m_lstbx_linktypes,SIGNAL(selected(int)),this,SLOT(SelectedListBoxItem(int)) );

    //QObject::connect ( spinrotz,SIGNAL(valueChanged(double)),m_globjectwidget,SLOT(setZRotation(double)) );
    
    //QObject::connect(m_bt_ok,SIGNAL(clicked()),this,SLOT(ClickedOkButton()));
    //QObject::connect(m_bt_cancel,SIGNAL(clicked()),this,SLOT(ClickedCancelButton()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
HIC::WSelection::~WSelection()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void HIC::WSelection::languageChange()
{
    setCaption( tr( "Robotbuilder - Select a link type" ) );
    m_txt_visual->setText("Visualization");
    m_bt_ok->setText( tr( "Ok" ) );
    m_bt_cancel->setText( tr( "Cancel" ) );
}

/*
 * Abre uma janela de Dialogo para capturar o tipo de link selecionado
 * em grupo de tipos de link informados atravs de um vetor.
 */
LinkType * HIC::WSelection::GetLinkType(QWidget * parent,const char* name,vector<LinkType *> linktypes)
{
  // Cria uma janela para selecao de tipos de link
  WSelection * selectionwindow = new WSelection(parent,name,true,0);
  // Recebe a lista de tipos de link
  selectionwindow->AddLinkTypes(linktypes);
  // Mostra a janela
  selectionwindow->exec();
  
  // Retorna o tipo de link selecionado
  return selectionwindow->m_selectedlinktype;
}

/** Recebe um vetor de tipos de link para serem usados na montagem da janela. */
void HIC::WSelection::AddLinkTypes(vector<LinkType *> linktypes)
{
  m_linktypes = linktypes;
  // Mostra uma lista de tipos de link a escolher
  // Numero de linhas  o numero de elementos do vetor
  for (int i = 0; i < m_linktypes.size(); i++ )
  {
    QString linha;
    linha = QString(m_linktypes[i]->GetLinkTypeName().c_str());
    linha +=  " | ";
    switch (m_linktypes[i]->GetLinkTypeFunction())
    {
      case BASE:
      linha += "Base (Initial Link)";
      break;

      case ACTUATOR:
      linha += "Actuator (Middle Link)";
      break;

      case END_EFFECTOR:
      linha += "End Effector (Final Link)";
      break;
    }
    linha += " | Revolute Joint";
    // Insere o texto no listbox
    m_lstbx_linktypes->insertItem(linha,i);
  }

  // Cria o OpenGL Widget
  
  if (m_linktypes.size() > 0)
  {
     m_lstbx_linktypes->setCurrentItem(0);
     m_globjectwidget = new GLObject(m_frame_linktyper,"globjectwidget",m_linktypes[0]);
     m_globjectwidget->setMinimumSize(250,250);
     
  }
  

}

/** Remove uma lista de tipos de link */
void HIC::WSelection::ClearLinkTypes()
{
  m_linktypes.clear();
}


/** Retorna a lista de tipos de link que esta armazenada na janela de selecao. */
vector<LinkType *> HIC::WSelection::ObterLinkTypes()
{
  return m_linktypes;
}

/** Trata do evento de selecao de um item do list box. */
void HIC::WSelection::SelectedListBoxItem (int index)
{
    cout << " listbox click event";
    m_globjectwidget = new GLObject(m_frame_linktyper,"globjectwidget",m_linktypes[index]);
    m_globjectwidget->setMinimumSize(250,250);
}

/** Trata do evneto de pressionar o botao ok */
void HIC::WSelection::ClickedOkButton()
{
   /*
   m_selectedlinktype = m_linktypes[m_lstbx_linktypes->currentItem()];
   this->close();
   */
}

/** Trata do evento de pressionar ao botao cancel */
void HIC::WSelection::ClickedCancelButton()
{
    /*
    m_selectedlinktype = 0;
    this->close();
    */
}
