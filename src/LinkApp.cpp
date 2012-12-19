// LinkApp.cpp: implementation of the LinkApp class.
//
//////////////////////////////////////////////////////////////////////

#include "LinkApp.h"

#include "WLinkTypeCreation.h"
#include "PersistentRevoluteLinkType.h"
#include "PersistentPrismaticLinkType.h"
#include "PersistentLinkType.h"

#include <q3filedialog.h>
#include <qmessagebox.h>
#include <qcombobox.h>
#include <q3table.h>
#include <fstream>
#include <qlineedit.h>

using namespace std;
using namespace DMC;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMC::LinkApp::LinkApp(QWidget * parent,LinkType * linktype)
{
    m_linktype = linktype;

    m_linktypewindow = new WLinkTypeView(parent,"Link Type",linktype);
    // Conexao de eventos entre widgets da janela e os metodos da aplicacao
    QObject::connect(m_linktypewindow->m_bt_createlinktype, SIGNAL(clicked()),this,SLOT(CreateLinkType()  ) );
    QObject::connect(m_linktypewindow->m_bt_excludelinktype,SIGNAL(clicked()),this,SLOT(ExcludeLinkType() ) );
    QObject::connect(m_linktypewindow->m_bt_updatelinktype, SIGNAL(clicked()),this,SLOT(UpdateLinkType()  ) );
    QObject::connect(m_linktypewindow->m_bt_loadlinktype,   SIGNAL(clicked()),this,SLOT(LoadLinkType()    ) );
    QObject::connect(m_linktypewindow->m_bt_savelinktype,   SIGNAL(clicked()),this,SLOT(SaveLinkType()    ) );	
}

TMC::LinkApp::~LinkApp()
{
    //delete m_linktypewindow (Nao percisa disso pois o Qt ja tem coletor de lixo)
}

