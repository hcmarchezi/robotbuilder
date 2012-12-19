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
#include "AuxTextFile.h"

namespace DMC 
{

string AuxTextFile::GetParameterValue(ifstream & file,string parameter_name)
{
    // Temporary character buffer for each line read from file
    const int buffer_size = 1000;
    char buffer[buffer_size];
    memset(buffer,'\0',buffer_size);

    // Reads a line of characters from file
    file.getline(buffer,buffer_size);
    string parameter_value = buffer;

    // Removes carriage return from the end of the string
    parameter_value = parameter_value.substr(0,parameter_value.length()-1);

    // Remove the parameter name from the string line
    printf ("%s = %s\n",parameter_name.data(),parameter_value.data());

    if (parameter_value.find(parameter_name + " = ") >= 0)
    {
        int parameter_name_length = parameter_name.length()+3;
        int parameter_value_length = parameter_value.length();
        parameter_value = parameter_value.substr(parameter_name_length,parameter_value_length - parameter_name_length);
    }
    else
    {
        return NULL;
    }

    return parameter_value;
}

void AuxTextFile::GetParameterValue(ifstream & file, string parameter_name, double (* matrix)[4][4])
{
    // Temporary character buffer for each line read from file
    const int buffer_size = 1000;
    char buffer[buffer_size];
    memset(buffer,'\0',buffer_size);

    // Reads a line of characters from file
    file.getline(buffer,buffer_size);
    string parameter_value = buffer;

    // Finds the parameter name in the string line
    if (parameter_value.find(parameter_name + " =") >= 0)
    {
        file >> (*matrix)[0][0];
        file >> (*matrix)[0][1];
        file >> (*matrix)[0][2];
        file >> (*matrix)[0][3];

        file >> (*matrix)[1][0];
        file >> (*matrix)[1][1];
        file >> (*matrix)[1][2];
        file >> (*matrix)[1][3];

        file >> (*matrix)[2][0];
        file >> (*matrix)[2][1];
        file >> (*matrix)[2][2];
        file >> (*matrix)[2][3];

        file >> (*matrix)[3][0];
        file >> (*matrix)[3][1];
        file >> (*matrix)[3][2];
        file >> (*matrix)[3][3];

        file.getline(buffer,buffer_size);
    }
    else
    {
        return;
    }
}



}
