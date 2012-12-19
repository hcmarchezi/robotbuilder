/****************************************************************************
** Form implementation generated from reading ui file 'WLinkTypeCreation.ui'
**
** Created: Thu Oct 28 11:58:42 2004
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "WLinkTypeCreation.h"

#include <qcombobox.h>
#include <q3groupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <q3table.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
#include <qmessagebox.h>
#include <q3filedialog.h>
#include <qstringlist.h>

#include <stdio.h>
#include <string>

/* 
 *  Constructs a WLinkTypeCreation which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
HIC::WLinkTypeCreation::WLinkTypeCreation( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "WLinkTypeCreation" );
    resize( 512, 455 ); 
    setProperty( "caption", tr( QString::fromUtf8( "New Link Type" ) ) );	
	setMaximumSize( 512, 455 );
	

    lbNome = new QLabel( this, "lbNome" );
    lbNome->setGeometry( QRect( 10, 10, 53, 20 ) ); 
    lbNome->setProperty( "text", tr( "Name:" ) );

    txtNome = new QLineEdit( this, "txtNome" );
    txtNome->setGeometry( QRect( 72, 10, 210, 22 ) ); 

    lbFuncao = new QLabel( this, "lbFuncao" );
    lbFuncao->setGeometry( QRect( 290, 10, 53, 20 ) ); 
    lbFuncao->setProperty( "text", tr( QString::fromUtf8( "Function" ) ) );

    lbTorcao = new QLabel( this, "lbTorcao" );
    lbTorcao->setGeometry( QRect( 250, 290, 53, 20 ) ); 
    lbTorcao->setProperty( "text", tr( QString::fromUtf8( "Twist" ) ) );

    grpGeometria = new Q3GroupBox( this, "grpGeometria" );
    grpGeometria->setGeometry( QRect( 10, 40, 490, 90 ) ); 
    grpGeometria->setProperty( "title", tr( "Geometry" ) );

    lbGeometria = new QLabel( grpGeometria, "lbGeometria" );
    lbGeometria->setGeometry( QRect( 30, 20, 110, 20 ) ); 
    lbGeometria->setProperty( "text", tr( "Geometry File" ) );

    txtGeometria = new QLineEdit( grpGeometria, "txtGeometria" );
    txtGeometria->setGeometry( QRect( 160, 20, 180, 22 ) ); 

	btSelecionarArquivo = new QPushButton("Search",this,"btSelecionarArquivo");
	btSelecionarArquivo->setGeometry( 350, 60, 50, 22);

	btCarregarGeometria = new QPushButton("Load",grpGeometria, "btCarregarGeometria");
	btCarregarGeometria->setGeometry( QRect( 390, 20, 80, 22 ) );
    
	lbNomeObjetoGeometrico = new QLabel( grpGeometria, "lbNomeObjetoGeometrico" );
    lbNomeObjetoGeometrico->setGeometry( QRect( 30, 50, 140, 20 ) ); 
    lbNomeObjetoGeometrico->setProperty( "text", tr( QString::fromUtf8( "Geometric object name" ) ) );

    cmbxGeometria = new QComboBox( FALSE, grpGeometria, "cmbxGeometria" );
    cmbxGeometria->setGeometry( QRect( 190, 50, 260, 22 ) ); 

    lbTipoJunta = new QLabel( this, "lbTipoJunta" );
    lbTipoJunta->setGeometry( QRect( 10, 320, 80, 20 ) ); 
    lbTipoJunta->setProperty( "text", tr( "Joint Type" ) );

    lbParametroFixo = new QLabel( this, "lbParametroFixo" );
    lbParametroFixo->setGeometry( QRect( 250, 320, 120, 20 ) ); 
    lbParametroFixo->setProperty( "text", tr( QString::fromUtf8( "Fixed Parameter" ) ) );

    lbComprimento = new QLabel( this, "lbComprimento" );
    lbComprimento->setGeometry( QRect( 10, 290, 70, 20 ) ); 
    lbComprimento->setProperty( "text", tr( "Length" ) );

    txtParametroFixo = new QLineEdit( this, "txtParametroFixo" );
    txtParametroFixo->setGeometry( QRect( 370, 320, 130, 22 ) ); 

    txtTorcao = new QLineEdit( this, "txtTorcao" );
    txtTorcao->setGeometry( QRect( 350, 290, 150, 22 ) ); 

    grpSistemaCoordenadas = new Q3GroupBox( this, "grpSistemaCoordenadas" );
    grpSistemaCoordenadas->setGeometry( QRect( 10, 140, 490, 140 ) ); 
    grpSistemaCoordenadas->setProperty( "title", tr( "Local Coordinate System" ) );

    tabCoordenadasLocais = new Q3Table( grpSistemaCoordenadas, "Table1" );
    tabCoordenadasLocais->setGeometry( QRect( 20, 20, 440, 104 ) ); 
    tabCoordenadasLocais->setProperty( "numRows", 4 );
    tabCoordenadasLocais->setProperty( "numCols", 4 );
	tabCoordenadasLocais->setText(0,0,"1");
	tabCoordenadasLocais->setText(0,1,"0");
	tabCoordenadasLocais->setText(0,2,"0");
	tabCoordenadasLocais->setText(0,3,"0");
	tabCoordenadasLocais->setText(1,0,"0");
	tabCoordenadasLocais->setText(1,1,"1");
	tabCoordenadasLocais->setText(1,2,"0");
	tabCoordenadasLocais->setText(1,3,"0");
	tabCoordenadasLocais->setText(2,0,"0");
	tabCoordenadasLocais->setText(2,1,"0");
	tabCoordenadasLocais->setText(2,2,"1");
	tabCoordenadasLocais->setText(2,3,"0");
	tabCoordenadasLocais->setText(3,0,"0");
	tabCoordenadasLocais->setText(3,1,"0");
	tabCoordenadasLocais->setText(3,2,"0");
	tabCoordenadasLocais->setText(3,3,"1");

    cmbxTipoJunta = new QComboBox( FALSE, this, "cmbxTipoJunta" );
    cmbxTipoJunta->setGeometry( QRect( 90, 320, 150, 22 ) ); 
	cmbxTipoJunta->insertItem("Prismatic");
	cmbxTipoJunta->insertItem("Revolute");
	
    txtComprimento = new QLineEdit( this, "txtComprimento" );
    txtComprimento->setGeometry( QRect( 90, 290, 150, 22 ) ); 

    grpMobilidadeJunta = new Q3GroupBox( this, "grpMobilidadeJunta" );
    grpMobilidadeJunta->setGeometry( QRect( 10, 350, 490, 60 ) ); 
    grpMobilidadeJunta->setProperty( "title", tr( QString::fromUtf8( "Joint Mobility Restriction" ) ) );

    lbMovimentoMaximo = new QLabel( grpMobilidadeJunta, "lbMovimentoMaximo" );
    lbMovimentoMaximo->setGeometry( QRect( 260, 20, 100, 20 ) ); 
    lbMovimentoMaximo->setProperty( "text", tr( QString::fromUtf8( "Maximum Movement" ) ) );

    txtMovimentoMinimo = new QLineEdit( grpMobilidadeJunta, "LineEdit7" );
    txtMovimentoMinimo->setGeometry( QRect( 130, 20, 100, 22 ) ); 

    txtMovimentoMaximo = new QLineEdit( grpMobilidadeJunta, "LineEdit8" );
    txtMovimentoMaximo->setGeometry( QRect( 360, 20, 100, 22 ) ); 

    lbMovimentoMinimo = new QLabel( grpMobilidadeJunta, "lbMovimentoMinimo" );
    lbMovimentoMinimo->setGeometry( QRect( 30, 20, 100, 20 ) ); 
    lbMovimentoMinimo->setProperty( "text", tr( QString::fromUtf8( "Minimum Movement" ) ) );

    cmbxFuncao = new QComboBox( FALSE, this, "cmbxFuncao" );
    cmbxFuncao->setGeometry( QRect( 350, 10, 150, 22 ) ); 
	cmbxFuncao->insertItem("End Effector");
	cmbxFuncao->insertItem("Link");
	cmbxFuncao->insertItem("Base");

    btSalvar = new QPushButton( this, "btSalvar" );
    btSalvar->setGeometry( QRect( 300, 420, 93, 26 ) ); 
    btSalvar->setProperty( "text", tr( "Save" ) );

    btCancelar = new QPushButton( this, "btCancelar" );
    btCancelar->setGeometry( QRect( 400, 420, 93, 26 ) ); 
    btCancelar->setProperty( "text", tr( "Cancel" ) );

	// Liga os Widgets necessarios aos seus respectivos eventos
	QObject::connect(cmbxTipoJunta,SIGNAL(activated(const QString &)),this,SLOT(cmbxTipoJunta_activated(const QString &)) );
	QObject::connect(btCarregarGeometria,SIGNAL(clicked()),this,SLOT(btCarregar_clicked()) );
	QObject::connect(btSelecionarArquivo,SIGNAL(clicked()),this,SLOT(btSelecionarArquivo_clicked()) );
	QObject::connect(btSalvar,SIGNAL(clicked()),this,SLOT(btSalvar_clicked()) );
	QObject::connect(btCancelar,SIGNAL(clicked()),this,SLOT(btCancelar_clicked()) );

	// Estado inicial da janela
	if (this->cmbxTipoJunta->currentText() == "Prismatic")
	{
		this->lbParametroFixo->setText("Joint Angle");
	}
	else if (this->cmbxTipoJunta->currentText() == "Revolute")
	{
		this->lbParametroFixo->setText("Joint Offset");
	}
	cmbxFuncao->setCurrentItem(1);
	bSalvar = false;
}

/*  
 *  Destroys the object and frees any allocated resources
 */
