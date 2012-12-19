// WView.cpp: implementation of the WView class.
//
//////////////////////////////////////////////////////////////////////

#include "WView.h"

#include <qslider.h>
#include <qlabel.h>
#include <q3frame.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>

#include "GLObject.h"
#include "QHSpinBox.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HIC::WView::WView(QWidget * parent,const char * name,GraphicObject * graphicobject):QWidget(parent,name)
{
    // Window Title
    setCaption(name);

    /////////////////////////////////////////////////////////////////
    // Create widgets
    /////////////////////////////////////////////////////////////////

    //  OpenGL frame
    Q3Frame * frame = new Q3Frame (this,"frame");
    frame->setFrameStyle ( Q3Frame::Sunken | Q3Frame::Panel );
    frame->setLineWidth(2);
    frame->setMinimumSize(450,450);

    // OpenGL widget
    m_globjectwidget = new GLObject(frame,"globjectwidget",graphicobject);

    // Rotation and translation controls
    QLabel * labeltitle = new QLabel("Coordinate System",this,"labeltitle");

    QLabel * labelrotx = new QLabel ("X Rotation (Degrees)",this,"labelrotx");
    QHSpinBox * spinrotx = new QHSpinBox (-3.14,3.14,0.0,10,this,"spinrotx");
    QObject::connect (spinrotx,SIGNAL(valueChanged(double)),m_globjectwidget,SLOT(setXRotation(double)) );

    QLabel * labelroty = new QLabel ("Y Rotation (Degress)",this,"labelroty");
    QHSpinBox * spinroty = new QHSpinBox (-3.14,3.14,0.0,10,this,"spinroty");
    QObject::connect (spinroty,SIGNAL(valueChanged(double)),m_globjectwidget,SLOT(setYRotation(double)) );
    
    QLabel * labelrotz = new QLabel ("Z Rotation (Degrees)",this,"labelrotz");
    QHSpinBox * spinrotz = new QHSpinBox (-3.14,3.14,0.0,10,this,"spinrotz");
    QObject::connect (spinrotz,SIGNAL(valueChanged(double)),m_globjectwidget,SLOT(setZRotation(double)) );

    QLabel * labeldesx = new QLabel ("X Translation",this,"labeldesx");
    QHSpinBox * spindesx = new QHSpinBox (-3.14,3.14,0.0,10,this,"spindesx");
    QObject::connect (spindesx,SIGNAL(valueChanged(double)),m_globjectwidget,SLOT(setXTranslation(double)) );

    QLabel * labeldesy = new QLabel ("Y Translation",this,"labeldesy");
    QHSpinBox * spindesy = new QHSpinBox (-3.14,3.14,0.0,10,this,"spindesy");
    QObject::connect (spindesy,SIGNAL(valueChanged(double)),m_globjectwidget,SLOT(setYTranslation(double)) );

    QLabel * labeldesz = new QLabel ("Z Translation",this,"labeldesz");
    QHSpinBox * spindesz = new QHSpinBox (-3.14,3.14,0.0,10,this,"spindesz");
    QObject::connect (spindesz,SIGNAL(valueChanged(double)),m_globjectwidget,SLOT(setZTranslation(double)) );

    QLabel * labelzoom = new QLabel ("Zoom",this,"labelzoom");
    QHSpinBox * spinzoom = new QHSpinBox (-5.0,5.0,1.0,0.1,this,"spinzoom");
    QObject::connect (spinzoom,SIGNAL(valueChanged(double)),m_globjectwidget,SLOT(setZoom(double)) );

    /////////////////////////////////////////////////////////////////
    // Organize global coordinate system rotation controls in vertical
    /////////////////////////////////////////////////////////////////

    Q3VBoxLayout * layout_controls = new Q3VBoxLayout(10,"layout_controls");
    layout_controls->addWidget (labeltitle);
    layout_controls->addWidget (labelrotx);
    layout_controls->addWidget (spinrotx);

    layout_controls->addWidget (labelroty);
    layout_controls->addWidget (spinroty);
    layout_controls->addWidget (labelrotz);
    layout_controls->addWidget (spinrotz);
    layout_controls->addWidget (labeldesx);
    layout_controls->addWidget (spindesx);
    layout_controls->addWidget (labeldesy);
    layout_controls->addWidget (spindesy);
    layout_controls->addWidget (labeldesz);
    layout_controls->addWidget (spindesz);
    layout_controls->addWidget (labelzoom);
    layout_controls->addWidget (spinzoom);
	layout_controls->setResizeMode (QLayout::SetFixedSize);

    /////////////////////////////////////////////////////////////////
    // Places m_globjectwidget inside the frame
    /////////////////////////////////////////////////////////////////
    Q3HBoxLayout * layout_frame = new Q3HBoxLayout (frame,2,2,"layout_frame");
    layout_frame->addWidget(m_globjectwidget,1);

    /////////////////////////////////////////////////////////////////
    // window layout: Controls in one side frames in another side
    /////////////////////////////////////////////////////////////////
    if (layout() == NULL)

        m_layout_window = new Q3HBoxLayout(this,20,20,"m_layout_window");
    else 
        m_layout_window = (Q3HBoxLayout *) layout();

    m_layout_window->addLayout(layout_controls);
    m_layout_window->addWidget(frame,1);

}



HIC::WView::~WView()
{

}


bool HIC::WView::close(bool alsoDelete)
{
    return QWidget::close(alsoDelete);
}
