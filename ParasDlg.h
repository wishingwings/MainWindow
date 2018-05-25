#ifndef PRARSDLG_H
#define PRARSDLG_H

#include <QDialog>
 #include <QList>
#include <QDebug>
#include <QSignalMapper>
#include <QObject>
#include "ui_ParasDlg.h"
namespace Ui
{
	class ParasDlg;
};
class ParasDlg : public QDialog
{
	Q_OBJECT
public:
	ParasDlg(QWidget *parent);
	~ParasDlg();
	
	//查找界面中所有控件
	void FindControl();

	
private:
	Ui::ParasDlg *ui;
	QSignalMapper *signalMapper;  

private slots:  
	//void doClicked(const QString &btnname);  
	void ClickButton();
 
	
};
#endif // PRARSDLG_H