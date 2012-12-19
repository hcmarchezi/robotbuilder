// Robot.cpp: implementation of the Robot class.
//
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif

#include "Robot.h"
#include <algorithm>
#include <GL/glu.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::Robot::Robot()
{
    m_base_position   = NULL;
    m_persistentrobot = new PersistentRobot(this);
}

PDC::Robot::~Robot()
{
    unsigned long i;

    // Desaloca a mtriz da posição da base
    if (m_base_position != NULL)
        free(m_base_position);

    // Desaloca cada um dos seus links da cadeia
    for (i = 0;i < m_links.size();i++)
        delete m_links[i];

    // Desaloca cada uma das posicoes de robo da lista
    for (i = 0;i < m_robotpositions.size();i++)
        delete m_robotpositions[i];
}

void PDC::Robot::GetBasePosition(double (* frame)[4][4])
{
    // Os elementos da matriz de frame e do sistema de coordenadas

    // são posicionados em locais diferentes daqueles que estamos
    // acostumados para seguir um padrão estipulado pelo OpenGL

    (*frame)[0][0] = m_base_position[0];
    (*frame)[1][0] = m_base_position[1];
    (*frame)[2][0] = m_base_position[2];
    (*frame)[3][0] = m_base_position[3];
    (*frame)[0][1] = m_base_position[4];
    (*frame)[1][1] = m_base_position[5];
    (*frame)[2][1] = m_base_position[6];
    (*frame)[3][1] = m_base_position[7];
    (*frame)[0][2] = m_base_position[8];

    (*frame)[1][2] = m_base_position[9];
    (*frame)[2][2] = m_base_position[10];
    (*frame)[3][2] = m_base_position[11];
    (*frame)[0][3] = m_base_position[12];
    (*frame)[1][3] = m_base_position[13];
    (*frame)[2][3] = m_base_position[14];
    (*frame)[3][3] = m_base_position[15];
}

void PDC::Robot::SetBasePosition(double frame[4][4])
{
    delete m_base_position;

    m_base_position = new double[16];

    // Pega o formato de matriz i j e converte para o
    // formato j i de acordo com o padrão do OpenGL

    m_base_position[0]  = frame[0][0];
    m_base_position[1]  = frame[1][0];
    m_base_position[2]  = frame[2][0];
    m_base_position[3]  = frame[3][0];
    m_base_position[4]  = frame[0][1];
    m_base_position[5]  = frame[1][1];
    m_base_position[6]  = frame[2][1];
    m_base_position[7]  = frame[3][1];
    m_base_position[8]  = frame[0][2];
    m_base_position[9]  = frame[1][2];
    m_base_position[10] = frame[2][2];
    m_base_position[11] = frame[3][2];

    m_base_position[12] = frame[0][3];

    m_base_position[13] = frame[1][3];
    m_base_position[14] = frame[2][3];
    m_base_position[15] = frame[3][3];
}

void PDC::Robot::AddLink(Link * newlink)
{
    unsigned long i = 0;
    unsigned long newnumber = newlink->GetLinkNumber();

    if (!(IsValidLinkNumber(newlink)))
        return;

    // Todos os links de numero >= ao novo numero sao atualizados
    for (i = newnumber;i < m_links.size();i++)
        m_links[i]->SetLinkNumber(m_links[i]->GetLinkNumber()+1);

    m_links.insert(m_links.begin()+newlink->GetLinkNumber(),newlink);
}

void PDC::Robot::ChangeLinkNumber(long newnumber, Link * selectedlink)
{
    unsigned long initialnumber = selectedlink->GetLinkNumber();
    unsigned long finalnumber   = newnumber;
    unsigned long aux; // numero auxiliar

    if (initialnumber > finalnumber)
    {
        // Atualiza o numero dos links do robo
        for (aux = finalnumber;aux < initialnumber - 1;aux++)
            m_links[aux]->SetLinkNumber(m_links[aux]->GetLinkNumber()+1);
    }
    else
    {
        // Atualiza o numero dos links do robo
        for (aux = initialnumber+1;aux < finalnumber;aux++)
            m_links[aux]->SetLinkNumber(m_links[aux]->GetLinkNumber()-1);
    }

    // Altera o numero do link selecionado
    m_links[initialnumber]->SetLinkNumber(newnumber);

    // Remove o link da posicao original no vetor
    m_links.erase(m_links.begin()+initialnumber);

    // Reinsere o Link na sua nova posicao
    m_links.insert(m_links.begin()+newnumber,selectedlink);
}

