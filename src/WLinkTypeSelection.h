/****************************************************************************
** Form interface generated from reading ui file 'WLinkTypeSelection.ui'
**
** Created: Wed Nov 3 12:32:16 2004
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef WLINKTYPESELECTION_H
#define WLINKTYPESELECTION_H

#include <qvariant.h>
#include <qdialog.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
class Q3VBoxLayout; 
class Q3HBoxLayout; 
class Q3GridLayout; 
class Q3GroupBox;
class QLineEdit;
class QPushButton;


namespace HIC
{

class WLinkTypeSelection : public QDialog
{ 
    Q_OBJECT

public:
    WLinkTypeSelection( QWidget* parent = 0, const char* name = 0, bool modal = TRUE, Qt::WFlags fl = 0 );
    ~WLinkTypeSelection();

	bool IsAdded();

    Q3GroupBox* m_grp_filename;
    QLineEdit* m_edt_filename;
    QPushButton* m_bt_load;
    QPushButton* m_bt_cancel;
    QPushButton* m_bt_add;
    Q3GroupBox* m_grp_linknumber;
    QLineEdit* m_edt_numlink;

protected:
	bool m_b_added;

public slots:

	void bt_add_clicked();
	void bt_cancel_clicked();
	void bt_load_clicked();

};

}

#endif // WLINKTYPESELECTION_H
