
#include "ImgOperation.h"

#include "mainwindow.h"

ImgOperation::ImgOperation(QWidget *parent):QGraphicsView(parent)
{
	

}


ImgOperation::~ImgOperation(void)
{
}

//���Ӱ�������¼�������
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




