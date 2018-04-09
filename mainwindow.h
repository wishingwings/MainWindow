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
#include <QCursor>
#include <QImage>
#include <QList>
#include "rect.h"
#include "ui_mainwindow.h"
#include "myscene.h"

#include <QPainter>

#include <QTextCodec>
#include <QToolBar>

#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>

#include <QMouseEvent>

#include <QScrollBar>

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>
 #include <QGraphicsSceneMouseEvent>

#include <QPainter>

#include <QPoint>
#include <QToolBar>
#include <QRectF>
#include <QRect>

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
	///鼠标初始x坐标
	///</summary>
	int x0;

	///</summary>
	///鼠标初始y坐标
	///</summary>
	int y0;

	
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
	
	///<summary>
	///工具栏
	///</summary>
	QToolBar *pToolBar;
	///<summary>
	///事件过滤器对象
	///</summary>
	QObject *obj;

	///<summary>
	///点对象 记录鼠标在Graphicsview选择ROI的起始点和最后的点
	///</summary>
	QPoint  currentPos;
	QPoint  endPos;


	///<summary>
	///用于记录Toolbar上点击的Action的ActionName :记录需要后续在graphicview上进行操作的Action，需要是QStringList
	///方便Clcked()事件判断，这个Action是哪个对象发出的
    ///例如：图像放大，图像缩小，图像1：1显示
	///</summary>
	QStringList *strList;
	
	///<summary>
	///Matrix
	///用于graphicsview的放大或缩小的Matrix
	///</summary>

	QMatrix matrix; 


	QPainter *paint;
	///<summary>
	///光标对象
	///用于graphicsview的光标
	///</summary>
	QCursor cursor;

	QString fileName;//读入图像文件的文件名

	//QLabel *label;
	QScrollArea *scrollArea ;

	QTreeView *treeView;

	QAction *openAction;
	QAction *PanAction;
	QAction *MagnifyAction;
	QAction *NewROIAction;

	QGraphicsScene *pScene;
	MyScene *myScene;
	QGraphicsView *graphicsView;
	QGraphicsRectItem *item_rect;	
	QGraphicsPixmapItem *pItem;

	/// <summary>  
	/// 图像元数据模型  
	/// </summary>  
	QStandardItemModel *imgMetaModel;  
	
	void InitTree();//初始化左侧树

	//void ShowImg(QList <GDALRasterBand*> *imgBand);   
	void ShowTree(const QString filename,int nBandCount);

	void ReadImg(const QString filename);//读出图像

	void ReadImgInfo(const QString filename);//读出图像基本信息

	void ShowBand(GDALRasterBand* band );  
		
	void mousePressEvent(QMouseEvent *event);

	void mouseReleaseEvent(QMouseEvent *event);

	//void paintEvent(QPaintEvent *event);
	
	void getActionName(); //获取ActionName

	void resizeEvent();
signals:
	void clicked();
	void released();//绘制ROI，鼠标左键放开
	//void RectMouseIsPressed();
	

private slots:
	void openFileSlot();
	
	//工具栏-图像漫游的槽
	void panPicSlot();

	//工具栏-图像放大的槽
	void MagnifyActionSlot();

	//工具栏-新建ROI的槽
	void NewROIActionSlot();

	void isPressed();
	void isReleased();
	virtual void mousePressEventSlot();

	//virtual void mouseReleaseEventSlot();
};

#endif // MAINWINDOW_H
