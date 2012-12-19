// RobotApp.cpp: implementation of the RobotApp class.
//
//////////////////////////////////////////////////////////////////////

#include "RobotApp.h"

#include "WSelection.h"
#include "WRobotCreation.h"
#include "WLinkTypeSelection.h"
#include "PersistentLinkType.h"
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <q3table.h>
#include <q3filedialog.h>
#include <fstream>

using namespace std;
using namespace PDC;
using namespace HIC;
using namespace DMC;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMC::RobotApp::RobotApp(QWidget * parent, Robot * robot)
{
    m_robot = robot; 

    // Toda vez que a aplicacao e criada uma nova janela e criada tambem
    //if (m_robotconstructionwindow == NULL)
    m_robotconstructionwindow = new WRobotConstruction(parent,"Robot Construction",robot);

    // Conectando os widgets da janela aos slots do objeto Aplicacao
    QObject::connect(m_robotconstructionwindow->m_bt_createrobot, SIGNAL(clicked()),this,SLOT(CreateRobot()) );
    QObject::connect(m_robotconstructionwindow->m_bt_updaterobot, SIGNAL(clicked()),this,SLOT(UpdateRobot()) );
    QObject::connect(m_robotconstructionwindow->m_bt_excluderobot,SIGNAL(clicked()),this,SLOT(ExcludeRobot()) );

    QObject::connect(m_robotconstructionwindow->m_bt_loadrobot,SIGNAL(clicked()),this,SLOT(LoadRobot()) );
    QObject::connect(m_robotconstructionwindow->m_bt_saverobot,SIGNAL(clicked()),this,SLOT(SaveRobot()) );

    QObject::connect(m_robotconstructionwindow->m_bt_addlink,   SIGNAL(clicked()),this,SLOT(InsertNewLinkRobot()) );
    QObject::connect(m_robotconstructionwindow->m_bt_updatelink,SIGNAL(clicked()),this,SLOT(UpdatePositionLinkRobot()) );
    QObject::connect(m_robotconstructionwindow->m_bt_removelink,SIGNAL(clicked()),this,SLOT(ExcludeLinkRobot()) );

    // Carrega uma lista de linktypes para a aplicacao
    //double coord[4][4];
    // Constru��o do um Tipo de Link de Revolu��o
    //RevoluteLinkType * basetype;
    //coord[0][0]=0.0;  coord[0][1]=0.0; coord[0][2]=1.0; coord[0][3]=330.0;
    //coord[1][0]=0.0;  coord[1][1]=1.0; coord[1][2]=0.0; coord[1][3]=-77.0;
    //coord[2][0]=-1.0; coord[2][1]=0.0; coord[2][2]=0.0; coord[2][3]=-15.0;
    //coord[3][0]=0.0;  coord[3][1]=0.0; coord[3][2]=0.0; coord[3][3]=1.0;
    //basetype = new RevoluteLinkType();
    //basetype->LoadGeometry("robotarm.3ds","Base");
    //basetype->SetCoordinateSystem(coord);
    //basetype->SetLinkLength(550.0);
    //basetype->SetLinkTwist(0.0);
    //basetype->SetLinkOffset(0.0);
    //basetype->SetLinkTypeFunction(BASE);
    //basetype->SetLinkTypeName("Base1");
    // Adiciona o tipo de link na lista de tipos de link
    //m_linktypes.push_back(basetype);
    
    /*
    RevoluteLinkType * basetype2;
    coord[0][0]=0.0;  coord[0][1]=1.0; coord[0][2]=0.0; coord[0][3]=77.0;
    coord[1][0]=0.0;  coord[1][1]=0.0; coord[1][2]=1.0; coord[1][3]=-15.0;
    coord[2][0]=1.0;  coord[2][1]=0.0; coord[2][2]=0.0; coord[2][3]=-330.0;
    coord[3][0]=0.0;  coord[3][1]=0.0; coord[3][2]=0.0; coord[3][3]=1.0;
    basetype2 = new RevoluteLinkType();
    basetype2->LoadGeometry("robotarm.3ds","Base");
    basetype2->SetCoordinateSystem(coord);
    basetype2->SetLinkLength(0.0);
    basetype2->SetLinkTwist(0.0);
    basetype2->SetLinkOffset(550.0);
    basetype2->SetLinkTypeFunction(BASE);
    basetype2->SetLinkTypeName("Base2");
    // adiciona na lista de tipos de link
    m_linktypes.push_back(basetype2);
    */
                                
    //RevoluteLinkType * armtype;
    // Constru��o do um Tipo de Link de Revolu��o do Bra�o
    //coord[0][0]=0.0;  coord[0][1]=0.0; coord[0][2]=1.0; coord[0][3]= 200.0;
    //coord[1][0]=0.0;  coord[1][1]=1.0; coord[1][2]=0.0; coord[1][3]= -77.0;
    //coord[2][0]=-1.0; coord[2][1]=0.0; coord[2][2]=0.0; coord[2][3]= -15.0;
    //coord[3][0]=0.0;  coord[3][1]=0.0; coord[3][2]=0.0; coord[3][3]= 1.0;
    //armtype = new RevoluteLinkType();
    //armtype->LoadGeometry("robotarm.3ds","V-Shaft");
    //armtype->SetCoordinateSystem(coord);
    //armtype->SetLinkLength(570.0);
    //armtype->SetLinkTwist(0.0);
    //armtype->SetLinkOffset(0.0);
    //armtype->SetLinkTypeFunction(ACTUATOR);
    //armtype->SetLinkTypeName("V-Shaft");
    // Adiciona na lista de tipos de link
    //m_linktypes.push_back(armtype);

    //RevoluteLinkType * endeffectortype;
    // Construcao de um tipo de link que possua uma ferramenta atachada
    //coord[0][0]=80.0;  coord[0][1]=0.0;  coord[0][2]=0.0;   coord[0][3]= -70.0;
    //coord[1][0]=0.0;   coord[1][1]=80.0; coord[1][2]=0.0;   coord[1][3]= -450.0;
    //coord[2][0]=0.0;   coord[2][1]=0.0;  coord[2][2]=80.0;  coord[2][3]= 450.0;
    //coord[3][0]=0.0;   coord[3][1]=0.0;  coord[3][2]=0.0;   coord[3][3]= 1.0;
    //endeffectortype = new RevoluteLinkType();
    //endeffectortype->LoadGeometry("TIG.3DS","01");
    //endeffectortype->SetCoordinateSystem(coord);
    //endeffectortype->SetLinkLength(570.0);
    //endeffectortype->SetLinkTwist(0.0);
    //endeffectortype->SetLinkOffset(0.0);
    //endeffectortype->SetLinkTypeFunction(END_EFFECTOR);
    //endeffectortype->SetLinkTypeName("End-Effector");
    // Adiciona na lista de tipos de link
    //m_linktypes.push_back(endeffectortype);   
}

