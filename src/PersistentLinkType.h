// PersistentLinkType.h: interface for the PersistentLinkType class.
//
//////////////////////////////////////////////////////////////////////

#ifndef PERSISTENTLINKTYPE_H
#define PERSISTENTLINKTYPE_H

#include "LinkType.h"

#include "PersistentObject.h"

namespace DMC
{

class PersistentLinkType : public PersistentObject  
{
public:
	PersistentLinkType();
	virtual ~PersistentLinkType();

	// Salva o objeto em arquivo pela primeira vez
	virtual void Save(string filename);
	// Recupera um objeto de um arquivo retornando um
	// endereco de memoria generico como void *
	static void * Retrieve(string filename);
	// Registra as alteracoes do objeto em um arquivo
	virtual void Update();
	// Apaga o arquivo do objeto
	virtual void Remove();
	// Verifica se possui o nome do arquivo
	bool hasFileName();
	
	// Atribui o nome do arquivo que contem a informacao geometrica
	void   SetGeometryFileName(string geometryfilename);
	// Obtem o nome do arquivo que contem a informacao geometrica
	string GetGeometryFileName();
	// Atribui o nome do objecto 3D que contem a informacao geometrica no arquivo
	void   SetGeometricObject(string geometricobject);
	// Obtem o nome do objecto 3D que contem a informacao geometrica no arquivo
	string GetGeometricObject();

protected:
	string m_geometricobject;	// Nome do objeto geometrico no arquivo que representa a geometria
	string m_geometryfilename;	// Nome do arquivo que tem a informacao geometrica
	LinkType * m_linktype;		// Referencia para o tipo de link
	
};

}

#endif 
