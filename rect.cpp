#include "rect.h"
#include <QGraphicsItem>
#include <QRectF>



Rect::Rect()
{
	
}

Rect::~Rect()
{
}

void Rect::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	
	qDebug()<<"RectIsPressed"<<endl;
	 // setRect(QRectF(event->scenePos(), QSizeF(0, 0))); 
	emit(itemIsPressed());
	QGraphicsItem::mousePressEvent(event);  
	
}
void Rect::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug()<<"ItemMouseMove"<<endl;
	
	QPointF point = event->pos();
	//QRectF r(rect().topLeft(),QSizeF(event->scenePos().x()-rect().topLeft().x(),event->scenePos().y()-rect().topLeft().y()));
	
	//setRect(r);

	//setRect(QRectF(event->scenePos(),QSizeF(100,100)));
}
void Rect::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	
	qDebug()<<"ItemMouseReleaseEvent"<<endl;
	emit(itemIsReleased());
	QGraphicsItem::mouseReleaseEvent(event);
}



QRectF Rect::boundingRect() const
{
	return QRectF(0,0,100,100);
}

 void Rect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) 
 {
 
 }


	 