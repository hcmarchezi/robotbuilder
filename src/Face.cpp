// Face.cpp: implementation of the Face class.
//
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif

#include "Face.h"

#include <GL/glu.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::Face::Face()
{

}

PDC::Face::~Face()
{

}

void PDC::Face::GetParameters(Point &vertex_1, Point &vertex_2, Point &vertex_3, long &red, long &green, long &blue)
{
	vertex_1 = m_vertex_1;
	vertex_2 = m_vertex_2;
	vertex_3 = m_vertex_3;
	red      = m_red;
	green    = m_green;
	blue     = m_blue;
}

void PDC::Face::SetParameters(Point vertex_1, Point vertex_2, Point vertex_3, long red, long green, long blue)
{
	m_vertex_1 = vertex_1;
    m_vertex_2 = vertex_2;
	m_vertex_3 = vertex_3;
	m_red      = red;
	m_green    = green;
	m_blue     = blue;
}  

void PDC::Face::Draw()
{
      glColor3ub(0,0,200);
    
    glBegin(GL_TRIANGLES);
        glVertex3f(m_vertex_1.x,m_vertex_1.y,m_vertex_1.z);
        glVertex3f(m_vertex_2.x,m_vertex_2.y,m_vertex_2.z);
        glVertex3f(m_vertex_3.x,m_vertex_3.y,m_vertex_3.z);
    glEnd();
    
    
    glColor3ub(m_red,m_green,m_blue);
    
    glBegin(GL_LINE_LOOP);
        glVertex3f(m_vertex_1.x,m_vertex_1.y,m_vertex_1.z);
        glVertex3f(m_vertex_2.x,m_vertex_2.y,m_vertex_2.z);
        glVertex3f(m_vertex_3.x,m_vertex_3.y,m_vertex_3.z);
    glEnd();
}