TMC::RobotApp::~RobotApp()
{
    
}

void TMC::RobotApp::CreateRobot()
{
	// Cria um objeto tipode link se nao houver
	if (this->m_robot != NULL)
	{		
		// Verifica se existe um tipo de link selecionado e n�o salvo
		if (this->m_robot->m_persistentrobot->GetFileName() == "")
		{
			if ( QMessageBox::information( this->m_robotconstructionwindow, "Aviso","O rob� atual nao foi salvo, prosseguir ?","Sim","N�o",NULL) == 1)
			{
				return;
			}
			
		}

		delete m_robot;		
	}
	
	// Mostra a janela de cricao de tipos de link
	WRobotCreation * wrobotcreation = new WRobotCreation();
	wrobotcreation->show();

	// Verifica se os dados devem ser salvos ou n�o
	if (!wrobotcreation->IsSaved())
	{
		return;
	}

	// Pega os parametros informados na janela
	string name = wrobotcreation->m_edt_name->text().latin1();
	double coordinate_system[4][4];
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][1] = wrobotcreation->m_tab_base->text(0,1).toDouble();
	coordinate_system[0][2] = wrobotcreation->m_tab_base->text(0,2).toDouble();
	coordinate_system[0][3] = wrobotcreation->m_tab_base->text(0,3).toDouble();
	coordinate_system[1][0] = wrobotcreation->m_tab_base->text(1,0).toDouble();
	coordinate_system[1][1] = wrobotcreation->m_tab_base->text(1,1).toDouble();
	coordinate_system[1][2] = wrobotcreation->m_tab_base->text(1,2).toDouble();
	coordinate_system[1][3] = wrobotcreation->m_tab_base->text(1,3).toDouble();
	coordinate_system[2][0] = wrobotcreation->m_tab_base->text(2,0).toDouble();
	coordinate_system[2][1] = wrobotcreation->m_tab_base->text(2,1).toDouble();
	coordinate_system[2][2] = wrobotcreation->m_tab_base->text(2,2).toDouble();
	coordinate_system[2][3] = wrobotcreation->m_tab_base->text(2,3).toDouble();
	coordinate_system[3][0] = wrobotcreation->m_tab_base->text(3,0).toDouble();
	coordinate_system[3][1] = wrobotcreation->m_tab_base->text(3,1).toDouble();
	coordinate_system[3][2] = wrobotcreation->m_tab_base->text(3,2).toDouble();
	coordinate_system[3][3] = wrobotcreation->m_tab_base->text(3,3).toDouble();

	// Cria o robo com os dados informados
	this->m_robot = new Robot();
	this->m_robot->SetRobotName(name);
	this->m_robot->SetBasePosition(coordinate_system);

	// Atualiza as janelas de robo
	this->m_robotconstructionwindow->m_globjectwidget->SetGraphicObject(this->m_robot);
	this->m_robottrajectorywindow->m_globjectwidget->SetGraphicObject(this->m_robot);
}

