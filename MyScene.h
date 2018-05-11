#pragma once
#include "rect.h"
#include <gdal_priv.h>
#include <gdal.h>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QPointF>
#include <QRect>
#include <QString>
#include <QScrollArea>
#include <QTimer>

class MyScene:public QGraphicsScene
{
	Q_OBJECT
public:
	//QList *ROIListInfo;
	QGraphicsItemGroup* itemGroup; //定义ITEM组 
	QList<QGraphicsRectItem*>* ROILists;  //记录初始绘制ROI的位置和大小
	QList<QGraphicsRectItem*>* tmpROILists; //记录整个过程中绘制ROI位置和大小
	static double dGeoPosX;
	static double dGeoPosY;
	QString _id;

	QPen pen; //定义绘制ROI的画笔

    static  float ROIScaleFactor;// 记录绘制ROI的缩放比例  MainWindow可以调用   
	//计算鼠标移动距离的X和Y值  //myScene.cpp可访问
	static int distX;
	static int distY;
	
	
	
	explicit MyScene(QObject *parent = 0);
	
	
	~MyScene(void);

	QPointF  beforePos;
	QPointF  movePos;
	QPointF  releasePos;

	void AfterPanActionLUPoint();
	void removeItemAt(int i);
	void RedrawROI(int i);//重新绘制ROI

	QPointF  ScreenPtToImgPt(QPointF screenPt);
	QPointF  ImgPtToScreenPt(QPointF screenPt);


protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
	void isMoving(QPointF &pos);
	void timeout();//定时器每隔1秒钟发送信号，获取myscene类的鼠标坐标转化成的地理坐标
	

private slots:
	void timeUpdate();//状态栏定时器的槽
	
   
public slots:

private:
	
	float scaleFactorNow; //记录现在场景长或宽的缩放比例（场景缩放比例开方） 
	QTimer *timerScene;
	
	QPointF *LUPoint;//图像的左上角点
	QPointF *newLUPoint; //经过平移后的图像的左上角点

	int mouseMoveXDistance();
	int mouseMoveYDistance();

	QList <float>ROIScaleFactorList; //记录每个ROI初始绘制时候，场景的放大倍数
	QList <int>BackgroundXMoveList; //记录每个ROI初始绘制背景图像移动X距离
	QList <int>BackgroundYMoveList; //记录每个ROI初始绘制背景图像移动Y距离
		
	int XMoveNow; //记录现在ScrollArea 水平移动距离
	int YMoveNow; //记录现在ScrollArea 垂直移动距离
	int XMoveBefore; //记录绘制ROI ScrollArea 水平移动距离
	int YMoveBefore; //记录绘制ROI ScrollArea 垂直移动距离
	
		
};


