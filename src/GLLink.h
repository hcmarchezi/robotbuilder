/***************************************************************************
                          gllink.h  -  description
                             -------------------
    begin                : Wed Jan 29 2003
    copyright            : (C) 2003 by humberto
    email                : humberto@localhost.localdomain
 ***************************************************************************/

#ifndef GLLINK_H
#define GLLINK_H

#include <qobject.h>
#include "Link.h"
#include "GLObject.h"

using namespace PDC;

namespace HIC
{

class GLLink : public QObject
{
Q_OBJECT

public:
	GLLink(Link * link,GLObject * globject);
	~GLLink();
public slots:
  void setLinkMovement (double movement);
private:
    Link * m_link;
    GLObject * m_globject;
};

}

#endif
