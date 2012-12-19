// QHSpinBox.h: interface for the QHSpinBox class.
//
//////////////////////////////////////////////////////////////////////

#ifndef QHSPINBOX_H
#define QHSPINBOX_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
//#include <qsignal.h>

namespace HIC
{

class QHSpinBox : public QWidget
{
    Q_OBJECT

public:
    QHSpinBox(double minValue,double maxValue,double initialValue,double step = 1,QWidget * parent = 0,const char * name = 0);
    virtual ~QHSpinBox();

public slots:
	void stepDown();
	void stepUp();
	void setValue(double value);
        void returnPressed();

signals:
    void valueChanged (double value);
    

private:
    QPushButton * m_leftbutton;
    QPushButton * m_rightbutton;
    QLineEdit  * m_lineedit;
    double m_max_value;
    double m_min_value;
    double m_value;
    double m_step;
    //QSignal * m_signal;
};

}

#endif


