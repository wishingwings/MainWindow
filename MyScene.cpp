#include "MyScene.h"
#include "mainwindow.h"

#include <QGraphicsSceneMouseEvent>

#include <QGraphicsRectItem>

#include <QDebug>
#include <QString>
#include <QPainter>
#include <QObject>

//传出参数
double MyScene::dGeoPosX;
double MyScene::dGeoPosY;
int MyScene::distX;
int MyScene::distY;
float MyScene::ROIScaleFactor;

//接收参数
static QString fileName; //读入图像文件的文件名 mainwindow.h的静态变量
static QString operationName;//最后一个标题栏操作对象的名字 mainwindow.h的静态变量
static void ReadImg(const QString filename);//读出图像 mainwindow执行的
static float scaleFactor; // 此时的图像缩放比例 mainwindow.h的静态变量
static int vScrollBarNow; //此时MainWindow QGraphicsView垂直滚动条滚动距离
static int hScrollBarNow; //此时MainWindow QGraphicsView水平滚动条滚动距离
//static QGraphicsItemGroup *itemGroup; 

MyScene::MyScene(QObject *parent):
QGraphicsScene(parent)
{
	LUPoint=new QPointF();
	timerScene=new QTimer(this);
	timerScene->start(1000); // 每次发射timeout信号时间间隔为1秒
	
	//定义绘制ROI画笔的样式
	//pen.setWidth(2);
	//pen.setColor(QColor(0, 160, 230));
	

	ROILists=new QList<QGraphicsRectItem *> ();
	tmpROILists=new QList<QGraphicsRectItem *> ();
	itemGroup=new QGraphicsItemGroup();
	ROIScaleFactor=1.0000000;
	
	scaleFactorNow=sqrt(MainWindow::scaleFactor); //获得现在长或宽的缩放比例

	QObject::connect(timerScene,SIGNAL(timeout()),this,SLOT(timeUpdate()));
	
}
void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QString filename=MainWindow::fileName;//读取从MainWindow读到图像的路径和名字
	QString operationName=MainWindow::operationName;//读取从MainWindow 获得标题栏上发出操作的最后一个对象的名字
	 double dscaleFactor=MainWindow::scaleFactor;//MainWindow计算出地理坐标和屏幕坐标的放大比例

	movePos = event->scenePos();
	int movePosX=movePos.x();
	int movePosY=movePos.y();

	qDebug()<<"MY SCENE mouseMoveEvent"<<endl;

	QGraphicsScene::mouseMoveEvent(event); //FIXME	
}