void TMC::RobotApp::UpdateRobot()
{
	// Instancia a janela de criacao de robos
	WRobotCreation* wrobotcreation = new WRobotCreation();
	
	// Passa as as informacoes do robo para a janela de criacao de robos
	wrobotcreation->m_edt_name->setText(this->m_robot->GetRobotName().data());
	double coordinate_system[4][4];
	this->m_robot->GetBasePosition(&coordinate_system);
	wrobotcreation->m_tab_base->setText(0,0,QString::number(coordinate_system[0][0]));
	wrobotcreation->m_tab_base->setText(0,1,QString::number(coordinate_system[0][1]));
	wrobotcreation->m_tab_base->setText(0,2,QString::number(coordinate_system[0][2]));
	wrobotcreation->m_tab_base->setText(0,3,QString::number(coordinate_system[0][3]));
	wrobotcreation->m_tab_base->setText(1,0,QString::number(coordinate_system[1][0]));
	wrobotcreation->m_tab_base->setText(1,1,QString::number(coordinate_system[1][1]));
	wrobotcreation->m_tab_base->setText(1,2,QString::number(coordinate_system[1][2]));
	wrobotcreation->m_tab_base->setText(1,3,QString::number(coordinate_system[1][3]));
	wrobotcreation->m_tab_base->setText(2,0,QString::number(coordinate_system[2][0]));
	wrobotcreation->m_tab_base->setText(2,1,QString::number(coordinate_system[2][1]));
	wrobotcreation->m_tab_base->setText(2,2,QString::number(coordinate_system[2][2]));
	wrobotcreation->m_tab_base->setText(2,3,QString::number(coordinate_system[2][3]));
	wrobotcreation->m_tab_base->setText(3,0,QString::number(coordinate_system[3][0]));
	wrobotcreation->m_tab_base->setText(3,1,QString::number(coordinate_system[3][1]));
	wrobotcreation->m_tab_base->setText(3,2,QString::number(coordinate_system[3][2]));
	wrobotcreation->m_tab_base->setText(3,3,QString::number(coordinate_system[3][3]));

	// Mostra a janela
	wrobotcreation->show();

	// Atualiza as informacoes do rob�
	this->m_robot->SetRobotName(wrobotcreation->m_edt_name->text().latin1());
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();
	coordinate_system[0][0] = wrobotcreation->m_tab_base->text(0,0).toDouble();

	// Atualiza as janelas de robo
	this->m_robotconstructionwindow->m_globjectwidget->SetGraphicObject(this->m_robot);
	this->m_robottrajectorywindow->m_globjectwidget->SetGraphicObject(this->m_robot);
}

void TMC::RobotApp::ExcludeRobot()
{
    QMessageBox::information(
        NULL,"Not Implemented Method",
        "TMC::RobotApp::ExcludeRobot()",
        QMessageBox::Ok,
        Qt::NoButton,
        Qt::NoButton);
}

void TMC::RobotApp::SaveRobot()
{
	// Recupera o objeto persistente
	PersistentRobot* persistentRobot = this->m_robot->m_persistentrobot;
    
	// Se o tipo de link vai ser salvo pela primeira vez
	if (persistentRobot->GetFileName().size() == 0)
	{	
		// Informe um arquivo de Robot para ser salvo
		QString filename = Q3FileDialog::getSaveFileName( ".",
			                                      "Robot Files (*.robot)",
				                                  NULL,
					                              "RobotBuilder - Salvar Robo",
						                          "Salvar Como");
		if (filename == "") return;

		// Verifica se o arquivo ja existe
		ifstream file(filename.data());

		if (file != NULL)
		{
			if (QMessageBox::information( this->m_robotconstructionwindow, "Aviso","O arquivo informando ja existe." "Deseja sobrescrever ?","&Sim", "&Nao",NULL,0,2) == 1)
			{
				return; // Se nao quiser sobrescrever retorna
			}
		}

		// Salva o tipo de link com o nome do arquivo informado
		string filename_str = filename.data();
		persistentRobot->Save(filename_str);	
	}
	else
	{
		// Atualiza os dadaos do tipo de link no arquivo
		persistentRobot->Update();
	}
	
}

