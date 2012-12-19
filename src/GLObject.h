// GLObject.h: interface for the GLObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GLOBJECT_H
#define GLOBJECT_H

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/glu.h>
//#include <qgl.h>
#include <QGLViewer/config.h>
#include <QGLViewer/domUtils.h>
#include <QGLViewer/qglviewer.h>

#include "GraphicObject.h"

using namespace PDC;

namespace HIC
{

class GLObject : public QGLWidget  
{
    Q_OBJECT

public:
	GLObject(QWidget * parent,const char * name,GraphicObject * graphicobject);
	virtual ~GLObject();
	void SetGraphicObject(GraphicObject * graphicobject);
	GraphicObject * GetGraphicObject();

public slots:
	virtual void makeObject();
    void setZTranslation ( double move );
	void setYTranslation ( double move );
	void setXTranslation ( double move );
	void setZoom (double zoom);
	void setZRotation ( double degrees );
	void setYRotation ( double degrees );
	void setXRotation ( double degrees );

protected:
	void resizeGL ( int w, int h );
	void paintGL();
	void initializeGL();
        // Graphic Object
        GraphicObject * m_graphicobject;


private:
    // Rotation and translation variables for OpenGL object
    GLfloat m_rotX,m_rotY,m_rotZ,m_zoom,m_transX,m_transY,m_transZ;

};

}

#endif