void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug()<<"myScene's mousePressEvent"<<endl;
	beforePos = event->scenePos();
	
		
	QGraphicsScene::mousePressEvent(event); //FIXME
}
void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

	QString filename=MainWindow::fileName;//读取从MainWindow读到图像的路径和名字
	qDebug()<<"MainWindow operation name"<<MainWindow::operationName;
	QString operationName=MainWindow::operationName;//读取从MainWindow 获得标题栏上发出操作的最后一个对象的名字
	qDebug()<<"myScene's releaseEvent"<<endl;
	releasePos = event->scenePos();

	//屏幕上绘制的ROI
	Rect *rect=new Rect(beforePos.x(),beforePos.y(),releasePos.x()-beforePos.x(),releasePos.y()-beforePos.y());

	if (filename!="")//如果
	{

		if(operationName=="NewROIAction")
		{
		/*const QRectF *rect=new QRectF (beforePos,QSizeF(movePos.x()-beforePos.x(),movePos.y()-beforePos.y()));
	
		QGraphicsRectItem *item_rect=new QGraphicsRectItem();
		//item_rect->setRect(QRectF (rect));
		item_rect->setRect(QRectF(beforePos,QSizeF(movePos.x()-beforePos.x(),movePos.y()-beforePos.y())));
		this->addItem(item_rect);
		
		qDebug()<<"Scene added item"<<endl;
		
		ROILists->append(item_rect);
		
		qDebug()<<"ROIList length"<<ROILists->count();
		qDebug()<<"ROIList added item"<<endl;*/

		//start from 20180410 考虑到需要删除ROI的操作
		
		int xEndPos=releasePos.x(); //在Rect类中绘制矩形 右下点坐标X值 在Rect类中再组合成矩形起始点的X坐标
	    int  yEndPos=releasePos.y();//在Rect类中绘制矩形  右下点坐标Y值 在Rect类中再组合成矩形起始点的Y坐标
		int xBeforePos=beforePos.x(); //在Rect类中绘制矩形起始点的X坐标
		int yBeforePos=beforePos.y(); //在Rect类中绘制矩形起始点的Y坐标
		
		
		//Rect *rect1=new Rect(beforePos.x(),beforePos.y(),releasePos.x(),releasePos.y());
		//rect1->setToolTip("ROI 1");

		_id="ROI_1";//rect的名字
		
		
		ROIScaleFactorList.append(MainWindow::scaleFactor);//记录绘制时候ROI的缩放倍数
		BackgroundXMoveList.append(MainWindow::hScrollBarNow);//记录绘制ROI时候，场景移动的X距离
		BackgroundYMoveList.append(MainWindow::vScrollBarNow);//记录绘制ROI时候，场景移动的Y距离
				
		this->addItem(rect);
		
		tmpROILists->append(rect);
	
		qDebug()<<"primative RECT TP"<<rect->boundingRect().topLeft();
		 		
		//ROIList存储ROI的原始状态 ROI的左上角点屏幕坐标转为图像上的坐标；根据缩放比例，ROI的长宽
		QPointF ROILUPt=ScreenPtToImgPt(beforePos);//记录ROI左上角点屏幕坐标转化为图像坐标
		int xPrimary=ROILUPt.x();
		int yPrimart=ROILUPt.y();
		
		if (scaleFactorNow>=1)
		{
			Rect *rectPrimary=new Rect(ROILUPt.x(),ROILUPt.y(),(releasePos.x()-beforePos.x())/scaleFactorNow,(releasePos.y()-beforePos.y())/scaleFactorNow);
			ROILists->append(rectPrimary);
			qDebug()<<"primative RECT TP after trans"<<rectPrimary->boundingRect().topLeft();
		}
		else
		{
			Rect *rectPrimary=new Rect(ROILUPt.x(),ROILUPt.y(),(releasePos.x()-beforePos.x())*scaleFactorNow,(releasePos.y()-beforePos.y())*scaleFactorNow);
			ROILists->append(rectPrimary);
		}
				
		//rect->setZValue(2.0000000000); //设置ZValue的值，使得选择的ROI矩形显示在最上层
		qDebug()<<"ROIList length"<<ROILists->count();
		//this->removeItem(rect);
		qDebug()<<" Scene item length"<<this->items().count();

		}
			
		if(operationName=="PanAction")
		{
			if (ROILists->count()>0)
			{
				for (int k=0;k<ROILists->count();k++)
				{
					
					RedrawROI(k);
					this->removeItem(rect);
					this->removeItemAt(this->items().count()-2);

				}

				qDebug()<<"myScene items count"<<this->items().count();
			}
		
			
		}

		if(operationName=="MagnifyAction")
		{

			if (ROILists->count()>0)
			{
				for (int k=0;k<ROILists->count();k++)
				{
					RedrawROI(k);
					this->removeItem(rect);
					this->removeItemAt(this->items().count()-2);
				}

				qDebug()<<"myScene items count"<<this->items().count();
			}
					
		}
			
	}
	QGraphicsScene::mouseReleaseEvent(event);//FIXME
}