HIC::WLinkTypeCreation::~WLinkTypeCreation()
{
    // no need to delete child widgets, Qt does it all for us
}

// Ao alterar o tipo de junta do tipo de link, o seu parametro fixo na janela
// aparece com o nome "Deslocamento da junta" para tipo de link de revolucao" ou
// "Angulo da junta" para tipo de link prismatico
void HIC::WLinkTypeCreation::cmbxTipoJunta_activated(const QString & strText)
{
	if (this->cmbxTipoJunta->currentText() == "Prismatic")
	{
		this->lbParametroFixo->setText("Joint Angle");
	}
	else if (this->cmbxTipoJunta->currentText() == "Revolute")
	{
		this->lbParametroFixo->setText("Joint Offset");
	}
}


//////////////////////////////////////////////////////////////////////
// Definicoes de Constantes para leitura de arquivo 3DS
//////////////////////////////////////////////////////////////////////

/* Main Chunk */
#define MAIN_CHUNK				0x4D4D	/* Main Chunk				*/
	#define CHUNK_3D_EDITOR		0x3D3D	/* Chunk do Editor 3D		*/  
		#define MESH_VERSION		0x3D3E	/* Versao da Malha			*/
		#define OBJECT_BLOCK		0x4000	/* Bloco de Objeto 3D		*/