void PDC::Robot::RemoveLink(Link * selectedlink)
{
    unsigned long aux;
    unsigned long linknumber = selectedlink->GetLinkNumber();

    for (aux=linknumber+1;aux<m_links.size();aux++)
        m_links[aux]->SetLinkNumber(m_links[aux]->GetLinkNumber()-1);

    m_links.erase(m_links.begin()+linknumber);
}

bool PDC::Robot::LoadRobot(string name)
{
    return false;
}

bool PDC::Robot::SaveRobot()
{
    return false;
}

RobotPosition * PDC::Robot::CaptureRobotPosition()
{
    unsigned long i;
    RobotPosition * robotposition = new RobotPosition;

    double movement;

    for (i = 0;i < m_links.size();i++)
    {
        LinkPosition * linkposition = new LinkPosition(m_links[i]);
        linkposition->CaptureLinkPosition();
        robotposition->AddLinkPosition(linkposition);

        movement = linkposition->GetLinkPositionMov();
    }

    return robotposition;
}

bool PDC::Robot::AddRobotPosition(RobotPosition * newrobotposition)
{
    unsigned long i = 0;
    unsigned long j = 0;

    // Verifica se existe uma posicao de robo com o
    // instante de tempo menor ou iguak ao informado
    if (m_robotpositions.size() > 0)
    {
        while (i < m_robotpositions.size())
        {
            double time1 = m_robotpositions[i]->GetInstantTime();
            double time2 = newrobotposition->GetInstantTime();

            // Se encontrou alguma posicao de robo com o mesmo
            // instante de tempo retorna erro
            if (time2 == time1)
                return false;
            // Se achou uma posicao de robo com o instante de tempo
            // que o novo sai do while
            else if (time2 < time1)
                break;

            i++;
        }
    }

    // Insere a posição de robô ordenadamente pelo instante de tempo
    m_robotpositions.insert(m_robotpositions.begin()+i,newrobotposition);

    // Conecta cada posicao de link do link j da ultima posicao de robô
    // para o seu respectivo posicao de link j da nova posicao de robô
    if (i > 0)
    {
        m_robotpositions[i-1]->SetNextRobotPosition(m_robotpositions[i]);

        for (j = 0;j < m_links.size();j++)
            m_robotpositions[i-1]->GetLinkPosition(j)->SetNextLinkPosition(m_robotpositions[i]->GetLinkPosition(j));
    }

    // Conecta cada posicao de link do link j da ultima posicao de robô
    // para o seu respectivo posicao de link j da nova posicao de robô
    if ((i < m_robotpositions.size()-1)&&(m_robotpositions.size() > 1))
    {
        m_robotpositions[i]->SetNextRobotPosition(m_robotpositions[i+1]);

        for (j = 0;j < m_links.size();j++)
            m_robotpositions[i]->GetLinkPosition(j)->SetNextLinkPosition(m_robotpositions[i+1]->GetLinkPosition(j));
    }

    return true;
}

void PDC::Robot::RemoveRobotPosition(RobotPosition * selectedrobotposition)
{
    unsigned long i = 0;
    unsigned long j;

    // Procura a posicao de robo que possui o instante de tempo informado
    while ( (m_robotpositions[i]->GetInstantTime() != selectedrobotposition->GetInstantTime())&&
            (i < m_robotpositions.size()) )
        i++;

    // ERRO: Posição de Robô não foi achada
    if (i == m_robotpositions.size())
        return;

    // Apaga a posicao de robô
    m_robotpositions.erase(m_robotpositions.begin() + i);

    // Refaz as conexões das posições de link entre a
    // posicao de robo entre as posicoes i-1 e i
    if (i > 0)
    {
        for (j = 0;j < m_links.size();j++)
            m_robotpositions[i-1]->GetLinkPosition(j)->SetNextLinkPosition(m_robotpositions[i]->GetLinkPosition(j));
    }
    // Se a ultima posicao foi deletada as posicoes de link
    // devem apontar para null
    else if ((i > 0)&&(i == m_robotpositions.size()))
    {
        for (j = 0;j < m_links.size();j++)
            m_robotpositions[i-1]->GetLinkPosition(j)->SetNextLinkPosition(NULL);
    }

}

bool PDC::Robot::UpdateRobotPosition(RobotPosition * selectedrobotposition)
{
    unsigned long i;

    // Captura as posicoes do robo
    for (i = 0;i < m_links.size();i++)
        selectedrobotposition->GetLinkPosition(i)->CaptureLinkPosition();

    return true;
}

