//***********************************************************************  
 //<copyright file="ImgOperation.h" company="">  
 //     Copyright (c) . All rights reserved.  
 //</copyright>  
 //<summary>图像操作类，负责图像的平移，放大，缩小等功能。</summary>  
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
	QCursor cursor;  //光标对象


	};

