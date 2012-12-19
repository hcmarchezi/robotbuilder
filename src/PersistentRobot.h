/***************************************************************************
                          PersistentRobot.h  -  description
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

#ifndef PERSISTENTROBOT_H
#define PERSISTENTROBOT_H

#include "PersistentObject.h"

namespace PDC
{
class Robot;
}

#include <string>

/**
  *@author humberto
  */

using namespace std;
using namespace PDC;
using namespace DMC;

namespace DMC
{
  
class PersistentRobot : public PersistentObject
{
private:
  Robot * m_robot;

public: 
	PersistentRobot(Robot * robot);
	~PersistentRobot();
	/** Atualiza os dados de um robo em um arquivo. */
	void Update();
	/** Salva os dados do robo em um arquivo. */
	void Save (string filename);
	/** Remove o arquivo de um robo. */
	void Remove();
	/** Recupera um robo através do nome de um arquivo. */
	static void * Retrieve (string filename);
};

}

#endif
