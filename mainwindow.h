//***********************************************************************  
 //<copyright file="Mainwindow.h" company="">  
 //     Copyright (c) . All rights reserved.  
 //</copyright>  
 //<summary>图像显示窗口类，负责图像的读取和显示等功能。</summary>  
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
	///图像数据集
	///</summary>
	GDALDataset *poDataset;
	///<summary>
	///图像的波段数
	///</summary>
	int nBandCount;

	/// <summary>  
	/// 判断是否显示RGB彩色图像  
	/// </summary>  
	bool m_showColor;

	/// <summary>  
	/// 缩放系数  
	/// </summary>  
	float m_scaleFactor;  

	/// <summary>  
	///   
	/// </summary>  
	QList <GDALRasterBand*>*imgBand;
	

	///<summary>
	///树列表数据模型
	///</summary>
	QStandardItemModel *model;
	
	Ui::MainWindowClass ui;
	QString fileName;//读入图像文件的文件名

	QLabel *label;
	QScrollArea *scrollArea ;

	QTreeView *treeView;

	QAction *openAction;

	QGraphicsView *graphicsView;
	
	void InitTree();//初始化左侧树

	void ShowImg(QList <GDALRasterBand*> *imgBand);   
	void ShowTree(const QString filename,int nBandCount);

	void ReadImg(const QString filename);

	void ShowBand(GDALRasterBand* band );  
	

private slots:
	void openFileSlot();
	//void treeItemChanged(QTreeWidgetItem* item,int column);
};

#endif // MAINWINDOW_H