void TMC::LinkApp::CreateLinkType()
{
	// Cria um objeto tipode link se nao houver
	if (this->m_linktype != NULL)
	{		
		// Verifica se existe um tipo de link selecionado e n�o salvo
		if (this->m_linktype->GetLinkTypeFunction() == -1)
		{
			if ( QMessageBox::information( this->m_linktypewindow, "Warning","Current link type was not saved, proceed ?","Yes","No",NULL) == 0)
			{
				return;
			}
			
		}

		delete m_linktype;		
	}
	
	// Mostra a janela de cricao de tipos de link
	WLinkTypeCreation * wlinktypecreation = new WLinkTypeCreation();
	wlinktypecreation->show();

	// Verifica se os dados devem ser salvos ou n�o
	if (!wlinktypecreation->salvar())
	{
		return;
	}

	// Pega os parametros para a cricao de um tipo de link e armazena em variaveis
	string strName     = wlinktypecreation->txtNome->text().latin1();
	int    iFunction   = wlinktypecreation->cmbxFuncao->currentItem();
	string strGeometryFileName = wlinktypecreation->txtGeometria->text().latin1();
	string strGeometricObject  = wlinktypecreation->cmbxGeometria->text(wlinktypecreation->cmbxGeometria->currentItem()).latin1();
	bool ok = true;
	double localCoordinate[4][4];
	localCoordinate[0][0] = wlinktypecreation->tabCoordenadasLocais->text(0,0).toDouble(&ok);
	localCoordinate[1][0] = wlinktypecreation->tabCoordenadasLocais->text(1,0).toDouble(&ok);
	localCoordinate[2][0] = wlinktypecreation->tabCoordenadasLocais->text(2,0).toDouble(&ok);
	localCoordinate[3][0] = wlinktypecreation->tabCoordenadasLocais->text(3,0).toDouble(&ok);
	localCoordinate[0][1] = wlinktypecreation->tabCoordenadasLocais->text(0,1).toDouble(&ok);
	localCoordinate[1][1] = wlinktypecreation->tabCoordenadasLocais->text(1,1).toDouble(&ok);
	localCoordinate[2][1] = wlinktypecreation->tabCoordenadasLocais->text(2,1).toDouble(&ok);
	localCoordinate[3][1] = wlinktypecreation->tabCoordenadasLocais->text(3,1).toDouble(&ok);
	localCoordinate[0][2] = wlinktypecreation->tabCoordenadasLocais->text(0,2).toDouble(&ok);
	localCoordinate[1][2] = wlinktypecreation->tabCoordenadasLocais->text(1,2).toDouble(&ok);
	localCoordinate[2][2] = wlinktypecreation->tabCoordenadasLocais->text(2,2).toDouble(&ok);
	localCoordinate[3][2] = wlinktypecreation->tabCoordenadasLocais->text(3,2).toDouble(&ok);
	localCoordinate[0][3] = wlinktypecreation->tabCoordenadasLocais->text(0,3).toDouble(&ok);
	localCoordinate[1][3] = wlinktypecreation->tabCoordenadasLocais->text(1,3).toDouble(&ok);
	localCoordinate[2][3] = wlinktypecreation->tabCoordenadasLocais->text(2,3).toDouble(&ok);
	localCoordinate[3][3] = wlinktypecreation->tabCoordenadasLocais->text(3,3).toDouble(&ok);
	double lenght = wlinktypecreation->txtComprimento->text().toDouble(&ok);
	double twist  = wlinktypecreation->txtTorcao->text().toDouble(&ok);
	string strJointType = wlinktypecreation->cmbxTipoJunta->text(wlinktypecreation->cmbxTipoJunta->currentItem()).latin1();
	double fixedParameter = wlinktypecreation->txtParametroFixo->text().toDouble(&ok);
	double lowerMovBound = wlinktypecreation->txtMovimentoMinimo->text().toDouble(&ok);
	double upperMovBound = wlinktypecreation->txtMovimentoMaximo->text().toDouble(&ok);

	// Verifica��o dos dados informados

	if (strName == "")
	{
		QMessageBox::critical( this->m_linktypewindow,"Error","Link type name must be informed");
		return;
	}

	if ((strGeometryFileName == "")||(strGeometricObject == ""))
	{
		QMessageBox::critical( this->m_linktypewindow,"Error","File with geometric information was not informed");
		return;
	}
	
	if (strJointType == "Prismatic")
	{
		this->m_linktype = new PrismaticLinkType();
	}
	else if (strJointType == "Revolute")
	{
		this->m_linktype = new RevoluteLinkType();
	}
	else
	{
		QMessageBox::critical( this->m_linktypewindow,"Error","Joint type selection was not found");
		return;
	}

	// Atribuindo os dados ao tipo de link
	this->m_linktype->SetLinkTypeName(strName);
	this->m_linktype->SetLinkTypeFunction(iFunction);
	this->m_linktype->LoadGeometry(strGeometryFileName,strGeometricObject);
	this->m_linktype->SetCoordinateSystem(localCoordinate);
	this->m_linktype->SetLinkLength(lenght);
	this->m_linktype->SetLinkTwist(twist);

	if (strJointType == "Prismatic")
	{
		((PrismaticLinkType*)this->m_linktype)->SetJointAngle(fixedParameter);
	}
	else if (strJointType == "Revolute")
	{
		((RevoluteLinkType*)this->m_linktype)->SetLinkOffset(fixedParameter);
	}	

	this->m_linktype->SetJointRestriction(lowerMovBound,upperMovBound);	
	this->m_linktypewindow->m_globjectwidget->SetGraphicObject(this->m_linktype);
}

