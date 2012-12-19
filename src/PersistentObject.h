/***************************************************************************
                          PersistentObject.h  -  description
                             -------------------
    begin                : Sat Oct 18 2003
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

#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <string>

using namespace std;


/**
  *@author humberto
  */

namespace DMC
{

//	Esta é a classe persistente basica especializada em salvar os objetos
//	em arquivos.
//	Todas as classes que herdarem dela devem obrigatoriamente implementar
//	os metodos indicados como virtuais.
class PersistentObject
{

protected:
  string m_filename; // Nome do arquivo onde o objeto será salvo

public: 
	PersistentObject();
	virtual ~PersistentObject();
	// Salva o objeto em arquivo pela primeira vez
	virtual void Save(string filename);
	// Recupera um objeto de um arquivo retornando um
	// endereco de memoria generico como void *
	static void * Retrieve(string filename);
	// Registra as alteracoes do objeto em um arquivo
	virtual void Update();
	// Apaga o arquivo do objeto
	virtual void Remove();
	// Obtem o nome do arquivo
	string GetFileName();
	// Atribui o nome do arquivo
	void SetFileName(string filename);

};

}

#endif
