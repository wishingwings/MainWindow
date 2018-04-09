#pragma once

#include <QtGui>
class Shape
{
public:
	
	virtual void startDraw(QGraphicsSceneMouseEvent * event);
	virtual void drawing(QGraphicsSceneMouseEvent * event);
	Shape(void);
	~Shape(void);
};
#endif//SHAPE_H

