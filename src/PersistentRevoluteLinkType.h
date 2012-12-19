/***************************************************************************
                          PersistentRevoluteLinkType.h  -  description
                             -------------------
    begin                : Sun Oct 26 2003
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

#ifndef PERSISTENTREVOLUTELINKTYPE_H
#define PERSISTENTREVOLUTELINKTYPE_H

#include "PersistentLinkType.h"

namespace PDC
{
class RevoluteLinkType;
}

using namespace DMC;
using namespace PDC;
using namespace std;

/**
  *@author humberto
  */

namespace DMC
{  

class PersistentRevoluteLinkType : public PersistentLinkType
{
private:
  RevoluteLinkType * m_revolutelinktype; // Objeto tipo de link que sera persistido  
  
public: 
	PersistentRevoluteLinkType(RevoluteLinkType * revolutelinktype);
	~PersistentRevoluteLinkType();
  /** Atualiza os dados de um tipo de link de revolucao no seu arquivo. */
  void Update();
  /** No descriptions */
  static void * Retrieve (string filename);
  /** Salva osa dados do tipo de link de revolucao em arquivo. */
  void Save (string filename);
  /** Remove o arquivo do tipo de link de revolucao. */
  void Remove();
};

}

#endif
