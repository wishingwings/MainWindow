//***********************************************************************  
 //<copyright file="Mainwindow.h" company="">  
 //     Copyright (c) . All rights reserved.  
 //</copyright>  
 //<summary>图像显示窗口类，负责图像的读取和显示等功能。</summary>  
 //***********************************************************************  

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore/qmath.h>
#include <QtGui/QMainWindow>
#include <QtGui/QAction>
#include<QAbstractScrollArea>
#include <QColor>
#include <QCursor>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QLabel>
#include <QLayout>
#include <QList>
#include <QMatrix>
#include <QMouseEvent>
#include <QObject>


#include <QPainter>
#include <QRectF>
#include <QRect>
#include <QScrollBar>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStatusBar>
#include <QScrollBar>

#include <QPoint>
#include <QToolBar>
#include <QTextCodec>
#include <QTimer>
#include <QToolBar>
#include <QTreeView>

#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView> 

#include <QScrollArea>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>

#include "gdal_priv.h"
#include  "gdal.h"
#include "MyScene.h"
#include "rect.h"
#include "ParasDlg.h"
#include "ScrollArea.h"
#include "ui_mainwindow.h"
#include "ui_ParasDlg.h"
#include "XML.h"



class MainWindow :public QMainWindow
{
	Q_OBJECT

public:
	

	static QString fileName;//读入图像文件的文件名 //可以让MyScene.cpp访问的图像名
	/// <summary>  
	/// 载入图像放大缩小的系数  //可以让MyScene.cpp 访问
	/// </summary>  
	static float scaleFactor;

	///</summary>
	///记录QGraphicsView 垂直ScrollBar目前的位置 用在valueChangedSlot函数
	///</summary>
	static int vScrollBarNow;

	///</summary>
	///记录QGraphicsView 水平ScrollBar目前的位置 用在valueChangedSlot函数
	///</summary>
	static int hScrollBarNow;

	static QString operationName;//点击操作栏对象的名字 //可以让MyScene.cpp访问
	static QPoint pitem1TL;

	
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	
	~MainWindow();
	
	
private:
	
	//为了计算屏幕坐标和地理坐标的转化，计算比例尺
	//GraphicsView的长宽
	int widthGraphicsView;
	int heightGraphicsView;
	double maxLatitude;
	double minLatitude;
	double maxLongtitude;
	double minLongtitude;
	
	//读入图像的尺寸：长宽
	int width;    
	int height;  

	int mySceneDistX;
	int mySceneDistY;

	///</summary>
	///鼠标初始x坐标
	///</summary>
	int x0;

	///</summary>
	///鼠标初始y坐标
	///</summary>
	int y0;

	
	///<summary>
	///图像的波段数
	///</summary>
	int nBandCount;
	
	///<summary>
	///PanAction 需要移动的hscrollBar
	///</summary>
	int hScrollBarX;

	
	///</summary>
	///记录图片放大的次数
	///</summary>
	int iZoomIn;

	///</summary>
	///记录图片缩小的次数
	///</summary>
	int iZoomOut;
	
	/// <summary>  
	/// 判断是否显示RGB彩色图像  
	/// </summary>  
	bool m_showColor;
	 
	
	QAction *openAction;
	QAction *PanAction;
	QAction *SetParasAction;//打开配置参数界面
	QAction *MagnifyAction;
	QAction *NewROIAction;
	/// <summary>  
	///  读取图像的QImage格式
	/// </summary>  
	QImage *img;

	
	/// <summary>  
	///   
	/// </summary>  
	QList <GDALRasterBand*>*imgBand;

	
	///<summary>
	///图像数据集
	///</summary>
	GDALDataset *poDataset;
	

	///<summary>
	///树列表数据模型
	///</summary>
	QStandardItemModel *model;

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
	///状态栏
	///</summary>
	QStatusBar *statusBar;
	///<summary>
	///用于记录Toolbar上点击的Action的ActionName :记录需要后续在graphicview上进行操作的Action，需要是QStringList
	///方便Clcked()事件判断，这个Action是哪个对象发出的
    ///例如：图像放大，图像缩小，图像1：1显示
	///</summary>
	QStringList *strList;

