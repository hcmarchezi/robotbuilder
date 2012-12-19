// RevoluteLinkType.cpp: implementation of the RevoluteLinkType class.
//
//////////////////////////////////////////////////////////////////////

#include "RevoluteLinkType.h"

#include <math.h>
#include "PersistentRevoluteLinkType.h"

using namespace DMC;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::RevoluteLinkType::RevoluteLinkType()
{
    m_persistentlinktype = new PersistentRevoluteLinkType(this);
	m_slide_type = "Revolute";
}

PDC::RevoluteLinkType::~RevoluteLinkType()
{
	delete m_persistentlinktype;
}

double PDC::RevoluteLinkType::GetLinkOffset()
{
    return m_link_offset;
}

void PDC::RevoluteLinkType::SetLinkOffset(double offset)
{
    m_link_offset = offset;
}

void PDC::RevoluteLinkType::CalculateFrame(double variableparam,double (* frame)[4][4])
{
    // No tipo de link cuja a junta é de revolução,
    // os parametros de comprimento (link length),
    // torção (link twist) e deslocamento da junta (link offset)
    // são fixos mas o parâmetro de ângulo da junta
    // (joint angle) é variável por isso este parametro eh informado
    // pelo link pois ele trata de aspectos de cinemática.

    // Os elementos da matriz de frame e do sistema de coordenadas
    // estão posicionados em locais diferentes daqueles que estamos
    // acostumados para seguir um padrão estipulado pelo OpenGL na
    // descricao de matrizes

    (*frame)[0][0] = cos(variableparam);
    (*frame)[1][0] = sin(variableparam)*cos(m_link_twist);
    (*frame)[2][0] = sin(variableparam)*sin(m_link_twist);
    (*frame)[3][0] = 0.0;


    (*frame)[0][1] = -sin(variableparam);
    (*frame)[1][1] = cos(variableparam)*cos(m_link_twist);
    (*frame)[2][1] = cos(variableparam)*sin(m_link_twist);
    (*frame)[3][1] = 0.0;

    (*frame)[0][2] = 0.0;
    (*frame)[1][2] = -sin(m_link_twist);
    (*frame)[2][2] = cos(m_link_twist);
    (*frame)[3][2] = 0.0;

    (*frame)[0][3] = m_link_length;
    (*frame)[1][3] = -sin(m_link_twist)*m_link_offset;
    (*frame)[2][3] = cos(m_link_twist)*m_link_offset;
    (*frame)[3][3] = 1.0;
}
