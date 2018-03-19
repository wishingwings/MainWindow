//***********************************************************************  
 //<copyright file="ImgOperation.h" company="">  
 //     Copyright (c) . All rights reserved.  
 //</copyright>  
 //<summary>ͼ������࣬����ͼ���ƽ�ƣ��Ŵ���С�ȹ��ܡ�</summary>  
 //***********************************************************************  

#pragma once
#ifdef IMGOPERATION.H
#define IMGOPERATION.H
#endif
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QCursor>
#include <QDebug>

class ImgOperation:public QGraphicsView
{
	Q_OBJECT;
public:
	ImgOperation(QWidget *parent=0);
	~ImgOperation();

protected:
	void mousePressEvent(QMouseEvent *event);
private:
	QCursor cursor;  //������


	};

