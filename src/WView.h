// WView.h: interface for the WView class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WVIEW_H
#define WVIEW_H

#include <qwidget.h>
#include <qlayout.h>
//Added by qt3to4:
#include <QHBoxLayout>
#include <QGLViewer/domUtils.h>
#include <QGLViewer/qglviewer.h>

#include "Robot.h"
#include "LinkType.h"
#include "GLObject.h"


using namespace PDC;

namespace HIC
{

class WView : public QWidget
{
    Q_OBJECT

public:
  GLObject * m_globjectwidget;
  WView(QWidget * parent,const char * name,GraphicObject * graphicobject);
  virtual ~WView();

public slots:
	bool close (bool alsoDelete);

protected:
  Q3HBoxLayout * m_layout_window;
};

}

#endif


