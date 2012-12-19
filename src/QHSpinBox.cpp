// QHSpinBox.cpp: implementation of the QHSpinBox class.
//
//////////////////////////////////////////////////////////////////////

#include "QHSpinBox.h"

#include <qlayout.h>
#include <qmessagebox.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <math.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HIC::QHSpinBox::QHSpinBox(double minValue,double maxValue,double initialValue,double step,QWidget * parent,const char * name):QWidget(parent,name)
{
    m_min_value = minValue;
    m_max_value = maxValue;
    m_step      = step;
    m_value     = initialValue;    

    m_leftbutton  = new QPushButton("<<",this,"leftbutton");
    m_leftbutton->setAutoRepeat(true);
    QObject::connect(m_leftbutton, SIGNAL(clicked()), this, SLOT(stepDown()));
    m_rightbutton = new QPushButton(">>",this,"rightbutton");
    m_rightbutton->setAutoRepeat(true);
    QObject::connect(m_rightbutton ,SIGNAL(clicked()),this, SLOT(stepUp()));

    m_lineedit = new QLineEdit(QString::number(m_value),this,"lineedit");
    m_lineedit->setMaximumSize(60,20);
    QObject::connect(m_lineedit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

    Q3HBoxLayout * layout = new Q3HBoxLayout(this,1,5,"hspinlayout");
    layout->addWidget(m_leftbutton);
    layout->addWidget(m_lineedit);
    layout->addWidget(m_rightbutton);
    layout->setResizeMode(QLayout::SetFixedSize);
}

HIC::QHSpinBox::~QHSpinBox()
{

}

void HIC::QHSpinBox::setValue(double value)
{
    m_value = value;
    m_lineedit->setText(QString::number(value));
    emit valueChanged(value);
}

void HIC::QHSpinBox::stepUp()
{
    m_value = m_value + m_step;
    if (fabs(m_value) < m_step) m_value = 0.0;
    m_lineedit->setText(QString::number(m_value));
    emit valueChanged(m_value);
}

void HIC::QHSpinBox::stepDown()
{
    m_value = m_value - m_step;
    if (fabs(m_value) < m_step) m_value = 0.0;
    m_lineedit->setText(QString::number(m_value));
    emit valueChanged(m_value);
}


void HIC::QHSpinBox::returnPressed()
{
    m_value = m_lineedit->text().toDouble();
    emit valueChanged(m_value);
}