void TMC::LinkApp::UpdateLinkType()
{
		// Cria um objeto tipode link se nao houver
	if (this->m_linktype == NULL)
	{			
		QMessageBox::critical( this->m_linktypewindow, "Error","A link type must be created or selected first");
		return;
	}		
	
	// Cria a janela de cricao de tipos de link
	WLinkTypeCreation * wlinktypecreation = new WLinkTypeCreation();

	// Pega os parametros para a atualizacao de um tipo de link e armazena na janela
	wlinktypecreation->txtNome->setText(this->m_linktype->GetLinkTypeName().c_str());
	wlinktypecreation->cmbxFuncao->setCurrentItem(this->m_linktype->GetLinkTypeFunction());

	wlinktypecreation->cmbxFuncao->setEnabled(false);

	wlinktypecreation->txtComprimento->setText(QString::number(this->m_linktype->GetLinkLength()));
	wlinktypecreation->txtTorcao->setText(QString::number(this->m_linktype->GetLinkTwist()));

	// Esconde as informacoes geometricas (que nao podem ser alteradas)
	wlinktypecreation->removeChild((QObject*)wlinktypecreation->grpGeometria);	
	wlinktypecreation->removeChild((QObject*)wlinktypecreation->btCarregarGeometria);
	wlinktypecreation->removeChild((QObject*)wlinktypecreation->btSelecionarArquivo);
	
	// Passa o sistema de coordenadas local para tabela
	double localCoordinate[4][4]; 
	this->m_linktype->GetCoordinateSystem(&localCoordinate);
	wlinktypecreation->tabCoordenadasLocais->setText(0,0,QString::number(localCoordinate[0][0]));
	wlinktypecreation->tabCoordenadasLocais->setText(0,1,QString::number(localCoordinate[0][1]));
	wlinktypecreation->tabCoordenadasLocais->setText(0,2,QString::number(localCoordinate[0][2]));
	wlinktypecreation->tabCoordenadasLocais->setText(0,3,QString::number(localCoordinate[0][3]));
	wlinktypecreation->tabCoordenadasLocais->setText(1,0,QString::number(localCoordinate[1][0]));
	wlinktypecreation->tabCoordenadasLocais->setText(1,1,QString::number(localCoordinate[1][1]));
	wlinktypecreation->tabCoordenadasLocais->setText(1,2,QString::number(localCoordinate[1][2]));
	wlinktypecreation->tabCoordenadasLocais->setText(1,3,QString::number(localCoordinate[1][3]));
	wlinktypecreation->tabCoordenadasLocais->setText(2,0,QString::number(localCoordinate[2][0]));
	wlinktypecreation->tabCoordenadasLocais->setText(2,1,QString::number(localCoordinate[2][1]));
	wlinktypecreation->tabCoordenadasLocais->setText(2,2,QString::number(localCoordinate[2][2]));
	wlinktypecreation->tabCoordenadasLocais->setText(2,3,QString::number(localCoordinate[2][3]));
	wlinktypecreation->tabCoordenadasLocais->setText(3,0,QString::number(localCoordinate[3][0]));
	wlinktypecreation->tabCoordenadasLocais->setText(3,1,QString::number(localCoordinate[3][1]));
	wlinktypecreation->tabCoordenadasLocais->setText(3,2,QString::number(localCoordinate[3][2]));
	wlinktypecreation->tabCoordenadasLocais->setText(3,3,QString::number(localCoordinate[3][3]));

	// Passa as restricoes de movimento
	double lowerMovBound, upperMovBound;
	this->m_linktype->GetJointRestriction(lowerMovBound,upperMovBound);
	wlinktypecreation->txtMovimentoMinimo->setText(QString::number(lowerMovBound));
	wlinktypecreation->txtMovimentoMaximo->setText(QString::number(upperMovBound));

	// Passa as informacoes de tipo de junta e o Parametro fico de DH restante
	if (this->m_linktype->GetSlideType()=="Prismatic")
	{
		wlinktypecreation->cmbxTipoJunta->setCurrentItem(0);
		double fixedParameter = ((PrismaticLinkType*)this->m_linktype)->GetJointAngle();
		wlinktypecreation->txtParametroFixo->setText(QString::number(fixedParameter));	
	}
	else
	{
		wlinktypecreation->cmbxTipoJunta->setCurrentItem(1);
		double fixedParameter = ((RevoluteLinkType*)this->m_linktype)->GetLinkOffset();
		wlinktypecreation->txtParametroFixo->setText(QString::number(fixedParameter));	
	}

	// Mostra a janela de cricao de tipos de link com os dados do tipode link corrente
	wlinktypecreation->show();

	// Verifica se os dados devem ser salvos ou n�o
	if (!wlinktypecreation->salvar())
	{
		return;
	}

	// Pega os parametros para a atualizacao de um tipo de link e armazena em variaveis
	string strName     = wlinktypecreation->txtNome->text().latin1();
	int    iFunction   = wlinktypecreation->cmbxFuncao->currentItem();
	string strGeometryFileName = wlinktypecreation->txtGeometria->text().latin1();
	string strGeometricObject  = wlinktypecreation->cmbxGeometria->currentText().latin1();
	bool ok = true;
	localCoordinate[4][4];
	localCoordinate[0][0] = wlinktypecreation->tabCoordenadasLocais->text(0,0).toDouble(&ok);
	localCoordinate[1][0] = wlinktypecreation->tabCoordenadasLocais->text(1,0).toDouble(&ok);
	localCoordinate[2][0] = wlinktypecreation->tabCoordenadasLocais->text(2,0).toDouble(&ok);
	localCoordinate[3][0] = wlinktypecreation->tabCoordenadasLocais->text(3,0).toDouble(&ok);
	localCoordinate[0][1] = wlinktypecreation->tabCoordenadasLocais->text(0,1).toDouble(&ok);
	localCoordinate[1][1] = wlinktypecreation->tabCoordenadasLocais->text(1,1).toDouble(&ok);
	localCoordinate[2][1] = wlinktypecreation->tabCoordenadasLocais->text(2,1).toDouble(&ok);
	localCoordinate[3][1] = wlinktypecreation->tabCoordenadasLocais->text(3,1).toDouble(&ok);
	localCoordinate[0][2] = wlinktypecreation->tabCoordenadasLocais->text(0,2).toDouble(&ok);
	localCoordinate[1][2] = wlinktypecreation->tabCoordenadasLocais->text(1,2).toDouble(&ok);
	localCoordinate[2][2] = wlinktypecreation->tabCoordenadasLocais->text(2,2).toDouble(&ok);
	localCoordinate[3][2] = wlinktypecreation->tabCoordenadasLocais->text(3,2).toDouble(&ok);
	localCoordinate[0][3] = wlinktypecreation->tabCoordenadasLocais->text(0,3).toDouble(&ok);
	localCoordinate[1][3] = wlinktypecreation->tabCoordenadasLocais->text(1,3).toDouble(&ok);
	localCoordinate[2][3] = wlinktypecreation->tabCoordenadasLocais->text(2,3).toDouble(&ok);
	localCoordinate[3][3] = wlinktypecreation->tabCoordenadasLocais->text(3,3).toDouble(&ok);
	double lenght = wlinktypecreation->txtComprimento->text().toDouble(&ok);
	double twist  = wlinktypecreation->txtTorcao->text().toDouble(&ok);
	string strJointType = wlinktypecreation->cmbxTipoJunta->currentText();
	double fixedParameter = wlinktypecreation->txtParametroFixo->text().toDouble(&ok);
	lowerMovBound = wlinktypecreation->txtMovimentoMinimo->text().toDouble(&ok);
	upperMovBound = wlinktypecreation->txtMovimentoMaximo->text().toDouble(&ok);


	// Verifying input parameters

	if (strName == "")
	{
		QMessageBox::critical( this->m_linktypewindow,"Erro","Nome do tipo de link deve ser informado");
		return;
	}

	//if (strGeometryFileName == "")
	//{
	//	QMessageBox::critical( this->m_linktypewindow,"Erro","Arquivo que contem a geometria nao foi informado");
	//	return;
	//}

	//if (strJointType == "Prism�tico")
	//{
	//	this->m_linktype = new PrismaticLinkType();
	//}
	//else if (strJointType == "de Revolu��o")
	//{
	//	this->m_linktype = new RevoluteLinkType();
	//}
	//else
	//{
	//	QMessageBox::critical( this->m_linktypewindow,"Erro","Tipo de junta selecionada n�o existe");
	//	return;
	//}

	this->m_linktype->SetLinkTypeName(strName);
	//this->m_linktype->SetLinkTypeFunction(iFunction);
	//this->m_linktype->LoadGeometry(strGeometryFileName,strGeometricObject);
	this->m_linktype->SetCoordinateSystem(localCoordinate);
	this->m_linktype->SetLinkLength(lenght);
	this->m_linktype->SetLinkTwist(twist);

	if (strJointType == "Prismatic")
	{
		((PrismaticLinkType*)this->m_linktype)->SetJointAngle(fixedParameter);
	}
	else if (strJointType == "Revolute")
	{
		((RevoluteLinkType*)this->m_linktype)->SetLinkOffset(fixedParameter);
	}	

	this->m_linktype->SetJointRestriction(lowerMovBound,upperMovBound);	
	this->m_linktypewindow->m_globjectwidget->SetGraphicObject(this->m_linktype);
}

