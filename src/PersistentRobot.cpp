/***************************************************************************
                          PersistentRobot.cpp  -  description
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

#include "PersistentRobot.h"

#include "Robot.h"
#include "PersistentLinkType.h"

#include <fstream>
#include <qstring.h>

#include "AuxTextFile.h"

DMC::PersistentRobot::PersistentRobot(Robot * robot)
{
	m_robot = robot;  
}


DMC::PersistentRobot::~PersistentRobot()
{
  
}

/** Salva os dados do robo em um arquivo. */
void DMC::PersistentRobot::Save (string filename)
{
	this->m_filename = filename;
	this->Update();
}

/** Atualiza os dados de um robo em um arquivo. */
void DMC::PersistentRobot::Update()
{
	double localCoordinate[4][4];	

	this->m_robot->GetBasePosition(&localCoordinate);


	ofstream file(m_filename.c_str());

	file << "NAME = " << this->m_robot->GetRobotName() << "\n";
	file << "BASE_POSITION_ORIENTATION = " << "\n";
	file << localCoordinate[0][0] << " " << localCoordinate[0][1] << " " << localCoordinate[0][2] << " " << localCoordinate[0][3] << "\n";
	file << localCoordinate[1][0] << " " << localCoordinate[1][1] << " " << localCoordinate[1][2] << " " << localCoordinate[1][3] << "\n";
	file << localCoordinate[2][0] << " " << localCoordinate[2][1] << " " << localCoordinate[2][2] << " " << localCoordinate[2][3] << "\n";
	file << localCoordinate[3][0] << " " << localCoordinate[3][1] << " " << localCoordinate[3][2] << " " << localCoordinate[3][3] << "\n";

	file << "LINK_CHAIN = \n";
	
	PersistentLinkType * persistentLinkType;
	Link               * link;
	for (int i=0; i < this->m_robot->SizeLink(); i++)
	{
		persistentLinkType = this->m_robot->GetLink(i)->GetLinkType()->m_persistentlinktype;
		link               = this->m_robot->GetLink(i);

		file << persistentLinkType->GetFileName() << " " << link->GetVariableLinkParam() << "\n";
	}

	file << "ROBOT_PATH = \n";

	for (int j=0; j < this->m_robot->SizeRobotPosition(); j++)
	{
		file << this->m_robot->GetRobotPosition(j)->GetInstantTime() << "\n";
		for (int k=0; k < this->m_robot->SizeLink(); k++)
		{
			LinkPosition * linkposition = this->m_robot->GetRobotPosition(j)->GetLinkPosition(k);
			file << linkposition->GetLinkPositionMov() << " ";
			file << linkposition->GetLinkVelocity() << "\n";
		}
	}
	
	//file << 
		
	file.close();
}

/** Recupera um robo atrav�s do nome de um arquivo. */
void * DMC::PersistentRobot::Retrieve (string filename)
{
	// Processo de Leitura do arquivo
    char character = '\0';
    string strline;

	// Armazena o nome do arquivo
    

	//m_filename = filename;

    // opens text file
    ifstream file(filename.data());
	
    // Robot name parameter value from file
    string name = AuxTextFile::GetParameterValue(file,"NAME");

    // Sistema de Coordenadas Local
    double coordinate[4][4];
    AuxTextFile::GetParameterValue(file,"BASE_POSITION_ORIENTATION",&coordinate);

	// Cria o robo com os dados informados
	Robot * robot = new Robot();
	robot->SetRobotName(name);
	robot->SetBasePosition(coordinate);


    // Lendo os links que fazem parte do rob�
	strline = "";
	do
	{
		file.get(character);
        if (character != '\n') strline = strline + character;	
	}
	while ( (!file.eof()) && (character != '\n') );      
        
	if (strline.find("LINK_CHAIN = ") >= 0)
    {
		int linknumber = 0;

		while (!file.eof())
		{		
			// Le o nome do arquivo do tipo de link
			strline = "";
			do
			{
				file.get(character);
				if (character != '\n') strline = strline + character;	
			}
			while ( (!file.eof()) && (character != '\n') );      

			// Se achar a secao de posicao de link pula o arquivo
			if (strline.find("ROBOT_PATH")==0)
			{
				break;
			}

			string link_filename = strline.substr(0,strline.find(" "));

			// Le o valor da parametro movel
			double parametro_movel = QString(strline.substr(strline.find(" ")+1,strline.size()).data()).toDouble();

			// Carrega o tipo de link no computador
			LinkType * linktype = (LinkType*)PersistentLinkType::Retrieve(link_filename);

			// Se nao encontrou o tipo de link retorna nulo
			if (linktype == NULL)
			{
				delete robot;
				return NULL;
			}

			// Cria o link e insere no robo com o seu parametro variavel inicial
			Link * link = new Link(linktype);
			link->SetVariableLinkParam(parametro_movel);
			link->SetLinkNumber(linknumber++);
			robot->AddLink(link);
		}
		        
    }

	// Le a posicao dos links
	//if (strline.find("ROBOT_PATH")==0)
	//{
	//	while (!file.eof())
	//	{		
	//		// Le o nome do arquivo do tipo de link
	//		strline = "";
	//		do
	//		{
	//			file.get(character);
	//			if (character != '\n') strline = strline + character;	
	//		}
	//		while ( (!file.eof()) && (character != '\n') );      
	//	}
	//
	//}

	// Se fim de arquivo retorna nulo pois houver erro de leitura do arquivo
	if ((strline.find("ROBOT_PATH")==0)&&(file.eof()))
	{
		delete robot;
		return NULL;
	}

	// Le a descricao do caminho do robo	
	while (!file.eof())
	{	
		// Le o instante de tempo e cria uma nova posicao de robo
		double time_instant;
		file >> time_instant;
		RobotPosition * robotposition = new RobotPosition();
		robotposition->SetInstantTime(time_instant);
				
		// Le a posicao e a velocidade de cada link naquele instante
		for (int i=0; i < robot->SizeLink(); i++)
		{	
			// Guarda a posicao do link na posicao de link e 
			// adiciona na posicao de robo
			double link_position;
			double link_velocity;
			file >> link_position >> link_velocity;
			LinkPosition * linkposition = new LinkPosition(robot->GetLink(i));
			linkposition->SetLinkPositionMov(link_position);
			linkposition->SetLinkVelocity(link_velocity);
			robotposition->AddLinkPosition(linkposition);
		}

		// Insere no robo
		robot->AddRobotPosition(robotposition);	
	}

	robot->CalculateTrajectories();

	return robot;
}

/** Remove o arquivo de um robo. */
void DMC::PersistentRobot::Remove()
{
  
}