// Carrega o conteudo do nome do arquivo geometrico informado e insere os objetos
// geometricos no combobox de objetos geometricos
void HIC::WLinkTypeCreation::btCarregar_clicked()
{
	
	// Remove os itens no combobox de objetos geom�tricos
	this->cmbxGeometria->clear();
	
	// Arquivo de leitura binaria
	QString strFileName = this->txtGeometria->text().stripWhiteSpace();

	if (strFileName == "")
	{
		QMessageBox::information ( this, "Error", "Not a valid file.");
		return;
	}

    FILE * arq = fopen(strFileName.latin1(),"rb");

	if (arq==NULL) {

		QMessageBox::information ( this, "Error", "Error in file reading, probably it was not found.");
		//MessgaBox ->  printf ("Erro na leitura do arquivo %s.\n",filename3DS.c_str());
		return;
	}

    char carac;
	std::string name;

	// WORD  -> short (2 bytes)
	// DWORD -> long  (4 bytes)
	// FLOAT -> float (4 bytes)
	unsigned short chunk_id;		// Identificacao do chunk
	unsigned long  chunk_length; // Tamanho do chunk em bytes

    do {

		if (fread(&chunk_id,2,1,arq)==0) {
			fclose(arq);
			printf ("Mesh Objects: \n");
			return;
		}

		switch(chunk_id) {

		case(MAIN_CHUNK):
			printf ("Main Chunk found\n");
			fread(&chunk_length,4,1,arq);
			printf ("Chunk size(file): %li\n",chunk_length);
			break;

		case(CHUNK_3D_EDITOR):
			printf ("3D Editor Chunk\n");
			fread(&chunk_length,4,1,arq);
			printf ("Chunk Size: %li\n",chunk_length);
			break;

		case(OBJECT_BLOCK):
			printf ("Object Definition\n");
			fread(&chunk_length,4,1,arq);
			printf ("Chunk Size: %li\n",chunk_length);
            // Nome do objeto
			name = "";
            do 	{
				fread(&carac,1,1,arq);
				if (carac != 0) name = name + carac;
			} while (carac!=0);
			printf ("object name = %s \n",name.c_str());
			this->cmbxGeometria->insertItem(name.c_str());
			break;

        default:
			printf ("Not defined chunk \n");
			fread(&chunk_length,4,1,arq);
			printf ("Chunk size: %li\n",chunk_length);
			// Pula o chunk desconhecido
			fseek(arq,chunk_length-6,SEEK_CUR);
			break;
		}

	} while (!(feof(arq)));

	fclose(arq);
	printf ("Objetos Mesh Lidos: \n");
}

// Faz um dialogo para selecao de arquivo aparecer
void HIC::WLinkTypeCreation::btSelecionarArquivo_clicked()
{
	QStringList lstFileName = Q3FileDialog::getOpenFileNames ( "*.3ds", ".", this, "GeometryGetFile", "Select a file with geometric information" );
	QStringList::Iterator it = lstFileName.begin()++;    
	if (it != lstFileName.end())
	{
		this->txtGeometria->setText( (*it).latin1() );
	}
}

// Flag indica salvamento se botao salvar � clicado
void HIC::WLinkTypeCreation::btSalvar_clicked()
{
	this->bSalvar = true;
	this->close();
}


// Flag indica cancelamento de flag cancelar � clicada
void HIC::WLinkTypeCreation::btCancelar_clicked()
{
	this->bSalvar = false;
	this->close();
}

// Informa se o usuario optou por salvar os dados ou n�o
bool HIC::WLinkTypeCreation::salvar()
{
	return this->bSalvar;
}