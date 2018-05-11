#include "MyScene.h"
#include "mainwindow.h"

#include <QGraphicsSceneMouseEvent>

#include <QGraphicsRectItem>

#include <QDebug>
#include <QString>
#include <QPainter>
#include <QObject>

//��������
double MyScene::dGeoPosX;
double MyScene::dGeoPosY;
int MyScene::distX;
int MyScene::distY;
float MyScene::ROIScaleFactor;

//���ղ���
static QString fileName; //����ͼ���ļ����ļ��� mainwindow.h�ľ�̬����
static QString operationName;//���һ��������������������� mainwindow.h�ľ�̬����
static void ReadImg(const QString filename);//����ͼ�� mainwindowִ�е�
static float scaleFactor; // ��ʱ��ͼ�����ű��� mainwindow.h�ľ�̬����
static int vScrollBarNow; //��ʱMainWindow QGraphicsView��ֱ��������������
static int hScrollBarNow; //��ʱMainWindow QGraphicsViewˮƽ��������������
//static QGraphicsItemGroup *itemGroup; 

MyScene::MyScene(QObject *parent):
QGraphicsScene(parent)
{
	LUPoint=new QPointF();
	timerScene=new QTimer(this);
	timerScene->start(1000); // ÿ�η���timeout�ź�ʱ����Ϊ1��
	
	//�������ROI���ʵ���ʽ
	//pen.setWidth(2);
	//pen.setColor(QColor(0, 160, 230));
	

	ROILists=new QList<QGraphicsRectItem *> ();
	tmpROILists=new QList<QGraphicsRectItem *> ();
	itemGroup=new QGraphicsItemGroup();
	ROIScaleFactor=1.0000000;
	
	scaleFactorNow=sqrt(MainWindow::scaleFactor); //������ڳ��������ű���

	QObject::connect(timerScene,SIGNAL(timeout()),this,SLOT(timeUpdate()));
	
}
void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QString filename=MainWindow::fileName;//��ȡ��MainWindow����ͼ���·��������
	QString operationName=MainWindow::operationName;//��ȡ��MainWindow ��ñ������Ϸ������������һ�����������
	 double dscaleFactor=MainWindow::scaleFactor;//MainWindow����������������Ļ����ķŴ����

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

	QString filename=MainWindow::fileName;//��ȡ��MainWindow����ͼ���·��������
	qDebug()<<"MainWindow operation name"<<MainWindow::operationName;
	QString operationName=MainWindow::operationName;//��ȡ��MainWindow ��ñ������Ϸ������������һ�����������
	qDebug()<<"myScene's releaseEvent"<<endl;
	releasePos = event->scenePos();

	//��Ļ�ϻ��Ƶ�ROI
	Rect *rect=new Rect(beforePos.x(),beforePos.y(),releasePos.x()-beforePos.x(),releasePos.y()-beforePos.y());

	if (filename!="")//���
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

		//start from 20180410 ���ǵ���Ҫɾ��ROI�Ĳ���
		
		int xEndPos=releasePos.x(); //��Rect���л��ƾ��� ���µ�����Xֵ ��Rect��������ϳɾ�����ʼ���X����
	    int  yEndPos=releasePos.y();//��Rect���л��ƾ���  ���µ�����Yֵ ��Rect��������ϳɾ�����ʼ���Y����
		int xBeforePos=beforePos.x(); //��Rect���л��ƾ�����ʼ���X����
		int yBeforePos=beforePos.y(); //��Rect���л��ƾ�����ʼ���Y����
		
		
		//Rect *rect1=new Rect(beforePos.x(),beforePos.y(),releasePos.x(),releasePos.y());
		//rect1->setToolTip("ROI 1");

		_id="ROI_1";//rect������
		
		
		ROIScaleFactorList.append(MainWindow::scaleFactor);//��¼����ʱ��ROI�����ű���
		BackgroundXMoveList.append(MainWindow::hScrollBarNow);//��¼����ROIʱ�򣬳����ƶ���X����
		BackgroundYMoveList.append(MainWindow::vScrollBarNow);//��¼����ROIʱ�򣬳����ƶ���Y����
				
		this->addItem(rect);
		
		tmpROILists->append(rect);
	
		qDebug()<<"primative RECT TP"<<rect->boundingRect().topLeft();
		 		
		//ROIList�洢ROI��ԭʼ״̬ ROI�����Ͻǵ���Ļ����תΪͼ���ϵ����ꣻ�������ű�����ROI�ĳ���
		QPointF ROILUPt=ScreenPtToImgPt(beforePos);//��¼ROI���Ͻǵ���Ļ����ת��Ϊͼ������
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
				
		//rect->setZValue(2.0000000000); //����ZValue��ֵ��ʹ��ѡ���ROI������ʾ�����ϲ�
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
// ���ܣ����»���ROI 
///��������������������Ų�����ROI��Ӧ���ػ�
///</summary>  
///<param name="i">��ʶROIList��ROI�����</param>  
void MyScene::RedrawROI(int i)
{
	qDebug()<<"ROIList count"<<ROILists->count();
	QGraphicsRectItem *rectItemRedraw=new QGraphicsRectItem();

	rectItemRedraw=ROILists->at(i);//���»���
	//this->removeItem(ROILists->at(i)); //��Ҫ��֮ǰMyScene.app���Ƶ�ROI����ɾ��
	
	
	qDebug()<<"Myscene count"<<this->items().count();
	qDebug()<<"ROIList count"<<ROILists->count();
	float temp_ROIScaleFactor=ROIScaleFactor;//myScene ROI�ı�����С

	qDebug()<<"rectItemRedraw upleft"<<rectItemRedraw->sceneBoundingRect().topLeft();
	QPointF pt=rectItemRedraw->sceneBoundingRect().topLeft();//����Scene�е�ROI���Ͻǵ�����
	
	QPointF ROIStartPt=beforePos;//ROI������Ļ�ϵĵ�
	XMoveNow=MainWindow::hScrollBarNow; //�������ScrollBar�ƶ���x����
	YMoveNow=MainWindow::vScrollBarNow; //�������ScrollBar�ƶ���Y����


	XMoveBefore=BackgroundXMoveList.at(i);
	YMoveBefore=BackgroundYMoveList.at(i);
	float scaleFactorBefore=ROIScaleFactorList.at(i);
		
	QPointF newPt=ImgPtToScreenPt(pt);
	
    int width=newPt.x();
	int height=newPt.y()+(YMoveNow-YMoveBefore);
	
	float temp_ROIinMySceneHeight=rectItemRedraw->sceneBoundingRect().height();  //MyScene�ϻ��Ƶ�ROI����ĸ�
	qDebug()<<"myscen ROI Height"<<rectItemRedraw->sceneBoundingRect().height();

	//ROI�������ĿǰMainWindow ͼ������ϵ��ת������MainWindow����ʾ�ĸ�
	float ROIMySceneHeight=temp_ROIinMySceneHeight*scaleFactorNow;
	qDebug()<<"in mainwindow ROI width"<<ROIMySceneHeight;

	float temp_ROIinMySceneWidth=	rectItemRedraw->sceneBoundingRect().width();//MyScene�ϻ��Ƶ�ROI����Ŀ�
	qDebug()<<"myscen ROI width"<<rectItemRedraw->sceneBoundingRect().width();

	//ROI�������ĿǰMainWindow ͼ������ϵ��ת������MainWindow����ʾ�Ŀ�
	float ROIMySceneWidth=temp_ROIinMySceneWidth*scaleFactorNow;
	qDebug()<<"in mainwindow ROI width"<<ROIMySceneWidth;

	
	//�������Ͻǵ���Ϣ�����ź�ĸߺͿ� ���»��ƾ���
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
// ���ܣ���Ļ�ϵ�����ת��Ϊͼ������ 
///������
///</summary>  
///<param name="screenPt">��Ļ�ϵĵ�</param>  

QPointF MyScene::ScreenPtToImgPt(QPointF screenPt)
{
	QPointF *imgPt=new QPointF();
	//��ǰQGraphicsView���Ͻǵ�ͼ�������x���꣬y����
	int xLUPt=MainWindow::hScrollBarNow;
	int yLUPt=MainWindow::vScrollBarNow;
	
	//��Ļ��ѡ�е��X,Y����
	int xScreenPt=screenPt.x();
 	int yScreenPt=screenPt.y();
	//scaleFactor��ͼ�����ŵı���

	float tmp_scaleFactor=sqrt(MainWindow::scaleFactor); //����ķŴ����ǷŴ�����������
	
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
// ���ܣ�ͼ������ת��Ϊ��Ļ�ϵ�����
///������
///</summary>  
///<param name="i">��ʶROIList��ROI�����</param>  

QPointF MyScene::ImgPtToScreenPt(QPointF ImgPt)
{
	QPointF *screenPt=new QPointF();
	//����QGraphicsView Scrollbar �ƶ�x���룬y����
	int xLUPt=MainWindow::hScrollBarNow;
	int yLUPt=MainWindow::vScrollBarNow;
	//֮ǰQGraphicsView Scrollbar �ƶ�x���룬y����
	int XMoveBefore=BackgroundXMoveList.at(0);
	int YMoveBefore=BackgroundYMoveList.at(0);

	//ͼ����X,Y����
	float xImgPt=ImgPt.x();
	float yImgPt=ImgPt.y();
	//scaleFactor��ͼ�����ŵı���

	float tmp_scaleFactor=sqrt(MainWindow::scaleFactor);

	
	float xScreenPt=float((xImgPt-xLUPt)*tmp_scaleFactor);
	float yScreenPt=float((yImgPt-yLUPt)*tmp_scaleFactor);

	
	
	screenPt->setX(xScreenPt);
	screenPt->setY(yScreenPt);

	return *screenPt;

}
int MyScene::mouseMoveXDistance()
{
	//�������갴��λ�������Xֵ
	int beforePosX=beforePos.x();
	
	//���������ƶ�λ�������Xֵ
	int movePosX=releasePos.x();
	
	//��������ˮƽ�ƶ��Ĳ�ֵ

	distX=qAbs(movePosX)-qAbs(beforePosX);

	return distX;
		
}

int MyScene::mouseMoveYDistance()
{
	//�������갴��λ�������Yֵ
	int beforePosY=beforePos.y();

	//���������ƶ�λ�������Yֵ
	int movePosY=releasePos.y();

	//�������괹ֱ�ƶ��Ĳ�ֵ
    distY=qAbs(movePosY)-qAbs(beforePosY);
	
	return distY;

}
//����ƽ�Ʋ�����ͼ�����ϵ�
void MyScene::AfterPanActionLUPoint()
{
	//�½�һ�����¼ƽ�ƺ�ͼ������ϵ�
	//newLUPoint->setX(LUPoint->x()+distX);
	newLUPoint=new QPointF();
	
	if (LUPoint==NULL)
	{
		LUPoint=new QPointF();

	}
	
	if(distX<0) //���ƽ�ƾ����X����Ϊ���� ֵΪ��
	{
		if(LUPoint->x()==0)
		{
			newLUPoint->setX(0);
		}
		//�Ƚ�ƽ�Ƶ�X�����ͼ��ԭ��X�������ľ���ֵ�ĸ���
		if(qAbs(distX)>qAbs(LUPoint->x()))
		{
			newLUPoint->setY(qAbs(distX)-qAbs(LUPoint->x()));
		}
		else
		{
			newLUPoint->setX(LUPoint->x());
		}
	}
	else//���ƽ�ƾ����X����Ϊ���� ֵΪ��
	{
		newLUPoint->setX(LUPoint->x()+distX);
	}
		

	if(distY<0) //���ƽ�ƾ����Y����Ϊ���� ֵΪ��
	{
		if(LUPoint->y()==0)
		{
			newLUPoint->setY(0);
		}
		//�Ƚ�ƽ�Ƶ�Y�����ͼ��ԭ��Y�������ľ���ֵ�ĸ���
		if(LUPoint->y()!=0||(qAbs(distY)>qAbs(LUPoint->y())))
		{
			newLUPoint->setY(qAbs(distY)-qAbs(LUPoint->y()));
		}
		else
		{
			newLUPoint->setY(LUPoint->y());
		}
	}
	else //���ƽ�ƾ����X����Ϊ���� ֵΪ��
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
