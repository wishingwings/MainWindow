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

#include <QToolBar>
#include <QImage>
#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QCursor>
#include <QMouseEvent>

#include <QScrollBar>

#include <QGraphicsPixmapItem>

#include <QPoint>
#include <QToolBar>
 #include <QRectF>

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
	///</summary>
	///����ʼx����
	///</summary>
	int x0;

	
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
	
	///<summary>
	///������
	///</summary>
	QToolBar *pToolBar;

	///<summary>
	///������
	///</summary>
	QCursor cursior;

	QString fileName;//����ͼ���ļ����ļ���

	//QLabel *label;
	QScrollArea *scrollArea ;

	QTreeView *treeView;

	QAction *openAction;

	QGraphicsView *graphicsView;
	
	void InitTree();//��ʼ�������

	void ShowImg(QList <GDALRasterBand*> *imgBand);   
	void ShowTree(const QString filename,int nBandCount);

	void ReadImg(const QString filename);

	void ShowBand(GDALRasterBand* band );  

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);//��갴���ͷ��¼�
	void wheelEvent(QWheelEvent *event); // �����¼�



	

private slots:
	void openFileSlot();
	
	//������-ͼ�����εĲ�
	void panPicSlot();

	//������-ͼ��Ŵ�Ĳ�
	void MagnifyActionSlot();
};

#endif // MAINWINDOW_H