void TMC::RobotApp::LoadRobot()
{
	bool ok = FALSE;

    // Seleciona um arquivo de Robot para ser aberto
    QString filename = Q3FileDialog::getOpenFileName( ".",
                                              "Robot Files (*.robot)",
                                              NULL,
                                              "RobotBuilder - Abertura de Robot",
                                              "Selecione um arquivo");

    // Verifica se um arquivo foi informado
    if (filename.isEmpty() ) return;

	// Destroi o link type da memoria se ja existir
	if (this->m_robot != NULL)
	{
		delete m_robot;
	}

	// Instancia o robot
	this->m_robot = (Robot*)PersistentRobot::Retrieve(filename.data());
 
    // Verifica se o arquivo foi aberto sem problemas
    if (this->m_robot == NULL)
    {
        // Uma mensagerm de erro aparece indicando que houve algum problema
        QMessageBox mb( "RobotBuilder - Carregamento de Robot ",
            "Houve um problema na abertura do arquivo.\nProvavelmente nao existe mais ou esta sendo usado\npor outro aplicativo.",
            QMessageBox::NoIcon,
            QMessageBox::Ok,
            Qt::NoButton,
            Qt::NoButton,
            NULL,
            "MessageBox LoadRobot");
        mb.exec();

        return;
    }

	// Passa o tipo de link para o Widget de visualizacao
	this->m_robotconstructionwindow->m_globjectwidget->SetGraphicObject(this->m_robot);
	this->m_robottrajectorywindow->m_globjectwidget->SetGraphicObject(this->m_robot);
	// Atualiza os controles da janela de trajetoria
	this->m_robottrajectorywindow->UpdateRobotControls();
}

