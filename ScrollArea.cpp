#include "ScrollArea.h"
#include <QMouseEvent>
#include<QDebug>
#include <QScrollBar>



ScrollArea::ScrollArea(QWidget *parent):QScrollArea(parent)
{
	installEventFilter(this);  
}

ScrollArea::~ScrollArea()
{
}

bool ScrollArea::eventFilter(QObject *obj,QEvent *evt)  
{
	if (evt->type() == QEvent::MouseMove) 
	{
		qDebug()<<"ScroolArea mousemove"<<endl;

		return true;
	
	}


}