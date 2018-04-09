#pragma once
#include <QGraphicsScene>
class MyScene:public QGraphicsScene
{
Q_OBJECT
public:
	explicit MyScene(QObject *parent = 0);
	
	
	~MyScene(void);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
	void isMoving(QPointF &pos);

	public slots:

private:
	QPointF  beforePos;
	QPointF  movePos;
	QPointF  releasePos;
};


