// PrismaticLinkType.cpp: implementation of the PrismaticLinkType class.
//
//////////////////////////////////////////////////////////////////////

#include "PrismaticLinkType.h"

#include <math.h>
#include "PersistentPrismaticLinkType.h"

using namespace DMC;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::PrismaticLinkType::PrismaticLinkType()
{
   m_persistentlinktype = new PersistentPrismaticLinkType(this);
   m_slide_type = "Prismatic";
}

PDC::PrismaticLinkType::~PrismaticLinkType()
{
   delete m_persistentlinktype;
}

double PDC::PrismaticLinkType::GetJointAngle()
{
    return m_joint_angle;
}

void PDC::PrismaticLinkType::SetJointAngle(double angle)
{
    m_joint_angle = angle;
}

void PDC::PrismaticLinkType::CalculateFrame(double variableparam,double (* frame)[4][4])
{
    // No tipo de link prismático,
    // os parametros de comprimento (link length),
    // torção (link twist) e ângulo da junta (joint angle)
    // são fixos mas o parâmetro de deslocamento da junta
    // (link offset) é variável por isso este parametro

    // é informado pelo link pois ele trata de aspectos
    // de cinemática.

    // Os elementos da matriz de frame e do sistema de coordenadas
    // estão posicionados em locais diferentes daqueles que estamos
    // acostumados para seguir um padrão estipulado pelo OpenGL na
    // descricao de matrizes

    (*frame)[0][0] = cos(m_joint_angle);
    (*frame)[1][0] = sin(m_joint_angle)*cos(m_link_twist);
    (*frame)[2][0] = sin(m_joint_angle)*sin(m_link_twist);
    (*frame)[3][0] = 0.0;

    (*frame)[0][1] = -sin(m_joint_angle);
    (*frame)[1][1] = cos(m_joint_angle)*cos(m_link_twist);
    (*frame)[2][1] = cos(m_joint_angle)*sin(m_link_twist);
    (*frame)[3][1] = 0.0;

    (*frame)[0][2] = 0.0;
    (*frame)[1][2] = -sin(m_link_twist);
    (*frame)[2][2] = cos(m_link_twist);
    (*frame)[3][2] = 0.0;

    (*frame)[0][3] = m_link_length;
    (*frame)[1][3] = -sin(m_link_twist)*variableparam;
    (*frame)[2][3] = cos(m_link_twist)*variableparam;
    (*frame)[3][3] = 1.0;
}
