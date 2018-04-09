#include "MyScene.h"

#include <QGraphicsSceneMouseEvent>

#include <QGraphicsRectItem>
#include <QPointF>
#include <QDebug>


MyScene::MyScene(QObject *parent) :
QGraphicsScene(parent)
{
}
void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	movePos= event->scenePos();
	int moveX=movePos.x()-beforePos.x();
	int moveY=movePos.y()-beforePos.y();
	
}
void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug()<<"myScene's mousePressEvent"<<endl;
	beforePos = event->scenePos();
	int x=beforePos.x();
		int y=beforePos.y();
		
	QGraphicsScene::mousePressEvent(event); //FIXME
}
void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug()<<"myScene's releaseEvent"<<endl;
	releasePos = event->scenePos();
	const QRectF *rect=new QRectF (beforePos,QSizeF(movePos.x()-beforePos.x(),movePos.y()-beforePos.y()));
	
	QGraphicsRectItem *item_rect=new QGraphicsRectItem();
	//item_rect->setRect(QRectF (rect));
	item_rect->setRect(QRectF(beforePos,QSizeF(movePos.x()-beforePos.x(),movePos.y()-beforePos.y())));
	this->addItem(item_rect);
	qDebug()<<"Scene added item"<<endl;
	//ui.graphicsView->setScene(pScene);
	QGraphicsScene::mouseReleaseEvent(event);//FIXME
}


MyScene::~MyScene(void)
{
}
