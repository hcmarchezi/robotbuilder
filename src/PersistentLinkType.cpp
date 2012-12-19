// PersistentLinkType.cpp: implementation of the PersistentLinkType class.
//
//////////////////////////////////////////////////////////////////////

#include "PersistentLinkType.h"

#include "PrismaticLinkType.h"
#include "RevoluteLinkType.h"
#include "PersistentPrismaticLinkType.h"
#include "PersistentRevoluteLinkType.h"

#include <qstring.h>
#include <qfileinfo.h>
#include <fstream>

#include <cstdlib>
#include "AuxTextFile.h"


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
    // Processo de Leitura do arquivo
    //char character = '\0';
    string strline;

    // Temporary character buffer for each line read from file
    const int buffer_size = 1000;
    char buffer[buffer_size];
        
    // Abre o arquivo informado
    ifstream file(filename.data());
	
    // Nome do Tipo de Link
    string name = AuxTextFile::GetParameterValue(file,"NAME");

    // Tipo de deslizamento da junta
    string slide_type = AuxTextFile::GetParameterValue(file,"SLIDE_TYPE"); // Prismatic/Revolute

    // Sistema de Coordenadas Local
    double coordinate[4][4]; 
    AuxTextFile::GetParameterValue(file,"LOCAL_COORDINATE_SYSTEM",&coordinate);
   
    // Fonte de Geometria
    string geometry_source = AuxTextFile::GetParameterValue(file,"GEOMETRY_SOURCE"); // Arquivo 3DS
    QFileInfo * qfileinfo = new QFileInfo(QString(geometry_source.c_str()));
    geometry_source = (qfileinfo->dirPath() + "/" + qfileinfo->fileName()).data();

    // Nome do Objeto 3D
    string geometric_object = AuxTextFile::GetParameterValue(file,"3D_OBJECT");  ; // Arquivo 3DS
 
    // Comprimento do Tipo de Link
    double link_length = strtod( AuxTextFile::GetParameterValue(file,"LINK_LENGTH").data() ,NULL );

    // Torcao do Tipo de Link
    double link_twist = strtod( AuxTextFile::GetParameterValue(file,"LINK_TWIST").data() ,NULL );

    // Deslocamento da junta
    double link_offset = strtod( AuxTextFile::GetParameterValue(file,"LINK_OFFSET").data() ,NULL );

    // Angulo da junta 
    double joint_angle = strtod( AuxTextFile::GetParameterValue(file,"JOINT_ANGLE").data() ,NULL );
    
    // Funcao do Tipo de Link
    string link_function = AuxTextFile::GetParameterValue(file,"LINK_FUNCTION");

    // Menor movimento possivel (angulo ou deslocamento conforme o tipo de deslizamento acima)
    double lowest_movement = strtod( AuxTextFile::GetParameterValue(file,"LOWEST_MOVEMENT").data() ,NULL );
 
    // Maior movimento possivel (angulo ou deslocamento conforme o tipo de deslizamento acima)
    double highest_movement = strtod( AuxTextFile::GetParameterValue(file,"HIGHEST_MOVEMENT").data() ,NULL );
  
    // Fecha o arquivo
    file.close();


	//////////////// Passando os dados do arquivo para o tipo de link /////////////

	LinkType * linktype;

	// Instancia o tipo de link correto dependendo do tipo de deslizamento de junta
	if (slide_type == "Prismatic")
	{
		linktype = new PrismaticLinkType();
	}
	else if (slide_type == "Revolute")
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
	linktype->m_persistentlinktype->SetFileName(filename);
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
		//QMessageBox::critical( linktypewindow,"Erro","Funcao de tipo de link n�o esta entre (BASE, LINK ou TOOL");
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