void TMC::RobotApp::InsertNewLinkRobot()
{
	// Se nao existe robo mostra mensagem de erro
	if (this->m_robot == NULL)
	{
		QMessageBox::critical(m_robotconstructionwindow,"Erro","Um robo deve ser criado antes de inserir um link");
		return;
	}


  // Verifica se o robo ja possui uma trajetoria 
  if (m_robot->IsTherePath())
  {
    if ( QMessageBox::warning(m_robotconstructionwindow,"Aviso","A insercao do novo link implicar na perda do caminho descrito.\n Deseja continuar ? ",0, 1) == 1 )
    {
		
		for (int i=0; i < m_robot->SizeRobotPosition(); i++)
		{
			// Pega a posicao
			RobotPosition * robotposition = m_robot->GetRobotPosition(i);
			// Remove 
			m_robot->RemoveRobotPosition(robotposition);
		}
		
	}
	// Retorna do metodo (cancela o caso-de-uso)
	else
	{		
	    return;		
	}
  }

  // Seleciona um novo tipo de link para fazer parte do robo
  LinkType * selectedlinktype;
  // Novo link a ser adicionado
  Link * novolink;
  
  //  selectedlinktype = WSelection::GetLinkType(m_robotconstructionwindow,"JanelaSelecao",m_linktypes);

  //QStringList lst;
  //for (int i=0;i < m_linktypes.size();i++)
  //{
  //    lst << m_linktypes[i]->GetLinkTypeName().c_str();
  //  }
  //bool ok;
  //QString linktypename = QInputDialog::getItem(
  //        "RobotBuilder", "Selecione um tipo de link:", lst, 1, TRUE, &ok,
  //        m_robotconstructionwindow );

  WLinkTypeSelection * wlinktypeselection = new WLinkTypeSelection();
  wlinktypeselection->show();


  if ( wlinktypeselection->IsAdded() )
  {
      // Botao ok pressionado
      // Procura um tipo de link com o nome de arquivo selecionado
	  string filename = wlinktypeselection->m_edt_filename->text().latin1();
	  selectedlinktype = (LinkType*) PersistentLinkType::Retrieve(filename.c_str());

	  if (selectedlinktype == NULL)
	  {
		QMessageBox::information( m_robotconstructionwindow, "Erro",
				"O arquivo do tipo de link informado\n"
				"nao foi achado." );
		return;

	  }
            
  }
  else
  {
      // Botao cancel foi pressionado, retorna
      return;
  }

  // Verifica a funcao do tipo de Link selecionado 
  switch (selectedlinktype->GetLinkTypeFunction())
  {
    // Tipo de link e uma base
    case BASE:
	{
		  // Verifica se ja existe outra base no robo
		  for (int i=0;i < m_robot->SizeLink(); i++)
		  {
			// Verifica a cada link se existe alguma BASE
			// Se existir envia uma msg de erro e retorna
			if (m_robot->GetLink(i)->GetLinkFunction() == BASE)
			{
			  QMessageBox::information( m_robotconstructionwindow, "RobotBuilder",
						  "Nao pode haver duas links do tipo BASE\n"
						  "no mesmo robo." );
			  return;
			}
		  }
		  // Cria um novo link com o tipo de link selecionado
		  novolink = new Link(selectedlinktype);
		  // Adiciona link na primeira posicao do robo
		  m_robot->AddLinkFirstPosition(novolink);
	}
    break;
    // Tipo de link e um atuador final
    case END_EFFECTOR:
	{
		  // Verifica se ja existe outra base no robo
		  for (int j=0;j < m_robot->SizeLink(); j++)
		  {
			// Verifica a cada link se existe alguma BASE
			// Se existir envia uma msg de erro e retorna
			if (m_robot->GetLink(j)->GetLinkFunction() == END_EFFECTOR)
			{
			  QMessageBox::information(m_robotconstructionwindow, "RobotBuilder",
						  "Nao pode haver dois links do tipo END EFFECTOR\n"
						  "no mesmo robo." );
			  return;
			}
		  }
		  // Cria um novo link com o tipo de link selecionado
		  novolink = new Link(selectedlinktype);
		  // Adiciona link na ultima posicao do robo
		  m_robot->AddLinkLastPosition(novolink);
	}
    break;
    // Tipo de link e um elo
    case ACTUATOR:
	{
		  // Sistema requisita o numero da posicao onde o link ficara no robo		  
		  int numeroposicao = wlinktypeselection->m_edt_numlink->text().toDouble();
		  // foi pressionado o botao ok
		  // Cria um novo link com o tipo de link selecionado
		  novolink = new Link(selectedlinktype);
		  // Informa a posicao do link
		  novolink->SetLinkNumber(numeroposicao);
		  // Verifica se a posicao do link e valida
		  if (m_robot->IsValidLinkNumber(novolink))
		  {
			// Insere o link na posicao informada
			m_robot->AddLink(novolink);
		  }
		  else
		  {
			// Mensagem de erro
			QMessageBox::critical(m_robotconstructionwindow, "Erro",
					  "O numero da posicao do link � inv�lido\n"
					  "Numero deve ser maior que o numero da base e menor uqe o numero da ferramenta." );
			// Apaga o link da memoria
			delete novolink;
			// Retorna do metodo
			return;
		  }
	}
    break;    
  }

  // Atualiza os controles da janela de trajetoria
  this->m_robottrajectorywindow->UpdateRobotControls();

}

void TMC::RobotApp::UpdatePositionLinkRobot()
{
     QMessageBox::information(
        NULL,"Not Implemented Method",
        "TMC::RobotApp::UpdatePositionLinkRobot()",
        QMessageBox::Ok,
        Qt::NoButton,
        Qt::NoButton);
}

void TMC::RobotApp::ExcludeLinkRobot()
{
    QMessageBox::information(
        NULL,"Not Implemented Method",
        "TMC::RobotApp::ExcludeLinkRobot()",
        QMessageBox::Ok,
        Qt::NoButton,
        Qt::NoButton);
}

void TMC::RobotApp::SelectNewLinkType()
{
     QMessageBox::information(
        NULL,"Not Implemented Method",
        "TMC::RobotApp::SelectNewLinkType()",
        QMessageBox::Ok,
        Qt::NoButton,
        Qt::NoButton);
}

void TMC::RobotApp::InformLinkNumber()
{
   QMessageBox::information(
        NULL,"Not Implemented Method",
        "TMC::RobotApp::InformLinkNumber()",
        QMessageBox::Ok,
        Qt::NoButton,
        Qt::NoButton);
}

void TMC::RobotApp::SelectRobotLink()
{
  QMessageBox::information(
        NULL,"Not Implemented Method",
        "TMC::RobotApp::SelectRobotLink()",
        QMessageBox::Ok,
        Qt::NoButton,
        Qt::NoButton);
}

int TMC::RobotApp::Exec()
{
    m_robotconstructionwindow->showMaximized();
    m_robotconstructionwindow->setFocus();
    return 0;
}

void TMC::RobotApp::SetTrajectoryWindow(WRobotTrajectory * robotTrajectoryWindow)
{
	this->m_robottrajectorywindow = robotTrajectoryWindow;
}
