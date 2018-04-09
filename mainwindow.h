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
	///����ʼx����
	///</summary>
	int x0;

	///</summary>
	///����ʼy����
	///</summary>
	int y0;

	
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
	///�¼�����������
	///</summary>
	QObject *obj;

	///<summary>
	///����� ��¼�����Graphicsviewѡ��ROI����ʼ������ĵ�
	///</summary>
	QPoint  currentPos;
	QPoint  endPos;


	///<summary>
	///���ڼ�¼Toolbar�ϵ����Action��ActionName :��¼��Ҫ������graphicview�Ͻ��в�����Action����Ҫ��QStringList
	///����Clcked()�¼��жϣ����Action���ĸ����󷢳���
    ///���磺ͼ��Ŵ�ͼ����С��ͼ��1��1��ʾ
	///</summary>
	QStringList *strList;
	
	///<summary>
	///Matrix
	///����graphicsview�ķŴ����С��Matrix
	///</summary>

	QMatrix matrix; 


	QPainter *paint;
	///<summary>
	///������
	///����graphicsview�Ĺ��
	///</summary>
	QCursor cursor;

	QString fileName;//����ͼ���ļ����ļ���

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
	/// ͼ��Ԫ����ģ��  
	/// </summary>  
	QStandardItemModel *imgMetaModel;  
	
	void InitTree();//��ʼ�������

	//void ShowImg(QList <GDALRasterBand*> *imgBand);   
	void ShowTree(const QString filename,int nBandCount);

	void ReadImg(const QString filename);//����ͼ��

	void ReadImgInfo(const QString filename);//����ͼ�������Ϣ

	void ShowBand(GDALRasterBand* band );  
		
	void mousePressEvent(QMouseEvent *event);

	void mouseReleaseEvent(QMouseEvent *event);

	//void paintEvent(QPaintEvent *event);
	
	void getActionName(); //��ȡActionName

	void resizeEvent();
signals:
	void clicked();
	void released();//����ROI���������ſ�
	//void RectMouseIsPressed();
	

private slots:
	void openFileSlot();
	
	//������-ͼ�����εĲ�
	void panPicSlot();

	//������-ͼ��Ŵ�Ĳ�
	void MagnifyActionSlot();

	//������-�½�ROI�Ĳ�
	void NewROIActionSlot();

	void isPressed();
	void isReleased();
	virtual void mousePressEventSlot();

	//virtual void mouseReleaseEventSlot();
};

#endif // MAINWINDOW_H
