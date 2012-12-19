/****************************************************************************
** Form interface generated from reading ui file 'WRobotCreation.ui'
**
** Created: Mon Nov 1 13:58:45 2004
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef WROBOTCREATION_H
#define WROBOTCREATION_H

#include <qvariant.h>
#include <qdialog.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <QLabel>
class Q3VBoxLayout; 
class Q3HBoxLayout; 
class Q3GridLayout; 
class Q3GroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class Q3Table;

namespace HIC
{

class WRobotCreation : public QDialog
{ 
    Q_OBJECT

public:
    WRobotCreation( QWidget* parent = 0, const char* name = 0, bool modal = TRUE, Qt::WFlags fl = 0 );
    ~WRobotCreation();

    QLabel* m_lb_name;
    QLineEdit* m_edt_name;
    Q3GroupBox* m_grp_base;
    Q3Table* m_tab_base;
    QPushButton* m_bt_save;
    QPushButton* m_bt_cancel;

	bool IsSaved();

public slots:
	void bt_save_clicked();
	void bt_cancel_clicked();

protected:
	bool bSalved;



};

}

#endif // WROBOTCREATION_H
