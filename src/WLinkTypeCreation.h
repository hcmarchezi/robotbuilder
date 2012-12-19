/****************************************************************************
** Form interface generated from reading ui file 'WLinkTypeCreation.ui'
**
** Created: Thu Oct 28 11:56:41 2004
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef WLINKTYPECREATION_H
#define WLINKTYPECREATION_H

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
class QComboBox;
class Q3GroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class Q3Table;

namespace HIC
{

class WLinkTypeCreation : public QDialog
{ 
    Q_OBJECT

public:
    WLinkTypeCreation( QWidget* parent = 0, const char* name = 0, bool modal = TRUE, Qt::WFlags fl = 0 );
    ~WLinkTypeCreation();

    QLabel* lbNome;
    QLineEdit* txtNome;
    QLabel* lbFuncao;
    QLabel* lbTorcao;
    Q3GroupBox* grpGeometria;
    QLabel* lbGeometria;
    QLabel* lbNomeObjetoGeometrico;
    QLineEdit* txtGeometria;
    QComboBox* cmbxGeometria;
	QPushButton* btCarregarGeometria;
    QLabel* lbTipoJunta;
    QLabel* lbParametroFixo;
    QLabel* lbComprimento;
    QLineEdit* txtParametroFixo;
    QLineEdit* txtTorcao;
    Q3GroupBox* grpSistemaCoordenadas;
    Q3Table* tabCoordenadasLocais;
    QComboBox* cmbxTipoJunta;
    QLineEdit* txtComprimento;
    Q3GroupBox* grpMobilidadeJunta;
    QLabel* lbMovimentoMaximo;
    QLineEdit* txtMovimentoMinimo;
    QLineEdit* txtMovimentoMaximo;
    QLabel* lbMovimentoMinimo;
    QComboBox* cmbxFuncao;
    QPushButton* btSalvar;
    QPushButton* btCancelar;
	QPushButton* btSelecionarArquivo;

	bool salvar();

public slots:
	void cmbxTipoJunta_activated(const QString & strText);
	void btCarregar_clicked();
	void btSelecionarArquivo_clicked();
	void btSalvar_clicked();
	void btCancelar_clicked();

protected:
	bool bSalvar;


};

}

#endif // WLINKTYPECREATION_H
