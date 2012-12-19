// WLinkTypeView.h: interface for the WLinkTypeView class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WLINKTYPEVIEW_H
#define WLINKTYPEVIEW_H

#include "WView.h"
#include <qpushbutton.h>
//Added by qt3to4:
#include <QVBoxLayout>

namespace HIC
{

class WLinkTypeView : public WView  
{
     Q_OBJECT
public:

    QPushButton * m_bt_createlinktype;
    QPushButton * m_bt_updatelinktype;
    QPushButton * m_bt_excludelinktype;
    QPushButton * m_bt_loadlinktype;
    QPushButton * m_bt_savelinktype;

    // Pushbuttons vertical layout
    Q3VBoxLayout * m_layout_button;

	//Construtor e Destrutor
    WLinkTypeView(QWidget * parent,const char * name,LinkType * linktype);
	virtual ~WLinkTypeView();
};

}

#endif


