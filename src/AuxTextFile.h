/***************************************************************************
 *   Copyright (C) 2008 by Humberto C Marchezi   *
 *   hcmarchezi@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef DMCAUXTEXTFILEREADER_H
#define DMCAUXTEXTFILEREADER_H

#include <string>
#include <fstream>

using namespace std;

namespace DMC {

/**
	@author Humberto C Marchezi <hcmarchezi@gmail.com>
*/
class AuxTextFile
{
public: static string GetParameterValue(ifstream & file,string parameter_name);
public: static void GetParameterValue(ifstream & file, string parameter_name, double (* matrix)[4][4]);
};

}

#endif
