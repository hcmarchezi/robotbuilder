/***************************************************************************
                          PersistentObject.cpp  -  description
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

#include "PersistentObject.h"

DMC::PersistentObject::PersistentObject()
{

}

DMC::PersistentObject::~PersistentObject()
{

}


void DMC::PersistentObject::Save(string filename)
{

}


// Recupera um objeto de um arquivo retornando um
// endereco de memoria generico como void *
void * DMC::PersistentObject::Retrieve(string filename)
{
  return 0;
}

// Registra as alteracoes do objeto em um arquivo
void DMC::PersistentObject::Update()
{

}


// Apaga o arquivo do objeto
void DMC::PersistentObject::Remove()
{

}

// Obtem o nome do arquivo do objeto de persistencia
string DMC::PersistentObject::GetFileName()
{
	return this->m_filename;
}

// Atribui o nome do arquivo no objeto de persistencia
void DMC::PersistentObject::SetFileName(string filename)
{
	this->m_filename = filename;
}


