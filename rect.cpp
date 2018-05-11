#include "rect.h"
#include "MyScene.h"
#include <QGraphicsItem>
#include <QRectF>
#include <QPointF>
#include <QObject>



Rect::Rect(int startPointX,int startPointY,int width,int height,QGraphicsRectItem *parent)
	

{
    startPos=QPointF(startPointX,startPointY);
	 m_width=width;
	 m_height=height;
	
	//setFlag(QGraphicsRectItem::ItemIsFocusable);  
	setFlag(QGraphicsRectItem::ItemIsSelectable);  

	setFlag(QGraphicsRectItem::ItemIsMovable);  
}

Rect::~Rect()
{

}

/*void Rect::setRect(const QRectF rect)
{
	
}*/
void Rect::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	
	qDebug()<<"ItemIsPressed"<<endl;
	setFocus();
	setSelected(true);

	QGraphicsItem::mousePressEvent(event);  
	
}
void Rect::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug()<<"ItemMouseMove"<<endl;
	
	QPointF point = event->pos();
	
}
void Rect::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	
	qDebug()<<"ItemMouseReleaseEvent"<<endl;
	
	
}

/*void Rect::deletle()
{

	qDebug()<<"ItemMouseReleaseEvent"<<endl;


}*/

QRectF Rect::boundingRect() const
{
	//return QRectF(-m_width/2-1,-m_height/2-1,m_width+2,m_height+2);//每个item都有自己的一个坐标系，  
	//这个设置相当于把item相对于自身的坐标系的原点（0,0）放到自己的正中央。
	//return QRectF(100,100,500,500);
	qreal penWidth = 1;
	return QRectF(startPos,QSizeF(m_width,m_height));
}

 void Rect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) 
 {
	 //painter->drawRect(QRectF(-m_width/2,-m_height/2,m_width,m_height));
	 QPen pen=painter->pen();
	 pen.setWidth(2);
	 pen.setColor(Qt::red); // 也可以这样设置绘制ROI边框颜色pen.setColor(QColor(0, 160, 230));
	 painter->setPen(pen);
	 painter->drawRect(QRectF (startPos,QSizeF(m_width,m_height)));
 }

 QPainterPath Rect::shape()const{   
	 
	 QPainterPath path;   
	 //path.addRect(QRectF(-m_width/2,-m_height/2,m_width,m_height));  
	  path.addRect(QRectF (startPos,QSizeF(m_width,m_height))); 
	 return path; 
 } 
	 