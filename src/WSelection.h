/****************************************************************************
** Form interface generated from reading ui file 'wselection.ui'
**
** Created: Sun Nov 9 21:50:27 2003
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.1.1   edited Nov 21 17:40 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef WSELECTION_H
#define WSELECTION_H

#include <qvariant.h>
#include <qdialog.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3Frame>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <QLabel>

#include "LinkType.h"
#include <vector>
#include "GLObject.h"

using namespace std;
using namespace PDC;

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class Q3Frame;
class QLabel;
class QPushButton;
class Q3ListBox;

namespace HIC
{

class WSelection : public QDialog
{
    Q_OBJECT

public:
    WSelection( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    virtual ~WSelection();

    QLabel*             m_txt_visual;
    QPushButton*        m_bt_ok;
    QPushButton*        m_bt_cancel;
    Q3ListBox*           m_lstbx_linktypes;
    Q3Frame*             m_frame_linktyper;
    GLObject*           m_globjectwidget;

    vector<LinkType *>  m_linktypes; // Lista de Tipos de Link    
        
  /**  Retorna o tipo de link que foi selecionado. */
  static LinkType * GetLinkType(QWidget * parent,const char* name,vector<LinkType *> linktypes);
  /** Recebe um vetor de tipos de link para serem usados na montagem da janela. */
  void AddLinkTypes(vector<LinkType *> linktypes);
  /** Remove a lista de tipos de link */
  void ClearLinkTypes();
  /** Retorna a lista de tipos de link que esta armazenada na janela de selecao. */
  vector<LinkType *> ObterLinkTypes( );

protected:
    Q3GridLayout* WSelectionLayout;
    /** Tipo de link selecionado na janela */
    LinkType *   m_selectedlinktype;

protected slots:
    virtual void languageChange();
    /** Trata do evento de selecao de um item do list box. */
    void SelectedListBoxItem (int index);
    /** Trata do evneto de pressionar o botao ok */
    void ClickedOkButton();
    /** Trata do evento de pressionar ao botao cancel */
    void ClickedCancelButton();
};

}

#endif // WSELECTION_H
