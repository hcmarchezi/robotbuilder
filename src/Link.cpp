// Link.cpp: implementation of the Link class.
//
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif

#include "Link.h"
#include <GL/glu.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::Link::Link(LinkType * linktype)
{
    m_linktype = linktype;
    m_variable_link_param = 0.0;

    double frame_aux[4][4];
    
    m_linktype->CalculateFrame(m_variable_link_param,&frame_aux);
    
    m_frame = new double[16];
    
    m_frame[0]  = frame_aux[0][0];
    m_frame[1]  = frame_aux[1][0];
    m_frame[2]  = frame_aux[2][0];
    m_frame[3]  = frame_aux[3][0];

    m_frame[4]  = frame_aux[0][1];
    m_frame[5]  = frame_aux[1][1];
    m_frame[6]  = frame_aux[2][1];
    m_frame[7]  = frame_aux[3][1];

    m_frame[8]  = frame_aux[0][2];
    m_frame[9]  = frame_aux[1][2];
    m_frame[10] = frame_aux[2][2];
    m_frame[11] = frame_aux[3][2];


    m_frame[12] = frame_aux[0][3];
    m_frame[13] = frame_aux[1][3];
    m_frame[14] = frame_aux[2][3];
    m_frame[15] = frame_aux[3][3];
}

PDC::Link::~Link()
{
    if (m_frame != NULL)
        delete m_frame;
}

long PDC::Link::GetLinkNumber()
{
    return m_number;
}

void PDC::Link::SetLinkNumber(long number)
{
    m_number = number;
}

long PDC::Link::GetLinkFunction()
{
    return m_linktype->GetLinkTypeFunction();
}

bool PDC::Link::LoadLink(string linkname)
{
    return false;
}

bool PDC::Link::SaveLink()
{
    return false;
}

void PDC::Link::Draw()
{
    m_linktype->Draw();
    glMultMatrixd(m_frame);
}

bool PDC::Link::VerifyJointRestriction(double movement)
{
    double lowestmovement,highestmovement;

    m_linktype->GetJointRestriction(lowestmovement,highestmovement);
    return ((movement >= lowestmovement)&&(movement <= highestmovement));
}

double PDC::Link::GetVariableLinkParam()
{
    return m_variable_link_param;
}

void   PDC::Link::SetVariableLinkParam(double movement)
{
    m_variable_link_param = movement;

    double frame_aux[4][4];
    
    m_linktype->CalculateFrame(movement,&frame_aux);

    delete m_frame;
    
    m_frame = new double[16];

    m_frame[0]  = frame_aux[0][0];
    m_frame[1]  = frame_aux[1][0];
    m_frame[2]  = frame_aux[2][0];
    m_frame[3]  = frame_aux[3][0];

    m_frame[4]  = frame_aux[0][1];
    m_frame[5]  = frame_aux[1][1];
    m_frame[6]  = frame_aux[2][1];
    m_frame[7]  = frame_aux[3][1];

    m_frame[8]  = frame_aux[0][2];
    m_frame[9]  = frame_aux[1][2];
    m_frame[10] = frame_aux[2][2];
    m_frame[11] = frame_aux[3][2];

    m_frame[12] = frame_aux[0][3];
    m_frame[13] = frame_aux[1][3];
    m_frame[14] = frame_aux[2][3];
    m_frame[15] = frame_aux[3][3];
}

LinkType * PDC::Link::GetLinkType()
{
    return this->m_linktype;
}