	QScrollArea *scrollArea;
	///</summary>
	///ScrollArea的水平滚动条
	///</summary>

	QScrollBar *hScrollBar;
	///</summary>
	///ScrollArea的垂直滚动条
	///</summary>

	QScrollBar *vScrollBar;
	
	///<summary>
	///Matrix
	///用于graphicsItem的放大或缩小的Matrix
	///</summary>
	QMatrix matrix; 

	///<summary>
	///Matrix
	///用于记录graphicsItem 目前状态的放大或缩小的Matrix
	///</summary>
	QMatrix currMatrix; 



	QPainter *paint;
	

	QLabel *LabelGeoXY; //在状态栏上显示鼠标所在点的地理坐标
	//QScrollArea *scrollArea ;
	QTimer *timer;
	QTreeView *treeView;



	///<summary>
	///光标对象
	///用于graphicsview的光标
	///</summary>
	QCursor cursor;

	QGraphicsScene *pScene;
	MyScene *myScene;
	QGraphicsView *graphicsView;
	QGraphicsRectItem *item_rect;	
	QGraphicsPixmapItem *pItem;
	QGraphicsPixmapItem *pItem1;
	

	/// <summary>  
	/// 图像元数据模型  
	/// </summary>  
	QStandardItemModel *imgMetaModel;  
	Ui::MainWindowClass ui;
	ParasDlg *parasDlg;

	
	// <summary> 
	/// 图像亮度增加  
	/// </summary>  
	QImage* BrightnessAdd(QImage *origin);

	double CalScaleFactor(double maxLatitude,double minLatitude,double maxLongtitude,double minLongtitude,int widthGraphicsView,int heightGraphicsView);

	bool eventFilter(QObject *o, QEvent *e);
	void InitTree();//初始化左侧树

	
	
	void ShowBand(GDALRasterBand* band );  
		
	
	void getActionName(); //获取ActionName
	
	void ImgPtChangedScenePt(); //图像上的点得到屏幕场景坐标

	void mousePressEvent(QMouseEvent *event);

	void mouseReleaseEvent(QMouseEvent *event);

	void mouseMoveEvent(QMouseEvent *event);

	void ReadImg(const QString filename,int myScenedistX,int myScenedistY);//读出图像
	void ReadImgInfo(const QString filename);//读出图像基本信息
	void  RedrawROI(int i);//重绘myScene中的ROI
	 

	void resizeEvent();
	void ScaleImage(double factor);//图像缩放
	
	void ScenePtChangedImgPt(); //屏幕场景坐标得到图像上的点

	void ShowTree(const QString filename,int nBandCount);



signals:
	void clicked();
	void released();//绘制ROI，鼠标左键放开
	void timeout();//定时器每隔1秒钟发送信号，获取myscene类的鼠标坐标转化成的地理坐标
	void sliderPressed ();//水平滚动条滚动条位置变化

	void valueChanged(int);//垂直滚动条位置变化
	
private slots:
	void openFileSlot();
	
	//弹出设置参数界面的槽
	void setParasSlot();
	
	//工具栏-图像漫游的槽
	void panPicSlot();

	//工具栏-图像放大的槽
	void MagnifyActionSlot();

	//工具栏-新建ROI的槽
	void NewROIActionSlot();		
	
	

	//工具栏-新建ROI的槽
	void DeleteROIActionSlot();
	
	//状态栏定时器的槽
	void timeUpdate();

	void VerticalScrollBarValueChangedSlot(int);//垂直滚动条滚动条位置变化的槽

	void HorizontalScrollBarValueChangedSlot(int);//水平滚动条位置变化的槽
	

	void isPressed();
	void isReleased();
	virtual void mousePressEventSlot();

	//virtual void mouseReleaseEventSlot();
};

#endif // MAINWINDOW_H
