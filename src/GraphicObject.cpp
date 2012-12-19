/***************************************************************************
                          graphicobject.cpp  -  description
                             -------------------
    begin                : Sat Oct 18 2003
    copyright            : (C) 2003 by humberto
    email                : humberto@localhost.localdomain
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/glu.h>

#include "GraphicObject.h"

PDC::GraphicObject::GraphicObject()
{

}

PDC::GraphicObject::~GraphicObject()
{

}

void PDC::GraphicObject::Draw()
{
     // Se vc ve linhas o método não sofreu override
     //glWiredTeapot(80.0);
     glBegin(GL_LINES);
        glVertex3f(-10.0f,-10.0f,0.0f);
        glVertex3f(10.0f,50.0f,0.0f);
        glVertex3f(50.0f,-20.0f,0.0f);
     glEnd();
}