//<summary> 
//RedrawROI()
// 功能：重新绘制ROI 
///描述：如果主窗口有缩放操作，ROI对应的重绘
///</summary>  
///<param name="i">标识ROIList中ROI的序号</param>  
void MyScene::RedrawROI(int i)
{
	qDebug()<<"ROIList count"<<ROILists->count();
	QGraphicsRectItem *rectItemRedraw=new QGraphicsRectItem();

	rectItemRedraw=ROILists->at(i);//重新绘制
	//this->removeItem(ROILists->at(i)); //需要把之前MyScene.app绘制的ROI区域删除
	
	
	qDebug()<<"Myscene count"<<this->items().count();
	qDebug()<<"ROIList count"<<ROILists->count();
	float temp_ROIScaleFactor=ROIScaleFactor;//myScene ROI的比例大小

	qDebug()<<"rectItemRedraw upleft"<<rectItemRedraw->sceneBoundingRect().topLeft();
	QPointF pt=rectItemRedraw->sceneBoundingRect().topLeft();//画在Scene中的ROI左上角点坐标
	
	QPointF ROIStartPt=beforePos;//ROI画在屏幕上的点
	XMoveNow=MainWindow::hScrollBarNow; //获得现在ScrollBar移动的x距离
	YMoveNow=MainWindow::vScrollBarNow; //获得现在ScrollBar移动的Y距离


	XMoveBefore=BackgroundXMoveList.at(i);
	YMoveBefore=BackgroundYMoveList.at(i);
	float scaleFactorBefore=ROIScaleFactorList.at(i);
		
	QPointF newPt=ImgPtToScreenPt(pt);
	
    int width=newPt.x();
	int height=newPt.y()+(YMoveNow-YMoveBefore);
	
	float temp_ROIinMySceneHeight=rectItemRedraw->sceneBoundingRect().height();  //MyScene上绘制的ROI区域的高
	qDebug()<<"myscen ROI Height"<<rectItemRedraw->sceneBoundingRect().height();

	//ROI区域根据目前MainWindow 图像缩放系数转换成在MainWindow上显示的高
	float ROIMySceneHeight=temp_ROIinMySceneHeight*scaleFactorNow;
	qDebug()<<"in mainwindow ROI width"<<ROIMySceneHeight;

	float temp_ROIinMySceneWidth=	rectItemRedraw->sceneBoundingRect().width();//MyScene上绘制的ROI区域的宽
	qDebug()<<"myscen ROI width"<<rectItemRedraw->sceneBoundingRect().width();

	//ROI区域根据目前MainWindow 图像缩放系数转换成在MainWindow上显示的宽
	float ROIMySceneWidth=temp_ROIinMySceneWidth*scaleFactorNow;
	qDebug()<<"in mainwindow ROI width"<<ROIMySceneWidth;

	
	//根据左上角点信息，缩放后的高和宽 重新绘制矩形
	QGraphicsRectItem *NewRectItem=new QGraphicsRectItem(width,height,ROIMySceneWidth,ROIMySceneHeight);
	
	qDebug()<<"NEW RECT ITEM' LT PT"<<NewRectItem->sceneBoundingRect().topLeft();
	
	qDebug()<<"scene items count "<<this->items().count();

	for(int i=0;i<tmpROILists->count();i++)
	{
		this->removeItem(tmpROILists->at(i));
	}
	qDebug()<<"scene items count now"<<this->items().count();
	NewRectItem->setPen(pen);
	this->addItem(NewRectItem);
	
	tmpROILists->append(NewRectItem);
	qDebug()<<"scene items count after add item"<<this->items().count();
	
	qDebug()<<"ROIList count"<<ROILists->count();
	

}

//<summary> 
// ScreenPtToImgPt
// 功能：屏幕上的坐标转化为图像坐标 
///描述：
///</summary>  
///<param name="screenPt">屏幕上的点</param>  

QPointF MyScene::ScreenPtToImgPt(QPointF screenPt)
{
	QPointF *imgPt=new QPointF();
	//当前QGraphicsView左上角点图像的坐标x坐标，y坐标
	int xLUPt=MainWindow::hScrollBarNow;
	int yLUPt=MainWindow::vScrollBarNow;
	
	//屏幕上选中点的X,Y坐标
	int xScreenPt=screenPt.x();
 	int yScreenPt=screenPt.y();
	//scaleFactor是图像缩放的倍数

	float tmp_scaleFactor=sqrt(MainWindow::scaleFactor); //长宽的放大倍数是放大倍数开方运算
	
	float ximgPt=float(xScreenPt/tmp_scaleFactor+xLUPt) ;
	float yimgPt=float(yScreenPt/tmp_scaleFactor+yLUPt);
  

	//qreal ximgPt=qreal(xScreenPt/tmp_scaleFactor+xLUPt) ;
	//qreal yimgPt=qreal(yScreenPt/tmp_scaleFactor+yLUPt);

    imgPt->setX(ximgPt);
	imgPt->setY(yimgPt);

	return *imgPt;

}


