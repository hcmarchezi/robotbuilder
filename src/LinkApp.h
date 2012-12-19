// LinkApp.h: interface for the LinkApp class.
//
//////////////////////////////////////////////////////////////////////

#include <qobject.h>
#include "WLinkTypeView.h"
#include "LinkType.h"

using namespace HIC;

namespace TMC
{

class LinkApp : public QObject
{
    Q_OBJECT
public:
	LinkApp(QWidget * parent,LinkType * linktype);
	virtual ~LinkApp();
	int Exec();

public slots:
	void LoadLinkType();
	void SaveLinkType();
	void ExcludeLinkType();
	void UpdateLinkType();
	void CreateLinkType();

private:
    WLinkTypeView * m_linktypewindow;
    LinkType      * m_linktype;

};

}

