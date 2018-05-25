#include "ParasDlg.h"
ParasDlg::ParasDlg(QWidget *parent)
	: QDialog(parent),ui(new Ui::ParasDlg)
{
	ui->setupUi(this);

			
	qDebug()<<"list count"<<ui->tabWidget->findChild<QLineEdit*>("focus");
	qDebug()<<"list count"<<ui->tabWidget->findChildren<QLineEdit*>();
	qDebug()<<"list count"<<ui->tabWidget->findChildren<QLineEdit*>().at(0);
	qDebug()<<"list count"<<ui->tabWidget->findChildren<QLineEdit*>().at(0)->objectName();
	qDebug()<<"list count"<<ui->tabWidget->findChildren<QLineEdit*>().at(0)->text();
	qDebug()<<"list count"<<ui->tabWidget->findChildren<QComboBox*>();
	qDebug()<<"list count"<<ui->tabWidget->findChildren<QComboBox*>().at(0)->currentIndex();
	qDebug()<<"list count"<<ui->tabWidget->findChildren<QComboBox*>().at(0)->currentText();

	connect(ui->okButton, SIGNAL(clicked()), this, SLOT(ClickButton()));
		
	

}
ParasDlg::~ParasDlg()
{
	delete ui;
}

void ParasDlg::ClickButton()
{
	qDebug()<<"Got it.Button Clicked";

	QStringList *LineEditList=new QStringList();
	QStringList *ComboBoxList=new QStringList();

	qDebug()<<"LineEdit number is"<<ui->tabWidget->findChildren<QLineEdit*>().count();
	qDebug()<<"ComboBox number is"<<ui->tabWidget->findChildren<QComboBox*>().count();
	qDebug()<<"list count"<<ui->tabWidget->findChildren<QComboBox*>();
	for(int i=0;i<ui->tabWidget->findChildren<QLineEdit*>().count();i++)
	{
		QString sLineEditName=ui->tabWidget->findChildren<QLineEdit*>().at(i)->objectName();
		LineEditList->append(sLineEditName);
		QString sLineEditValue=ui->tabWidget->findChildren<QLineEdit*>().at(i)->text();
		LineEditList->append(sLineEditValue);
	}

	for(int i=0;i<ui->tabWidget->findChildren<QComboBox*>().count();i++)

	{
		QString sComboBoxName=ui->tabWidget->findChildren<QComboBox*>().at(i)->objectName();
		ComboBoxList->append(sComboBoxName);
		int m=ui->tabWidget->findChildren<QComboBox*>().at(i)->currentIndex();
		ComboBoxList->append(QString::number(m,10));//把int转化为QString
		QString sComboBoxValue=ui->tabWidget->findChildren<QComboBox*>().at(i)->currentText();
		ComboBoxList->append(sComboBoxValue);
	}

	qDebug()<<"LineEditList is"<<*LineEditList;
	qDebug()<<"ComboBoxList is"<<*ComboBoxList;



}




/*void ParasDlg::slotButton(QString s)

{
	QList<QLineEdit *> allLEdit = this->findChildren<QLineEdit *>();


}*/