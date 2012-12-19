                                                                     
                                                                     
                                                                     
                                             
// PersistentLinkType.cpp: implementation of the PersistentLinkType class.
//
//////////////////////////////////////////////////////////////////////

#include "PersistentLinkType.h"

#include "PrismaticLinkType.h"
#include "RevoluteLinkType.h"
#include "PersistentPrismaticLinkType.h"
#include "PersistentRevoluteLinkType.h"

#include <qstring.h>
#include <fstream>

#include <qmessagebox.h>

#include "tinyxml.h"
#include <cstdlib>
#include <qdir.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DMC::PersistentLinkType::PersistentLinkType()
{

}

DMC::PersistentLinkType::~PersistentLinkType()
{

}

// Salva o objeto em arquivo pela primeira vez
void DMC::PersistentLinkType::Save(string filename)
{
}

// Recupera um objeto de um arquivo retornando um
// endereco de memoria generico como void *
void * DMC::PersistentLinkType::Retrieve(string filename)
{
    // Reads XML File
    TiXmlDocument document(filename.c_str());
    if (!document.LoadFile())
    {
        return NULL;
    }

    // Reads XML root node
    TiXmlNode * link_type_node = document.FirstChild("link_type");	

    // Extracting property <name> value
    TiXmlElement * name_element = link_type_node->FirstChildElement("name");
    if (!name_element) { return NULL; }
    string name = name_element->GetText();
	
    // Extracting property <slide_type> value
    TiXmlElement * slide_type_element = link_type_node->FirstChildElement("slide_type");
    if (!slide_type_element) { return NULL; }
    string slide_type = slide_type_element->GetText();
    
    // Extracting Local Coordinate System ( position + orientation )
    double coordinate[4][4];
    TiXmlElement * local_coordinate_system_element = link_type_node->FirstChildElement("local_coordinate_system");
    if (!local_coordinate_system_element) { return NULL; }
    TiXmlElement * cell_element = local_coordinate_system_element->FirstChildElement();

    while(cell_element != NULL)
    {
        string strRow =  cell_element->Attribute("row");
        int row    = atoi(strRow.c_str());

        string strColumn = cell_element->Attribute("column");
        int column = atoi(strColumn.c_str());

        string strValue = cell_element->GetText();
        double value = strtod(strValue.c_str(),NULL);
        coordinate[row][column] = value;
        	
        cell_element = cell_element->NextSiblingElement();
    }

    // Extracting 3DS file and object id
    TiXmlNode * geometry_source_node = link_type_node->FirstChild("geometry_source");
    if (!geometry_source_node) { return NULL; }
    TiXmlElement * file_element = geometry_source_node->FirstChildElement("file");
    if (!file_element) { return NULL; }
    string geometry_source = file_element->GetText();
    TiXmlElement * objec_id_element = geometry_source_node->FirstChildElement("object_id");
    if (!objec_id_element) { return NULL; }
    string geometric_object = objec_id_element->GetText();

    // Extracting Denavit Hartemberg Parameters for the link type
    TiXmlNode * denavit_hartemberg_node = link_type_node->FirstChild("denavit_hartemberg_parameters");
    if (!denavit_hartemberg_node) { return NULL; }
  
    double link_length = 0.0;
    TiXmlElement * link_length_element = denavit_hartemberg_node->FirstChildElement("link_length");
    if (!link_length_element) { return NULL; }
    link_length = strtod(link_length_element->GetText(),NULL);

    double link_twist = 0.0;
    TiXmlElement * link_twist_element = denavit_hartemberg_node->FirstChildElement("link_twist");
    if (!link_twist_element) { return NULL; }
    link_twist = strtod(link_twist_element->GetText(),NULL);
    
    double link_offset = 0.0;
    TiXmlElement * link_offset_element = denavit_hartemberg_node->FirstChildElement("link_offset");
    if (!link_offset_element) { return NULL; }
    link_offset = strtod(link_offset_element->GetText(),NULL);

    double joint_angle = 0.0;
    TiXmlElement * joint_angle_element = denavit_hartemberg_node->FirstChildElement("joint_angle");
    if (!joint_angle_element) { return NULL; }
    link_offset = strtod(joint_angle_element->GetText(),NULL); 

    // Extracting link function 
    TiXmlElement * link_function_element = link_type_node->FirstChildElement("link_function");
    if (!link_function_element) { return NULL; }
    string link_function = link_function_element->GetText();

    // Movement Restrictions - Lowest and Highest Movement
    TiXmlNode * movement_restriction_node = link_type_node->FirstChild("movement_restriction");
    if (!movement_restriction_node) { return NULL; }
    
    double lowest_movement = 0.0;
    TiXmlElement * lowest_movement_element = movement_restriction_node->FirstChildElement("lowest_movement");
    if (!lowest_movement_element) { return NULL; }
    lowest_movement = strtod(lowest_movement_element->GetText(),NULL);

    double highest_movement = 0.0;
    TiXmlElement * highest_movement_element = movement_restriction_node->FirstChildElement("highest_movement");
    if (!highest_movement_element) { return NULL; }
    highest_movement = strtod(highest_movement_element->GetText(),NULL);
    
    
    





//     // Processo de Leitura do arquivo
//     char character = '\0';
//     string strline;
// 
// 	// Abre o arquivo informado
//     ifstream file(filename.data());
// 
//     // Nome do Tipo de Link
//     string name;
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
//     
//     printf ("NAME = %s\n",name.data());
//     if (strline.find("NAME = ") >= 0)
//     {
//         name = strline.substr(7,strline.size() - 7);
//     }
// 
//     // Tipo de deslizamento da junta
//     string slide_type; // Prismatic/Revolute
//     strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
//     if (strline.find("SLIDE_TYPE = ") >= 0)
//     {
//         slide_type = strline.substr(13,strline.size()-13);
//     }
// 
//     // Sistema de Coordenadas Local
//     double coordinate[4][4];
//     strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
//     if (strline.find("LOCAL_COORDINATE_SYSTEM = ") >= 0)
//     {
//         file >> coordinate[0][0];
//         file >> coordinate[0][1];
//         file >> coordinate[0][2];
//         file >> coordinate[0][3];
// 
//         file >> coordinate[1][0];
//         file >> coordinate[1][1];
//         file >> coordinate[1][2];
//         file >> coordinate[1][3];
// 
//         file >> coordinate[2][0];
//         file >> coordinate[2][1];
//         file >> coordinate[2][2];
//         file >> coordinate[2][3];
// 
//         file >> coordinate[3][0];
//         file >> coordinate[3][1];
//         file >> coordinate[3][2];
//         file >> coordinate[3][3];
// 
// 		file.get(character);
//     }
// 
//     // Fonte de Geometria
//     string geometry_source; // Arquivo 3DS
//     strline = "";
// 
// 	while ((!file.eof())&&(strline.size()==0))
// 	{	
// 		do
// 		{
// 			file.get(character);
// 			if (character != '\n') strline = strline + character;	
// 		}
// 		while ((character != '\n'));   
// 	}
// 	
// 
//     if (strline.find("GEOMETRY_SOURCE = ") >= 0)
//     {
//         geometry_source = strline.substr(18,strline.size()-18);
//     }
// 
// 	// Nome do Objeto 3D
// 	string geometric_object; // Arquivo 3DS
//     strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
//     if (strline.find("3D_OBJECT = ") >= 0)
//     {
//         geometric_object = strline.substr(12,strline.size()-12);
//     }
// 
//     // Comprimento do Tipo de Link
//     double link_length;
//     strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
//     if (strline.find("LINK_LENGTH = ") >= 0)
//     {
//         link_length = QString(strline.substr(14,strline.size()-14).data()).toDouble();
//     }
// 
//     // Torcao do Tipo de Link
//     double link_twist;
//     strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
//     if (strline.find("LINK_TWIST = ") >= 0)
//     {
// 		link_twist = QString(strline.substr(13,strline.size()-13).data()).toDouble();
//     }
// 
// 	// Deslocamento da junta
// 	double link_offset = 0.0;
// 	strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
//     if ((strline.find("LINK_OFFSET = ") >= 0)&&(strline.size()>14))
//     {
//         link_offset = QString(strline.substr(14,strline.size()-14).data()).toDouble();
//     }
// 
//     // Angulo da junta 
//     double joint_angle = 0.0;    
//     strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
// 	if ((strline.find("JOINT_ANGLE = ") >=0 )&&(strline.size()>14))
//     {
//         joint_angle = QString(strline.substr(14,strline.size()-14).data()).toDouble();
//     }
// 
// 	// Funcao do Tipo de Link
//     string    link_function;
//     strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
//     if (strline.find("LINK_FUNCTION = ") >= 0)
//     {
//         link_function = strline.substr(16,strline.size()-16);
//     }
// 
//     // Menor movimento possivel (angulo ou deslocamento conforme o tipo de deslizamento acima)
//     double lowest_movement;
//     strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );         
//     if (strline.find("LOWEST_MOVEMENT = ") >= 0)
//     {
//         lowest_movement = QString(strline.substr(18,strline.size()-18).data()).toDouble();
//     }
// 
//     // Maior movimento possivel (angulo ou deslocamento conforme o tipo de deslizamento acima)
//     double highest_movement;
//     strline = "";
// 	do
// 	{
// 		file.get(character);
//         if (character != '\n') strline = strline + character;	
// 	}
// 	while ( (!file.eof()) && (character != '\n') );        
//     if (strline.find("HIGHEST_MOVEMENT = ") >= 0)
//     {
//         highest_movement = QString(strline.substr(19,strline.size()-19).data()).toDouble();
//     }
// 
//     // Fecha o arquivo
//     file.close();


	//////////////// Passando os dados do arquivo para o tipo de link /////////////

	LinkType * linktype;

	// Instancia o tipo de link correto dependendo do tipo de deslizamento de junta
	if (slide_type == "prismatic")
	{
		linktype = new PrismaticLinkType();
	}
	else if (slide_type == "revolute")
	{
		linktype = new RevoluteLinkType();
	}
	// Se nao for nem Prismatico e nem de Revolucao, exibe uma mensagem
	else
	{
		//QMessageBox::critical( this->m_linktypewindow,"Erro","Arquivo que contem a geometria nao foi informado");
		return NULL;
	}

	// Seta os dados para o tipo de link
	linktype->SetLinkTypeName(name);
	linktype->SetCoordinateSystem(coordinate);
	linktype->LoadGeometry(geometry_source,geometric_object);
	linktype->SetLinkLength(link_length);
	linktype->SetLinkTwist(link_twist);
	
	// Seta o nome do arquivo para a camada de persistencia do objeto
	linktype->m_persistentlinktype->m_filename = filename;
	
	// Seta o parametro fixo restante dependendo do tipo de link criado
	if (slide_type == "Prismatic")
	{
		((PrismaticLinkType*)linktype)->SetJointAngle(joint_angle);
	}
	else
	{
		((RevoluteLinkType*)linktype)->SetLinkOffset(link_offset);
	}

	// Seta a funcao do tipo de link
	if (link_function == "BASE")
	{
		linktype->SetLinkTypeFunction(0);
	}
	else if (link_function == "LINK")
	{
		linktype->SetLinkTypeFunction(1);
	}
	else if (link_function == "TOOL")
	{
		linktype->SetLinkTypeFunction(2);
	}
	else
	{
		//QMessageBox::critical( linktypewindow,"Erro","Funcao de tipo de link nï¿½o esta entre (BASE, LINK ou TOOL");
		delete linktype;
		return NULL;
	}

	// Seta a restricao de movimento do tipo de link
	linktype->SetJointRestriction(lowest_movement,highest_movement);	

	return (void*)linktype;
}

// Registra as alteracoes do objeto em um arquivo
void DMC::PersistentLinkType::Update()
{
}

// Apaga o arquivo do objeto
void DMC::PersistentLinkType::Remove()
{
}

// Verifica se o objeto a fazer a persistencia ja tem o nome do arquivo
bool DMC::PersistentLinkType::hasFileName()
{
	return (this->m_filename.size() > 0);
}

// Atribui o nome do arquivo que contem a informacao geometrica
void   DMC::PersistentLinkType::SetGeometryFileName(string geometryfilename)
{
	this->m_geometryfilename = geometryfilename;
}

// Obtem o nome do arquivo que contem a informacao geometrica
string DMC::PersistentLinkType::GetGeometryFileName()
{
	return this->m_geometryfilename;
}

// Atribui o nome do objecto 3D que contem a informacao geometrica no arquivo
void   DMC::PersistentLinkType::SetGeometricObject(string geometricobject)
{
	this->m_geometricobject = geometricobject;
}

// Obtem o nome do objecto 3D que contem a informacao geometrica no arquivo
string DMC::PersistentLinkType::GetGeometricObject()
{
	return this->m_geometricobject;
}