void TMC::LinkApp::ExcludeLinkType()
{
    QMessageBox::information(
        NULL,"Not Implemented Method",
        "TMC::LinkApp::ExcludeLinkType()",
        QMessageBox::Ok,
        Qt::NoButton,
        Qt::NoButton);
}

void TMC::LinkApp::SaveLinkType()
{
	// Recupera o objeto persistente
	PersistentLinkType* persistentLinkType = this->m_linktype->m_persistentlinktype;
    
	// Se o tipo de link vai ser salvo pela primeira vez
	if (!persistentLinkType->hasFileName())
	{	
		// Informe um arquivo de LinkType para ser salvo
		QString filename = Q3FileDialog::getSaveFileName( ".",
			                                      "LinkType Files (*.linktype)",
				                                  NULL,
					                              "RobotBuilder - LinkType Save",
						                          "Salve As");

		// Verifica se o arquivo ja existe
		ifstream file(filename.data());

		if (file != NULL)
		{
			if (QMessageBox::information( this->m_linktypewindow, "Warning","File already exists." "Overwrite ?","&Yes", "&No",NULL,0,2) == 1)
			{
				return; // Se nao quiser sobrescrever retorna
			}
		}

		// Salva o tipo de link com o nome do arquivo informado
		string filename_str = filename.data();
		persistentLinkType->Save(filename_str);	
	}
	else
	{
		// Atualiza os dadaos do tipo de link no arquivo
		persistentLinkType->Update();
	}
}

