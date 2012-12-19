/***************************************************************************
                          PersistentPrismaticLinkType.h  -  description
                             -------------------
    begin                : Sat Oct 25 2003
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

#ifndef PERSISTENTPRISMATICLINKTYPE_H
#define PERSISTENTPRISMATICLINKTYPE_H

#include "PersistentLinkType.h"

namespace PDC
{
class PrismaticLinkType;
}

using namespace DMC;
using namespace PDC;
using namespace std;

/**
  *@author humberto
  */

namespace DMC
{

class PersistentPrismaticLinkType : public PersistentLinkType
{
private:    
	// Objeto tipo de link que sera persistido
	PrismaticLinkType * m_prismaticlinktype;   

public: 
	
	PersistentPrismaticLinkType(PrismaticLinkType * prismaticlinktype);
	~PersistentPrismaticLinkType();
	// Remove o arquivo de um tipo de link. 
	void Remove();
	// Atualiza as informacoes do tipo de lnk em arquivo. 
	void Update();
	// Recupera o um tipo de link prismatico do arquivo especificado. 
	static void * Retrieve (string filename);
	// Salva o tipo de link prismatico em arquivo. 
	void Save (string filename); 
};

}

#endif
