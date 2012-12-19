/***************************************************************************
                          PersistentRevoluteLinkType.cpp  -  description
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

#include "PersistentRevoluteLinkType.h"

#include <fstream>
#include "RevoluteLinkType.h"

using namespace PDC;


DMC::PersistentRevoluteLinkType::PersistentRevoluteLinkType(RevoluteLinkType * revolutelinktype)
{
  m_revolutelinktype = revolutelinktype;  
}


DMC::PersistentRevoluteLinkType::~PersistentRevoluteLinkType()
{
  
}

// Salva osa dados do tipo de link de revolucao em arquivo. 
void DMC::PersistentRevoluteLinkType::Save (string filename)
{
  m_filename = filename;
  Update();  
}

// Recupera um tipo de link de revolucao de uma arquivo 
void * DMC::PersistentRevoluteLinkType::Retrieve (string filename)
{
	return PersistentLinkType::Retrieve(filename);
}

// Atualiza os dados de um tipo de link de revolucao no seu arquivo. 
void DMC::PersistentRevoluteLinkType::Update()
{
  // Abre o arquivo  
  ofstream file(m_filename.c_str());

  file << "NAME = " << m_revolutelinktype->GetLinkTypeName() << '\n';
  
  file << "SLIDE_TYPE = Revolute" << '\n';
    
  double local_coordinate_system[4][4];
  m_revolutelinktype->GetCoordinateSystem(&local_coordinate_system);

  file << "LOCAL_COORDINATE_SYSTEM = " << '\n';
  file << local_coordinate_system[0][0] << " ";
  file << local_coordinate_system[0][1] << " ";
  file << local_coordinate_system[0][2] << " ";
  file << local_coordinate_system[0][3] << " " << '\n';

  file << local_coordinate_system[1][0] << " ";
  file << local_coordinate_system[1][1] << " ";
  file << local_coordinate_system[1][2] << " ";
  file << local_coordinate_system[1][3] << " " << '\n';

  file << local_coordinate_system[2][0] << " ";
  file << local_coordinate_system[2][1] << " ";
  file << local_coordinate_system[2][2] << " ";
  file << local_coordinate_system[2][3] << " "<< '\n';

  file << local_coordinate_system[3][0] << " ";
  file << local_coordinate_system[3][1] << " ";
  file << local_coordinate_system[3][2] << " ";
  file << local_coordinate_system[3][3] << " " << '\n';

  file << "GEOMETRY_SOURCE = " << this->m_geometryfilename << '\n';
  file << "3D_OBJECT = " << this->m_geometricobject << '\n';

  file << "LINK_LENGTH = "   << m_revolutelinktype->GetLinkLength() << '\n';
  file << "LINK_TWIST  = "   << m_revolutelinktype->GetLinkTwist()  << '\n';
  file << "LINK_OFFSET = "  << m_revolutelinktype->GetLinkOffset() << '\n';
  file << "JOINT_ANGLE  = " << "\n";
  
  int iLinkFunction = m_revolutelinktype->GetLinkTypeFunction();
  
  if (iLinkFunction == 0)
  {
      file << "LINK_FUNCTION = BASE\n";
  }
  else if (iLinkFunction == 1)
  {
      file << "LINK_FUNCTION = LINK\n";
  }
  else if (iLinkFunction == 2)  
  {
	  file << "LINK_FUNCTION = TOOL\n";
  }  

  double lowest_movement, highest_movement;
  m_revolutelinktype->GetJointRestriction(lowest_movement,highest_movement);

  file << "LOWEST_MOVEMENT = " << lowest_movement  << '\n';
  file << "HIGHEST_MOVEMENT = "<< highest_movement << '\n';

  // Fecha o arquivo
  file.close(); 
}

// Remove o arquivo do tipo de link de revolucao. 
void DMC::PersistentRevoluteLinkType::Remove()
{
  
}

