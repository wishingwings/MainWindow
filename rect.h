#pragma once
#ifndef RECT_H
#define RECT_H
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
 #include <QGraphicsSceneMouseEvent>


class Rect:public QObject,public QGraphicsItem
{
	Q_OBJECT  
	Q_INTERFACES(QGraphicsItem) //֪ͨҪʵ�ֵ��๹�ɺ��ֽ���ĺ� 
	private:
	
	public:
	
	//��ͼ����
	//virtual function
	QRectF boundingRect() const;
	//QPainterPath shape() const;
	
	//���ƺ���  
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0); 
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	QGraphicsSceneMouseEvent* event;
	Rect(); 
	~Rect();
signals:  

	void itemIsPressed();
	void itemIsReleased();
	
	
};
#endif
