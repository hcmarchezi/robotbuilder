/***************************************************************************
                          gllink.cpp  -  description
                             -------------------
    begin                : Wed Jan 29 2003
    copyright            : (C) 2003 by humberto
    email                : humberto@localhost.localdomain
 ***************************************************************************/

#include "GLLink.h"

HIC::GLLink::GLLink(Link * link,GLObject * globject)
{
     m_globject = globject;
     m_link = link;
}

HIC::GLLink::~GLLink()
{

}

void HIC::GLLink::setLinkMovement (double movement)
{
	  m_link->SetVariableLinkParam (movement);
    m_globject->updateGL();
}
