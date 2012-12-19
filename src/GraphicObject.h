/***************************************************************************
                          graphicobject.h  -  description
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

#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H


/**Classe abstrata puramente virtual que define uma interface para um objeto gr�fico tridimensional
  *@author humberto
  */

namespace PDC
{

class GraphicObject
{
public:
	GraphicObject();
	virtual ~GraphicObject();
  /** Esse m�todo deve ser implementado pelas classes filhas e cont�m as primitivas OpenGL de desenho para a visualiza��o do objeto. */
  virtual void Draw();
};

}

#endif
