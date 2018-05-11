#pragma once
#ifndef RECT_H
#define RECT_H
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QPainterPath> 
#include <QPainter>
#include <QSizeF>
#include <QRectF>


class Rect:public QObject,public QGraphicsRectItem
{
	  Q_OBJECT

	//Q_INTERFACES(QGraphicsItem) //֪ͨҪʵ�ֵ��๹�ɺ��ֽ���ĺ� 
	private:
		
		QColor brushColor;
		int m_width;   
		int m_height;
		int width;   
		int height;
		QPointF startPos;
		QPointF endPos;
		

	
	public:
		
		Rect(int startPointX,int startPointY,int endPointX,int endPointY,QGraphicsRectItem *parent=0); 
	
	//��ͼ����
	//virtual function
	QRectF boundingRect() const;
	QPainterPath shape() const;
	
	//���ƺ���  
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0); 
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	//void setRect(const QRectF (rect));
	
	~Rect();
signals:  

	void itemIsPressed();
	void itemIsReleased();

	
	
	
};
#endif
