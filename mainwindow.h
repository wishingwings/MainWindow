//***********************************************************************  
 //<copyright file="Mainwindow.h" company="">  
 //     Copyright (c) . All rights reserved.  
 //</copyright>  
 //<summary>ͼ����ʾ�����࣬����ͼ��Ķ�ȡ����ʾ�ȹ��ܡ�</summary>  
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
	

	static QString fileName;//����ͼ���ļ����ļ��� //������MyScene.cpp���ʵ�ͼ����
	/// <summary>  
	/// ����ͼ��Ŵ���С��ϵ��  //������MyScene.cpp ����
	/// </summary>  
	static float scaleFactor;

	///</summary>
	///��¼QGraphicsView ��ֱScrollBarĿǰ��λ�� ����valueChangedSlot����
	///</summary>
	static int vScrollBarNow;

	///</summary>
	///��¼QGraphicsView ˮƽScrollBarĿǰ��λ�� ����valueChangedSlot����
	///</summary>
	static int hScrollBarNow;

	static QString operationName;//������������������ //������MyScene.cpp����
	static QPoint pitem1TL;

	
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	
	~MainWindow();
	
	
private:
	
	//Ϊ�˼�����Ļ����͵��������ת�������������
	//GraphicsView�ĳ���
	int widthGraphicsView;
	int heightGraphicsView;
	double maxLatitude;
	double minLatitude;
	double maxLongtitude;
	double minLongtitude;
	
	//����ͼ��ĳߴ磺����
	int width;    
	int height;  

	int mySceneDistX;
	int mySceneDistY;

	///</summary>
	///����ʼx����
	///</summary>
	int x0;

	///</summary>
	///����ʼy����
	///</summary>
	int y0;

	
	///<summary>
	///ͼ��Ĳ�����
	///</summary>
	int nBandCount;
	
	///<summary>
	///PanAction ��Ҫ�ƶ���hscrollBar
	///</summary>
	int hScrollBarX;

	
	///</summary>
	///��¼ͼƬ�Ŵ�Ĵ���
	///</summary>
	int iZoomIn;

	///</summary>
	///��¼ͼƬ��С�Ĵ���
	///</summary>
	int iZoomOut;
	
	/// <summary>  
	/// �ж��Ƿ���ʾRGB��ɫͼ��  
	/// </summary>  
	bool m_showColor;
	 
	
	QAction *openAction;
	QAction *PanAction;
	QAction *SetParasAction;//�����ò�������
	QAction *MagnifyAction;
	QAction *NewROIAction;
	/// <summary>  
	///  ��ȡͼ���QImage��ʽ
	/// </summary>  
	QImage *img;

	
	/// <summary>  
	///   
	/// </summary>  
	QList <GDALRasterBand*>*imgBand;

	
	///<summary>
	///ͼ�����ݼ�
	///</summary>
	GDALDataset *poDataset;
	

	///<summary>
	///���б�����ģ��
	///</summary>
	QStandardItemModel *model;

	///<summary>
	///������
	///</summary>
	QToolBar *pToolBar;
	///<summary>
	///�¼�����������
	///</summary>
	QObject *obj;

	///<summary>
	///����� ��¼�����Graphicsviewѡ��ROI����ʼ������ĵ�
	///</summary>
	QPoint  currentPos;
	QPoint  endPos;

	
	///<summary>
	///״̬��
	///</summary>
	QStatusBar *statusBar;
	///<summary>
	///���ڼ�¼Toolbar�ϵ����Action��ActionName :��¼��Ҫ������graphicview�Ͻ��в�����Action����Ҫ��QStringList
	///����Clcked()�¼��жϣ����Action���ĸ����󷢳���
    ///���磺ͼ��Ŵ�ͼ����С��ͼ��1��1��ʾ
	///</summary>
	QStringList *strList;

	QScrollArea *scrollArea;
	///</summary>
	///ScrollArea��ˮƽ������
	///</summary>

	QScrollBar *hScrollBar;
	///</summary>
	///ScrollArea�Ĵ�ֱ������
	///</summary>

	QScrollBar *vScrollBar;
	
	///<summary>
	///Matrix
	///����graphicsItem�ķŴ����С��Matrix
	///</summary>
	QMatrix matrix; 

	///<summary>
	///Matrix
	///���ڼ�¼graphicsItem Ŀǰ״̬�ķŴ����С��Matrix
	///</summary>
	QMatrix currMatrix; 



	QPainter *paint;
	

	QLabel *LabelGeoXY; //��״̬������ʾ������ڵ�ĵ�������
	//QScrollArea *scrollArea ;
	QTimer *timer;
	QTreeView *treeView;



	///<summary>
	///������
	///����graphicsview�Ĺ��
	///</summary>
	QCursor cursor;

	QGraphicsScene *pScene;
	MyScene *myScene;
	QGraphicsView *graphicsView;
	QGraphicsRectItem *item_rect;	
	QGraphicsPixmapItem *pItem;
	QGraphicsPixmapItem *pItem1;
	

	/// <summary>  
	/// ͼ��Ԫ����ģ��  
	/// </summary>  
	QStandardItemModel *imgMetaModel;  
	Ui::MainWindowClass ui;
	ParasDlg *parasDlg;

	
	// <summary> 
	/// ͼ����������  
	/// </summary>  
	QImage* BrightnessAdd(QImage *origin);

	double CalScaleFactor(double maxLatitude,double minLatitude,double maxLongtitude,double minLongtitude,int widthGraphicsView,int heightGraphicsView);

	bool eventFilter(QObject *o, QEvent *e);
	void InitTree();//��ʼ�������

	
	
	void ShowBand(GDALRasterBand* band );  
		
	
	void getActionName(); //��ȡActionName
	
	void ImgPtChangedScenePt(); //ͼ���ϵĵ�õ���Ļ��������

	void mousePressEvent(QMouseEvent *event);

	void mouseReleaseEvent(QMouseEvent *event);

	void mouseMoveEvent(QMouseEvent *event);

	void ReadImg(const QString filename,int myScenedistX,int myScenedistY);//����ͼ��
	void ReadImgInfo(const QString filename);//����ͼ�������Ϣ
	void  RedrawROI(int i);//�ػ�myScene�е�ROI
	 

	void resizeEvent();
	void ScaleImage(double factor);//ͼ������
	
	void ScenePtChangedImgPt(); //��Ļ��������õ�ͼ���ϵĵ�

	void ShowTree(const QString filename,int nBandCount);



signals:
	void clicked();
	void released();//����ROI���������ſ�
	void timeout();//��ʱ��ÿ��1���ӷ����źţ���ȡmyscene����������ת���ɵĵ�������
	void sliderPressed ();//ˮƽ������������λ�ñ仯

	void valueChanged(int);//��ֱ������λ�ñ仯
	
private slots:
	void openFileSlot();
	
	//�������ò�������Ĳ�
	void setParasSlot();
	
	//������-ͼ�����εĲ�
	void panPicSlot();

	//������-ͼ��Ŵ�Ĳ�
	void MagnifyActionSlot();

	//������-�½�ROI�Ĳ�
	void NewROIActionSlot();		
	
	

	//������-�½�ROI�Ĳ�
	void DeleteROIActionSlot();
	
	//״̬����ʱ���Ĳ�
	void timeUpdate();

	void VerticalScrollBarValueChangedSlot(int);//��ֱ������������λ�ñ仯�Ĳ�

	void HorizontalScrollBarValueChangedSlot(int);//ˮƽ������λ�ñ仯�Ĳ�
	

	void isPressed();
	void isReleased();
	virtual void mousePressEventSlot();

	//virtual void mouseReleaseEventSlot();
};

#endif // MAINWINDOW_H