void TMC::LinkApp::LoadLinkType()
{
    bool ok = FALSE;

    // Seleciona um arquivo de LinkType para ser aberto
    QString filename = Q3FileDialog::getOpenFileName( ".",
                                              "LinkType Files (*.linktype)",
                                              NULL,
                                              "RobotBuilder - LinkType Open",
                                              "Select file");

    // Verifica se um arquivo foi informado
    if (filename.isEmpty() )
	{
		this->m_linktypewindow->m_globjectwidget->SetGraphicObject(NULL);				
		m_linktype = NULL;		
		return;
	}	

 	LinkType * linktype = (LinkType*)PersistentLinkType::Retrieve(filename.data());
 
    // Verifica se o arquivo foi aberto sem problemas
    if (linktype == NULL)
    {
        // Uma mensagerm de erro aparece indicando que houve algum problema
        QMessageBox mb( "RobotBuilder - Link Type Load ",
            "A problem ocurred during file opening.\nProbably it does not exist more or it is been used\nby another application.",
            QMessageBox::NoIcon,
            QMessageBox::Ok,
            Qt::NoButton,
            Qt::NoButton,
            NULL,
            "MessageBox LoadLinkType");
        mb.exec();				

		this->m_linktypewindow->m_globjectwidget->SetGraphicObject(NULL);				
		if (m_linktype != NULL) { delete m_linktype; }
		this->m_linktype = NULL;
        return;
    }
	else
	{		
		this->m_linktypewindow->m_globjectwidget->SetGraphicObject(linktype);				
		if (m_linktype != NULL) { delete m_linktype; }
		this->m_linktype = linktype;
	}

	// Passa o tipo de link para o Widget de visualizacao
	//this->m_linktypewindow->m_globjectwidget->SetGraphicObject(this->m_linktype);	
}


int TMC::LinkApp::Exec()
{
    m_linktypewindow->showMaximized();
    m_linktypewindow->setFocus();
    return 0;
}
