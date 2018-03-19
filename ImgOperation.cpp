
#include "ImgOperation.h"

#include "mainwindow.h"

ImgOperation::ImgOperation(QWidget *parent):QGraphicsView(parent)
{
	

}


ImgOperation::~ImgOperation(void)
{
}

//增加按下鼠标事件处理函数
void ImgOperation::mousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	
	{
			QCursor cursor;
			cursor.setShape(Qt::ClosedHandCursor);
			QApplication::setOverrideCursor(cursor);

			this->setDragMode(QGraphicsView::ScrollHandDrag );  
			this->setInteractive( false );  
			lastEventCursorPos = event->pos();  


	}


}