bool PDC::Robot::IsValidLinkNumber(Link * newlink)
{
    long linknumber   = newlink->GetLinkNumber();
    long linkfunction = newlink->GetLinkFunction();

    bool AlreadyHasBase        = false;;
    bool AlreadyHasEndEffector = false;;

    // Verifica se ja existe uma base no robô e se ja existe um end-effector
    if (m_links.size()>0)
    {
        AlreadyHasBase        = (m_links[0]->GetLinkFunction() == BASE);
        AlreadyHasEndEffector = (m_links[m_links.size() - 1]->GetLinkFunction() == END_EFFECTOR);
    }

    // Se o novo Link for uma base e ja houver uma base ou número do link é diferente
    // de 0 retorna false
    if (linkfunction == BASE)
    {
        if ((AlreadyHasBase)||(linknumber != 0))
            return false;
        else
            return true;
    }

    // Se o novo Link for um end effector e ja houver um end-effector retorna false
    if (linkfunction == END_EFFECTOR)
    {
        if ((AlreadyHasEndEffector)||(linknumber != (long) m_links.size()))
            return false;
        else
            return true;
    }

    // Se o novo Link tiver a função de SIMPLES
    if (AlreadyHasBase&&AlreadyHasEndEffector)
    {
        return ((linknumber) >= 0)&&(linknumber <= (long)m_links.size());
    }
    else if (AlreadyHasBase)
    {
        return ((linknumber) > 0)&&(linknumber <= (long) m_links.size());
    }
    else if (AlreadyHasEndEffector)
    {
        return ((linknumber) >= 0)&&(linknumber < (long) m_links.size());
    }
    else
    {
        return ((linknumber) > 0)&&(linknumber < (long) m_links.size());
    }
}

bool PDC::Robot::IsTrajectoryCalculated()
{
    return m_robotpositions[0]->IsTrajectoryCalculated();
}

bool PDC::Robot::CalculateTrajectories()
{
    unsigned long i;

    if (!IsTherePath())
        return false;

    for (i=0;i < m_robotpositions.size()-1;i++)
    {
        m_robotpositions[i]->CalculateRobotTrajectory();
    }

    return true;
}

void PDC::Robot::SetRobotName(string name)
{
    m_name = name;
}

string PDC::Robot::GetRobotName()
{
    return m_name;
}

void PDC::Robot::MoveRobotLinks(double time)
{
    unsigned long i = 0;

    while (i < m_robotpositions.size()-1)
    {
        // Verifica se o instante de tempo esta contido
        // no par de robotpositions
        if ((m_robotpositions[i]->GetInstantTime() <=  time)&&
            (m_robotpositions[i+1]->GetInstantTime() >= time))
            break;

        i++;
    }

    // O tempo fornecido esta fora do intervalo definido na trajetoria
    if (i == m_robotpositions.size())
        return;

    // A fórmula de trajetopria funciona para um tempo entre 0 e tf
    // daí a razão da subtracao no tempo abaixo
    m_robotpositions[i]->MoveRobotLinks(time - m_robotpositions[i]->GetInstantTime());
	//m_robotpositions[i]->MoveRobotLinks(time);
}

void PDC::Robot::AddLinkFirstPosition(Link * newlink)
{
    unsigned long aux;

    // Atualiza o numero dos links no robo
    for (aux = 0;aux < m_links.size();aux++)
        m_links[aux]->SetLinkNumber(m_links[aux]->GetLinkNumber()+1);

    newlink->SetLinkNumber(0);
    m_links.insert(m_links.begin(),newlink);
}

void PDC::Robot::AddLinkLastPosition(Link * newlink)
{
    newlink->SetLinkNumber(m_links.size());
    m_links.push_back(newlink);
}

void PDC::Robot::Draw()
{
    unsigned long count;

    long linknumber;


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for (count = 0; count < m_links.size(); count ++)
    {
        linknumber = m_links[count]->GetLinkNumber();
        m_links[count]->Draw();
    }
    glPopMatrix();
}

Link * PDC::Robot::GetLink(long linknumber)
{
    return m_links[linknumber];
}

RobotPosition * PDC::Robot::GetRobotPosition(long order)
{
    return m_robotpositions[order];
}

bool PDC::Robot::IsTherePath()
{
    return (m_robotpositions.size() > 0);
}

long PDC::Robot::SizeLink()
{
    return m_links.size();
}

double PDC::Robot::GetInitialTime()
{
    if (m_robotpositions.size() > 0)
        return m_robotpositions[0]->GetInstantTime();

    return 0.0;
}

double PDC::Robot::GetFinalTime()
{
    if (m_robotpositions.size() > 0)
        return m_robotpositions[m_robotpositions.size()-1]->GetInstantTime();

    return 0.0;
}

long PDC::Robot::SizeRobotPosition()
{
    return m_robotpositions.size();
}