//<summary> 
// ImgPtToScreenPt
// 功能：图像坐标转化为屏幕上的坐标
///描述：
///</summary>  
///<param name="i">标识ROIList中ROI的序号</param>  

QPointF MyScene::ImgPtToScreenPt(QPointF ImgPt)
{
	QPointF *screenPt=new QPointF();
	//现在QGraphicsView Scrollbar 移动x距离，y距离
	int xLUPt=MainWindow::hScrollBarNow;
	int yLUPt=MainWindow::vScrollBarNow;
	//之前QGraphicsView Scrollbar 移动x距离，y距离
	int XMoveBefore=BackgroundXMoveList.at(0);
	int YMoveBefore=BackgroundYMoveList.at(0);

	//图像上X,Y坐标
	float xImgPt=ImgPt.x();
	float yImgPt=ImgPt.y();
	//scaleFactor是图像缩放的倍数

	float tmp_scaleFactor=sqrt(MainWindow::scaleFactor);

	
	float xScreenPt=float((xImgPt-xLUPt)*tmp_scaleFactor);
	float yScreenPt=float((yImgPt-yLUPt)*tmp_scaleFactor);

	
	
	screenPt->setX(xScreenPt);
	screenPt->setY(yScreenPt);

	return *screenPt;

}
int MyScene::mouseMoveXDistance()
{
	//计算出鼠标按下位置坐标的X值
	int beforePosX=beforePos.x();
	
	//计算出鼠标移动位置坐标的X值
	int movePosX=releasePos.x();
	
	//计算出鼠标水平移动的差值

	distX=qAbs(movePosX)-qAbs(beforePosX);

	return distX;
		
}

int MyScene::mouseMoveYDistance()
{
	//计算出鼠标按下位置坐标的Y值
	int beforePosY=beforePos.y();

	//计算出鼠标移动位置坐标的Y值
	int movePosY=releasePos.y();

	//计算出鼠标垂直移动的差值
    distY=qAbs(movePosY)-qAbs(beforePosY);
	
	return distY;

}
//计算平移操作的图像左上点
void MyScene::AfterPanActionLUPoint()
{
	//新建一个点记录平移后图像的左上点
	//newLUPoint->setX(LUPoint->x()+distX);
	newLUPoint=new QPointF();
	
	if (LUPoint==NULL)
	{
		LUPoint=new QPointF();

	}
	
	if(distX<0) //如果平移距离的X方向为向左 值为负
	{
		if(LUPoint->x()==0)
		{
			newLUPoint->setX(0);
		}
		//比较平移的X距离和图像原点X坐标距离的绝对值哪个大
		if(qAbs(distX)>qAbs(LUPoint->x()))
		{
			newLUPoint->setY(qAbs(distX)-qAbs(LUPoint->x()));
		}
		else
		{
			newLUPoint->setX(LUPoint->x());
		}
	}
	else//如果平移距离的X方向为向下 值为正
	{
		newLUPoint->setX(LUPoint->x()+distX);
	}
		

	if(distY<0) //如果平移距离的Y方向为向上 值为负
	{
		if(LUPoint->y()==0)
		{
			newLUPoint->setY(0);
		}
		//比较平移的Y距离和图像原点Y坐标距离的绝对值哪个大
		if(LUPoint->y()!=0||(qAbs(distY)>qAbs(LUPoint->y())))
		{
			newLUPoint->setY(qAbs(distY)-qAbs(LUPoint->y()));
		}
		else
		{
			newLUPoint->setY(LUPoint->y());
		}
	}
	else //如果平移距离的X方向为向下 值为正
	{
		newLUPoint->setX(LUPoint->y()+distY);
	}

		LUPoint=newLUPoint;
	
	
}
void MyScene::timeUpdate()
{



}

void MyScene::removeItemAt(int i)
{
	
	//this->items().;
	
}
MyScene::~MyScene(void)
{
}
