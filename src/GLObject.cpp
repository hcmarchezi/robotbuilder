// GLObject.cpp: implementation of the GLObject class.
//
//////////////////////////////////////////////////////////////////////

#include "GLObject.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HIC::GLObject::GLObject(QWidget * parent,const char * name,GraphicObject * graphicobject):QGLWidget(parent,name)
{
    // As variaveis de rotacao e zoom nao contem o valor atual mas apenas 
	// a variacao
	m_rotX = m_rotY = m_rotZ = m_transX = m_transY = m_transZ = 0.0;
    m_zoom = 1.0;
    m_graphicobject = graphicobject;
}

HIC::GLObject::~GLObject()
{

}

void HIC::GLObject::SetGraphicObject(GraphicObject * graphicobject)
{
	m_graphicobject = graphicobject;
}

GraphicObject * HIC::GLObject::GetGraphicObject()
{
	return m_graphicobject;
}


void HIC::GLObject::setXRotation(double degrees)
{
    GLfloat deltaX =  (GLfloat) fmod(degrees,360.0) - m_rotX;

	glMatrixMode(GL_PROJECTION);
	glRotatef(deltaX,1.0f,0.0f,0.0f);

	m_rotX = (GLfloat) fmod(degrees,360.0);
    updateGL();
}

void HIC::GLObject::setYRotation(double degrees)
{
	GLfloat deltaY = (GLfloat) fmod(degrees,360.0) - m_rotY;
    
	glMatrixMode(GL_PROJECTION);
	glRotatef(deltaY,0.0f,1.0f,0.0f);

	m_rotY = (GLfloat) fmod(degrees,360.0);
    updateGL();
}

void HIC::GLObject::setZRotation(double degrees)
{
	GLfloat deltaZ = (GLfloat) fmod(degrees,360.0) - m_rotZ;
    
	glMatrixMode(GL_PROJECTION);
	glRotatef(deltaZ,0.0f,0.0f,1.0f);

	m_rotZ = (GLfloat) fmod(degrees,360.0);
    updateGL();
}

void HIC::GLObject::setZoom(double zoom)
{
    GLfloat deltaZoom = (GLfloat) zoom - m_zoom;
		
	glMatrixMode(GL_PROJECTION);
	if (deltaZoom > 0)
	{
		glScalef(1.5f,1.5f,1.5f);
	}
	else
	{
		glScalef(0.75f,0.75f,0.75f);
	}	
	
	m_zoom = (GLfloat) zoom;
    updateGL();
}

void HIC::GLObject::setXTranslation(double move)
{
    m_transX = (GLfloat) move;
    updateGL();
}

void HIC::GLObject::setYTranslation(double move)
{
    m_transY = (GLfloat) move;
    updateGL();
}

void HIC::GLObject::setZTranslation(double move)
{
    m_transZ = (GLfloat) move;
    updateGL();
}

void HIC::GLObject::initializeGL()
{
    GLfloat max = 2000.0f; /////////

    glEnable(GL_DEPTH_TEST);
	glOrtho(-max,max,-max,max,-max,max);
	glClearColor (0.0f,0.0f,0.0f,1.0f);
    glColor3f(1.0f,1.0f,1.0f);
    
	//glRotatef(-180.0,0.0f,1.0f,0.0f);
    //glRotatef(90.0f,0.0,0.0f,1.0f);
    //glTranslatef(-1200.0f,0.0f,0.0f);
    //glScalef(1.2f,1.2f,1.2f);
}

void HIC::GLObject::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

    //glRotatef(m_rotX,1.0f,0.0f,0.0f);
	//glRotatef(m_rotY,0.0f,1.0f,0.0f);
	//glRotatef(m_rotZ,0.0f,0.0f,1.0f);
	//glScalef(m_zoom,m_zoom,m_zoom);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(m_transX,m_transY,m_transZ);

	glBegin(GL_LINES);
		glColor3f ( 1.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f(30.0f, 0.0f, 0.0f);
		glColor3f ( 0.0f, 1.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f,30.0f, 0.0f);
		glColor3f ( 0.0f, 0.0f, 1.0f);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f,30.0f);
	glEnd();

    makeObject();
	
	glPopMatrix();
	
}

void HIC::GLObject::resizeGL(int w, int h)
{

   // Prevenindo divisao por zero
   if (h==0) h = 1;
   if (w==0) w = 1;

    // Mantendo o aspecto quadrado da Viewport
    if (w <= h)
     {
           glViewport (0,0, (GLint)w, (GLint)w );
     }
     else
     {
           glViewport (0,0, (GLint)h, (GLint)h );
     }
}


void HIC::GLObject::makeObject()
{
    //glutWireTeapot(500.0);
	// Desenha o objeto se ele nao for 
	// uma referencia nula
	if (m_graphicobject != NULL)
	{
		m_graphicobject->Draw();
	}
}
