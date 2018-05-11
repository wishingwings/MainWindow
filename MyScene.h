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
	QGraphicsItemGroup* itemGroup; //����ITEM�� 
	QList<QGraphicsRectItem*>* ROILists;  //��¼��ʼ����ROI��λ�úʹ�С
	QList<QGraphicsRectItem*>* tmpROILists; //��¼���������л���ROIλ�úʹ�С
	static double dGeoPosX;
	static double dGeoPosY;
	QString _id;

	QPen pen; //�������ROI�Ļ���

    static  float ROIScaleFactor;// ��¼����ROI�����ű���  MainWindow���Ե���   
	//��������ƶ������X��Yֵ  //myScene.cpp�ɷ���
	static int distX;
	static int distY;
	
	
	
	explicit MyScene(QObject *parent = 0);
	
	
	~MyScene(void);

	QPointF  beforePos;
	QPointF  movePos;
	QPointF  releasePos;

	void AfterPanActionLUPoint();
	void removeItemAt(int i);
	void RedrawROI(int i);//���»���ROI

	QPointF  ScreenPtToImgPt(QPointF screenPt);
	QPointF  ImgPtToScreenPt(QPointF screenPt);


protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
	void isMoving(QPointF &pos);
	void timeout();//��ʱ��ÿ��1���ӷ����źţ���ȡmyscene����������ת���ɵĵ�������
	

private slots:
	void timeUpdate();//״̬����ʱ���Ĳ�
	
   
public slots:

private:
	
	float scaleFactorNow; //��¼���ڳ������������ű������������ű��������� 
	QTimer *timerScene;
	
	QPointF *LUPoint;//ͼ������Ͻǵ�
	QPointF *newLUPoint; //����ƽ�ƺ��ͼ������Ͻǵ�

	int mouseMoveXDistance();
	int mouseMoveYDistance();

	QList <float>ROIScaleFactorList; //��¼ÿ��ROI��ʼ����ʱ�򣬳����ķŴ���
	QList <int>BackgroundXMoveList; //��¼ÿ��ROI��ʼ���Ʊ���ͼ���ƶ�X����
	QList <int>BackgroundYMoveList; //��¼ÿ��ROI��ʼ���Ʊ���ͼ���ƶ�Y����
		
	int XMoveNow; //��¼����ScrollArea ˮƽ�ƶ�����
	int YMoveNow; //��¼����ScrollArea ��ֱ�ƶ�����
	int XMoveBefore; //��¼����ROI ScrollArea ˮƽ�ƶ�����
	int YMoveBefore; //��¼����ROI ScrollArea ��ֱ�ƶ�����
	
		
};


