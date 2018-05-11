#pragma once
#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QObject>
#include <QScrollArea>
#include <QPoint>

class ScrollArea:public QScrollArea
{
	Q_OBJECT

public:
	ScrollArea(QWidget* parent=NULL);
	~ScrollArea();

private:

	
	bool eventFilter(QObject *obj,QEvent *evt);  

};

#endif// SCROLLAREA_H