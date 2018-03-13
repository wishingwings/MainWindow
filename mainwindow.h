//***********************************************************************  
 //<copyright file="Mainwindow.h" company="">  
 //     Copyright (c) . All rights reserved.  
 //</copyright>  
 //<summary>ͼ����ʾ�����࣬����ͼ��Ķ�ȡ����ʾ�ȹ��ܡ�</summary>  
 //***********************************************************************  

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QAction>
#include "ui_mainwindow.h"
#include <QImage>
#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>

#include <QGraphicsPixmapItem>

#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include <QDir>
#include <QLayout>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView> 

#include <QScrollArea>
#include <QMessageBox>
#include<QMenuBar>
#include <QObject>
#include <gdal_priv.h>
#include <gdal.h>

class MainWindow :public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	///<summary>
	///ͼ�����ݼ�
	///</summary>
	GDALDataset *poDataset;
	///<summary>
	///ͼ��Ĳ�����
	///</summary>
	int nBandCount;

	/// <summary>  
	/// �ж��Ƿ���ʾRGB��ɫͼ��  
	/// </summary>  
	bool m_showColor;

	/// <summary>  
	/// ����ϵ��  
	/// </summary>  
	float m_scaleFactor;  

	/// <summary>  
	///   
	/// </summary>  
	QList <GDALRasterBand*>*imgBand;
	

	///<summary>
	///���б�����ģ��
	///</summary>
	QStandardItemModel *model;
	
	Ui::MainWindowClass ui;
	QString fileName;//����ͼ���ļ����ļ���

	QLabel *label;
	QScrollArea *scrollArea ;

	QTreeView *treeView;

	QAction *openAction;

	QGraphicsView *graphicsView;
	
	void InitTree();//��ʼ�������

	void ShowImg(QList <GDALRasterBand*> *imgBand);   
	void ShowTree(const QString filename,int nBandCount);

	void ReadImg(const QString filename);

	void ShowBand(GDALRasterBand* band );  
	

private slots:
	void openFileSlot();
	//void treeItemChanged(QTreeWidgetItem* item,int column);
};

#endif // MAINWINDOW_H
