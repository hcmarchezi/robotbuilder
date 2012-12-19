// WLinkTypeView.cpp: implementation of the WLinkTypeView class.
//
//////////////////////////////////////////////////////////////////////

#include "WLinkTypeView.h"

#include <qpushbutton.h>
//Added by qt3to4:
#include <Q3VBoxLayout>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HIC::WLinkTypeView::WLinkTypeView(QWidget * parent,const char * name,LinkType * linktype):WView(parent,name,(LinkType *)linktype)
{
    // Create windows buttons
    m_bt_createlinktype     = new QPushButton("Create New Link",this,"bt_createlinktype");
    m_bt_updatelinktype  = new QPushButton("Modify Link",this,"bt_updatelinktype");
    m_bt_excludelinktype = new QPushButton("Remove Link",this,"bt_excludelinktype");
    m_bt_loadlinktype      = new QPushButton("Load Link",this,"bt_loadlinktype");
    m_bt_savelinktype       = new QPushButton("Save Link",this,"bt_savelinktype");

    // Vertical Layout for Buttons
    m_layout_button = new Q3VBoxLayout (10,"WLinkTypeView::layout_button");
    m_layout_button->addWidget(m_bt_createlinktype);
    m_layout_button->addWidget(m_bt_updatelinktype);
    m_layout_button->addWidget(m_bt_excludelinktype);
    m_layout_button->addWidget(m_bt_loadlinktype);
    m_layout_button->addWidget(m_bt_savelinktype);
    // fixed size layout
    m_layout_button->setResizeMode(QLayout::SetFixedSize);

    // Organiza com o layout da janela
    m_layout_window->addLayout(m_layout_button);
    //m_layout_window->setResizeMode(QLayout::Fixed);
}

HIC::WLinkTypeView::~WLinkTypeView()
{

}

