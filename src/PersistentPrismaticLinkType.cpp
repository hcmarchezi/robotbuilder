/***************************************************************************
                          PersistentPrismaticLinkType.cpp  -  description
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

#include "PersistentPrismaticLinkType.h"

#include <fstream>
#include "PrismaticLinkType.h"


DMC::PersistentPrismaticLinkType::PersistentPrismaticLinkType(PrismaticLinkType * prismaticlinktype)
{
    m_prismaticlinktype = prismaticlinktype;
}


DMC::PersistentPrismaticLinkType::~PersistentPrismaticLinkType()
{
  
}

// Salva o tipo de link prismatico em arquivo. 
void DMC::PersistentPrismaticLinkType::Save (string filename)
{
  // Armazena o nome do arquivo
  m_filename = filename;
  // Chama o metodo de atualizacao de dados
  Update();
}

// Recupera o um tipo de link prismatico do arquivo especificado. 
void * DMC::PersistentPrismaticLinkType::Retrieve (string filename)
{
	return PersistentLinkType::Retrieve(filename);
}

// Atualiza as informacoes do tipo de lnk em arquivo. 
void DMC::PersistentPrismaticLinkType::Update()
{
  // Abre o arquivo  
  ofstream file(m_filename.c_str());

  file << "NAME = " << m_prismaticlinktype->GetLinkTypeName() << '\n';
  
  file << "SLIDE_TYPE = Prismatic" << '\n';
    
  double local_coordinate_system[4][4];
  m_prismaticlinktype->GetCoordinateSystem(&local_coordinate_system);

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

  file << "LINK_LENGTH = "   << m_prismaticlinktype->GetLinkLength() << '\n';
  file << "LINK_TWIST  = "   << m_prismaticlinktype->GetLinkTwist()  << '\n';
  file << "LINK_OFFSET = \n";
  file << "JOINT_ANGLE  = "  << m_prismaticlinktype->GetJointAngle() << '\n';
  
  long lLinkFunction = m_prismaticlinktype->GetLinkTypeFunction();
  
  if (lLinkFunction == 0)
  {
      file << "LINK_FUNCTION = BASE\n";
  }
  else if (lLinkFunction == 1)
  {
      file << "LINK_FUNCTION = LINK\n";
  }
  else if (lLinkFunction == 2)  
  {
	  file << "LINK_FUNCTION = TOOL\n";
  }  

  double lowest_movement, highest_movement;
  m_prismaticlinktype->GetJointRestriction(lowest_movement,highest_movement);

  file << "LOWEST_MOVEMENT = " << lowest_movement  << '\n';
  file << "HIGHEST_MOVEMENT = "<< highest_movement << '\n';

  // Fecha o arquivo
  file.close(); 
}

// Remove o arquivo de um tipo de link. 
void DMC::PersistentPrismaticLinkType::Remove()
{
  
}

