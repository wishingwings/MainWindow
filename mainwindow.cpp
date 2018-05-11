#include "mainwindow.h"
#include "MyScene.h" //Ϊ������ȫ�ֱ���QList ROILists
#include "rect.h"
#include "gdal.h"
#include "gdal_priv.h"

//���յı���
static double dGeoPosX; //MyScene��������ڵ�ĵ�������X ��ʼ��
static double dGeoPosY; //MyScene��������ڵ�ĵ�������Y ��ʼ��

static int distX;//MyScene����ƶ���Xֵ
static int distY;//MyScene����ƶ���Xֵ

static double ROIscaleFactor;  //MyScene ����ROIʱ��ͼ������ű���

static QList<QGraphicsRectItem*> *ROILists;//��ʼ��*ROILists
//�����ı���

QString MainWindow::fileName=""; //myScene.cpp����Ҫʹ������ͼ�������
QString  MainWindow::operationName="";//myScene.cpp����Ҫʹ�ò��������һ������������
QPoint  MainWindow::pitem1TL;
float MainWindow::scaleFactor;

int MainWindow::vScrollBarNow; //QGrphicsView ��ֱ���������ڵ�λ��  myScene��Ҫȷ��ROI���Ͻǵ��ƶ���λ��

int MainWindow::hScrollBarNow; //QGrphicsView ˮƽ���������ڵ�λ��  myScene��Ҫȷ��ROI���Ͻǵ��ƶ���λ��
QGraphicsItemGroup MainWindow::*itemGroup;
 

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	
	ui.setupUi(this);
	setWindowState(Qt::WindowMaximized);//ʹ�ô������
	//������ʾͼ�������

	vScrollBarNow=ui.graphicsView->verticalScrollBar()->value();
	hScrollBarNow=2;
	iZoomIn=0;
	scaleFactor=1.000000;//Ĭ��ͼ��Ŵ���Ϊ1
	
	vScrollBar=ui.graphicsView->verticalScrollBar();
	hScrollBar=ui.graphicsView->horizontalScrollBar();
	vScrollBar->setTracking(true);
	
	
	timer=new QTimer(this);
	timer->start(1000); // ÿ�η���timeout�ź�ʱ����Ϊ1��
	

	fileName="";
	strList=new QStringList();
	myScene=new MyScene(this);
	
	qDebug()<<myScene->sceneRect()<<endl;
	
	 LabelGeoXY = new QLabel(this);

	
	//Ϊ��ͼ���ó���
	
	ui.graphicsView->setScene(myScene);

	//ui.graphicsView->setMouseTracking(true);
	ui.scrollArea->setMouseTracking(true);
	//ui.centralWidget->setMouseTracking(true);
	//ui.scrollAreaWidgetContents->setMouseTracking(true);
	MainWindow::setMouseTracking(true);
		
	//���������ʾ��������
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	//���������ʾ��������

	QToolBar *pToolBar=addToolBar(tr("&File"));
		
	QObject::connect(ui.openAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
   	
	QObject::connect(ui.PanAction,SIGNAL(triggered()),this,SLOT(panPicSlot()));
		
	QObject::connect(ui.MagnifyAction,SIGNAL(triggered()),this,SLOT(MagnifyActionSlot()));

	QObject::connect(ui.NewROIAction,SIGNAL(triggered()),this,SLOT(NewROIActionSlot()));
	
	QObject::connect(ui.DeleteROIAction,SIGNAL(triggered()),this,SLOT(DeleteROIActionSlot()));

	QObject::connect(this,SIGNAL(clicked()),this,SLOT(mousePressEventSlot()));

	QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));

	QObject::connect(vScrollBar,SIGNAL(valueChanged(int)),this,SLOT(VerticalScrollBarValueChangedSlot(int)));

	QObject::connect(hScrollBar,SIGNAL(valueChanged(int)),this,SLOT(HorizontalScrollBarValueChangedSlot(int)));

	//QObject::connect(myScene,SIGNAL(sendData(int X,int Y)), this, SLOT(ReceiveDataSlot(int X,int Y)));
	//QObject::connect(this,SIGNAL(sliderPressed()),this,SLOT(valueChangedSlot(int)));

	//QObject::connect(rect,SIGNAL(itemIsPressed()),this,SLOT(isPressed()));  //FIXME
	//QObject::connect(rect,SIGNAL(itemIsReleased()),this,SLOT(isReleased()));//FIXME


	//QObject::connect(this,SIGNAL(RectMouseIsPressed()),this,SLOT(mousePressEventSlot()));

	//QObject::connect(this,SIGNAL(released()),this,SLOT(mouseReleaseEvent()));
		
}

MainWindow::~MainWindow()
{
	
}


void MainWindow::resizeEvent() 
{
	ui.graphicsView->size();
	int widthGraphicsView=ui.graphicsView->size().width();
	int heightGraphicsView=ui.graphicsView->size().height();

}

void MainWindow::ReadImgInfo(QString fileName)
{

	if ( fileName == "" || poDataset== NULL )  
	{  
		return;  
	}  
	
	 /*int row = 0; // ������¼����ģ�͵��к� 

	 // ͼ��ĸ�ʽ��Ϣ  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Description" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetDescription() ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Meta Infor") ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetMetadataItem( GDAL_DMD_LONGNAME) ) ) ;  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr("Data Type") ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem(GDALGetDataTypeName( ( poDataset->GetRasterBand( 1)->GetRasterDataType() ) ) ) );  

	 // ͼ��Ĵ�С�Ͳ��θ���  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "X Size" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterXSize() ) ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Y Size" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterYSize() ) ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Band Count" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterCount() ) ) );  

	 // ͼ���ͶӰ��Ϣ  
	 imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Projection" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetProjectionRef() ) );  

	 // ͼ�������ͷֱ�����Ϣ  
	 double adfGeoTransform[6];  
	 QString origin = "";  
	 QString pixelSize = "";  
	 if( poDataset->GetGeoTransform(adfGeoTransform ) == CE_None )  
	 {  
		 origin = QString::number(adfGeoTransform[0] ) + "," + QString::number( adfGeoTransform[3] );  
		 pixelSize = QString::number(adfGeoTransform[1] ) + "," + QString::number( adfGeoTransform[5] );  
	 }  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Origin" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem(origin ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Pixel Size" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem(pixelSize ) );  */


}


//<summary>  
///QGraphicsView ��ֱ�����������仯���������¼�
///</summary>  
///<param name="value">�������仯����ֵ</param>  

void MainWindow::VerticalScrollBarValueChangedSlot(int value)
{
	qDebug()<<"verticalScrollBar value changed"<<endl;
	qDebug()<<"changeint factValue"<<endl;
	
	vScrollBarNow=value;
	//Ŀǰ��ֱ����������ֵ��¼�ڱ�����
	int temp=hScrollBarNow;
	if(fileName.isEmpty())
	{
		return;
	}
	else
	{
		int vBarHeight = ui.graphicsView->verticalScrollBar()->height();//��ֱ�������߶�
		int vBarValueRange=height-vBarHeight;//������������������=ͼ��ĸ߶�-�������ĸ߶�
		
		if (vScrollBarNow==vBarValueRange) //��������ķ�Χ==����������ƶ����� ˵���������Ѿ������λ��
		{
			return;
		}
		else
		{
			
			 GDALRasterBand  *poBand1;
			 myScene->removeItem(pItem1);
			 myScene->removeItem(pItem);
			 qDebug()<<"scene item count"<<myScene->items().count();
			//myScene->itemGroup->removeFromGroup(pItem1);
		     //pItem1->clearFocus();
			//int y=ui.graphicsView->verticalScrollBar()->pos().y();
			//int vBarValue=ui.graphicsView->verticalScrollBar()->value();
			int vBarMaxValue=ui.graphicsView->verticalScrollBar()->maximum();//���ֵ�͵��� ����������ƶ�����-�������߶�
		
			int bytePerLine = int((widthGraphicsView * 8 + 31 )/ 32*4);  
			unsigned char* allBandUC = new unsigned char[bytePerLine * heightGraphicsView]; 
			poBand1=poDataset->GetRasterBand(1);
			
			int widthFact=int(widthGraphicsView/scaleFactor);
			int heightFact=int(heightGraphicsView/scaleFactor);

			int x=int(hScrollBarNow/scaleFactor);
			int y=int(value/scaleFactor);

			poBand1->RasterIO(GF_Read,hScrollBarNow,value,widthGraphicsView,heightGraphicsView,allBandUC,widthGraphicsView,heightGraphicsView, GDT_Byte,0,0);
			pItem1=new QGraphicsPixmapItem( QPixmap::fromImage(QImage(allBandUC,widthGraphicsView,heightGraphicsView,QImage::Format_Indexed8)));

			pItem1->setPos(hScrollBarNow,value);//�����½�item1�����Ͻǵ�
			//pItem1->scale(scaleFactor,scaleFactor);
			qDebug()<<"pItem1 height"<<pItem1->boundingRect().height();
			qDebug()<<"pItem1 width"<<pItem1->boundingRect().width();
			qDebug()<<"pitem1 rect TL"<<pItem1->sceneBoundingRect().topLeft();
			qDebug()<<"pitem1 rect TR"<<pItem1->sceneBoundingRect().topRight();
			qDebug()<<"pitem1 rect BL"<<pItem1->sceneBoundingRect().bottomLeft();
			qDebug()<<"pitem1 rect BR"<<pItem1->sceneBoundingRect().bottomRight();
			pItem1->setMatrix(currMatrix);

		      qDebug()<<"pItem1 height"<<pItem1->boundingRect().height();
		      qDebug()<<"pItem1 width"<<pItem1->boundingRect().width();
			  qDebug()<<"pitem1 rect TL"<<pItem1->sceneBoundingRect().topLeft();
			  qDebug()<<"pitem1 rect TR"<<pItem1->sceneBoundingRect().topRight();
			  qDebug()<<"pitem1 rect BL"<<pItem1->sceneBoundingRect().bottomLeft();
			  qDebug()<<"pitem1 rect BR"<<pItem1->sceneBoundingRect().bottomRight();
			/*QImage img=QImage(allBandUC,widthGraphicsView,heightGraphicsView,QImage::Format_Indexed8);
			
				
			qDebug()<<"pixmap height"<<img.height();
			qDebug()<<"pixmap width"<<img.width();
			
			QPixmap redrawPixmap(widthGraphicsView,heightGraphicsView);

			QPainter painter(&redrawPixmap);
			painter.drawPixmap(x,y,widthGraphicsView,heightGraphicsView,QPixmap::fromImage(img));
			painter.end();
			
			QGraphicsPixmapItem *pBackImg=new QGraphicsPixmapItem(redrawPixmap);
			
			pBackImg->setPos(x,y);	
			
			qDebug()<<"pBackImg height"<<pBackImg->boundingRect().height();
			qDebug()<<"pBackImg width"<<pBackImg->boundingRect().width();
		
			pitem1TL.setX(int(hScrollBarNow/scaleFactor));
			pitem1TL.setY(int(value/scaleFactor));
			int vBarValuebefore=ui.graphicsView->verticalScrollBar()->height();
			qDebug()<<"vbar max "<<vBarValuebefore;
			qDebug()<<"pitem1 rect TL"<<pItem1->sceneBoundingRect().topLeft();
			qDebug()<<"pitem1 rect TR"<<pItem1->sceneBoundingRect().topRight();
			qDebug()<<"pitem1 rect BL"<<pItem1->sceneBoundingRect().bottomLeft();
			qDebug()<<"pitem1 rect BR"<<pItem1->sceneBoundingRect().bottomRight();
			//currMatrix��¼�����pItem1�Ŵ�ı���
			//pItem1->setMatrix(currMatrix);

			int vBarValue=ui.graphicsView->verticalScrollBar()->height();
			qDebug()<<"vbar max "<<vBarValue;
			qDebug()<<"pitem1 rect TL"<<pBackImg->sceneBoundingRect().topLeft();
			qDebug()<<"pitem1 rect TR"<<pBackImg->sceneBoundingRect().topRight();
			qDebug()<<"pitem1 rect BL"<<pBackImg->sceneBoundingRect().bottomLeft();
			qDebug()<<"pitem1 rect BR"<<pBackImg->sceneBoundingRect().bottomRight();*/
			//�����ػ���MyScene�ľ���
			//QGraphicsRectItem *rectItemRedraw=new QGraphicsRectItem();
			qDebug()<<"ROILists count"<<myScene->ROILists->count();
			
			//��pitem1����itemGroup
			//myScene->itemGroup->addToGroup(pItem1);
			//myScene->addItem(myScene->itemGroup);
			myScene->addItem(pItem1);
			
			qDebug()<<"myScene items count"<<myScene->items().count();
			
			if(myScene->ROILists->count()!=0)
			{
				for(int i=0;i<myScene->ROILists->count();i++)
				{
					myScene->RedrawROI(i);
					qDebug()<<"myScene items count"<<myScene->items().count();
									
					
				}
			}
			
		
		
			qDebug()<<"myScene's including items"<<myScene->items().count();
			ui.graphicsView->setScene(myScene);


	
		}

	}

}

void MainWindow::HorizontalScrollBarValueChangedSlot(int value)
{
	qDebug()<<"HorizontalScrollBar value changed"<<value;
	qDebug()<<"changed value"<<endl;
	int temp=vScrollBarNow;
	hScrollBarNow=value;//Ŀǰ��ֱ����������ֵ��¼�ڱ�����

	if(fileName.isEmpty())
	{
		return;
	}
	else
	{
		int hBarWidth = ui.graphicsView->horizontalScrollBar()->width();//ˮƽ���������
		int hBarValueRange=width-hBarWidth;

		if (hScrollBarNow==hBarValueRange) //��������ķ�Χ==����������ƶ�����
		{
			return;
		}
		else
		{
		/*	GDALRasterBand  *poBand1;

			int bytePerLine = (widthGraphicsView * 8 + 31 )/ 32*4;  
			unsigned char* allBandUC = new unsigned char[bytePerLine * heightGraphicsView]; 
			poBand1=poDataset->GetRasterBand(1);
			
			poBand1 ->RasterIO(GF_Read,value,vScrollBarNow, widthGraphicsView,heightGraphicsView,allBandUC ,widthGraphicsView,heightGraphicsView, GDT_Byte, 0, 0);
			pItem1=new QGraphicsPixmapItem( QPixmap::fromImage(QImage(allBandUC,widthGraphicsView,heightGraphicsView,QImage::Format_Indexed8)));
			pItem1->setPos(value,vScrollBarNow);//�����½�item�����Ͻǵ�
			myScene->addItem(pItem1);
			pItem1->setMatrix(currMatrix);

			if(myScene->ROILists->count()!=0)
			{
				for(int i=0;i<myScene->ROILists->count();i++)
				{
					myScene->RedrawROI(i);
				}
			}*/

			qDebug()<<"myScene's including items"<<myScene->items().count();
			ui.graphicsView->setScene(myScene);

		}

	}

}

void MainWindow::openFileSlot()
{
	qDebug()<<"fileName is";
	//get file name
	fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath()); // ��mainwindow.h�Ѷ���
	qDebug()<<"fileName is"<<fileName;

	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"��ʾ","��ѡ����Ҫ�򿪵��ļ�");
		return;
	}


	else
	{
		/*QImage *img=new QImage;
		
		if(! ( img->load(fileName) ) ) //����ͼ��
		{
			QMessageBox::information(this,
				tr("��ͼ��ʧ��"),
				tr("��ͼ��ʧ��!"));
			delete img;
			return;
		}*/

		ReadImg(fileName,0,0);
		
		//CalScaleFactor(maxLatitude,minLatitude,maxLongtitude,minLongtitude,widthGraphicsView,heightGraphicsView);

		ShowTree(fileName,nBandCount);
	}

}

void MainWindow::ReadImg(QString fileName,int myScenedistX,int myScenedistY)

{
    myScenedistX=MyScene::distX;
	myScenedistY=MyScene::distY;

	
	GDALAllRegister();         //����GDAL��ȡͼƬ����Ҫ����ע��  

	//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //����֧������·��  
	

	GDALRasterBand  *poBand;
	
	QByteArray ba=fileName.toLatin1();
	char *mm=ba.data();
	qDebug()<<mm<<endl;

	poDataset=(GDALDataset*)GDALOpen(mm,GA_ReadOnly);
	double GT[6];
	//�õ�����任ģ��  
	poDataset->GetGeoTransform(GT);  
	
	//��ȡͼ��Ĵ�С
	width=poDataset->GetRasterXSize();    
	height=poDataset->GetRasterYSize();     
	
	//��ȡͼ��Ĳ�����
	nBandCount=poDataset->GetRasterCount();
	qDebug()<<nBandCount<<endl;	

	//��ȡӰ����������
	poBand=poDataset->GetRasterBand(1);
	poBand -> GetRasterDataType();

	// ͼ�������ͷֱ�����Ϣ  
	double adfGeoTransform[6];  
	QString origin = "";  
	QString pixelSize = "";
	poDataset->GetGeoTransform(adfGeoTransform);

	if( poDataset->GetGeoTransform(adfGeoTransform ) == CE_None )  
	{  
		poDataset->GetGeoTransform(adfGeoTransform);
	}

	//�����ʾͼ���GraphicsViewʵ�ʳߴ�
	widthGraphicsView=ui.graphicsView->size().width();
	heightGraphicsView=ui.graphicsView->size().height();
	 
	//int bytePerLine = (width * 8 + 31 )/ 32*4;  
	//unsigned char* allBandUC = new unsigned char[bytePerLine * height]; 
	//ÿ�ν������봰�ڳߴ��С��ͼ�� 2018/04/20
	int bytePerLine = (widthGraphicsView * 8 + 31 )/ 32*4;  
	unsigned char* allBandUC = new unsigned char[bytePerLine * heightGraphicsView]; 
	
	
	poBand->RasterIO(GF_Read,0,0, widthGraphicsView, heightGraphicsView,allBandUC ,widthGraphicsView, heightGraphicsView, GDT_Byte, 0, 0);

//	GDALClose(poDataset);
	pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage(allBandUC,widthGraphicsView,heightGraphicsView,QImage::Format_Indexed8)));
	
	qDebug()<<"pItem height"<<pItem->boundingRect().height();
	qDebug()<<"pItem width"<<pItem->boundingRect().width();
	
	pItem1=pItem;
	myScene->setSceneRect(0,0,width,height);//Ϊ��ʹ�ù�������ʾͼ��ʵ�ʵĳ���
		
	//��item���������
	myScene->addItem(pItem);
	//Ϊ��ͼ���ó���
	ui.graphicsView->setScene(myScene);
	

}

//����ͼ����ʾ��ͼ��γ�ȵı�����
double MainWindow::CalScaleFactor(double maxLatitude,double minLatitude,double maxLongtitude,double minLongtitude,int widthGraphicsView,int heightGraphicsView)
{
	 double HeightScaleFactor;
	 double WidthScaleFactor;

	 if (maxLatitude!=0&&minLatitude!=0&&maxLongtitude!=0&&minLongtitude!=0&&widthGraphicsView!=0&&heightGraphicsView!=0)
	 {
		 HeightScaleFactor=(maxLongtitude-minLongtitude)/heightGraphicsView;
		 WidthScaleFactor=(maxLatitude-minLatitude)/widthGraphicsView;
	 }
	 if (HeightScaleFactor>WidthScaleFactor)
	 {
		 return HeightScaleFactor;
	 }
	 else
	 {
		 return WidthScaleFactor;
	 }
}


//<summary>  
///��ȡ�������� (Ϊ�˷������֣������������GraphicsView��������������������ĸ����󷢳����ź�)
///</summary>  
///
void MainWindow::getActionName()

{
	QAction *act=(QAction*) sender();//��ȡ���������Ķ���
	QString actName=act->objectName();//��ȡ����������������֣�����ΪMagnifyAction
	
	strList->append(actName);
	
};

//<summary>  
///�������� ʵ��ͼ��ƽ�Ʋ�
///</summary>  
///<param name="event">�������¼�</param>
void MainWindow::panPicSlot()

{
	//�ж��Ƿ��Ѿ���ͼ������
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"Error Message","Please select a file");
		return;
	}
	
	getActionName();

}

//<summary>  
///�������� ʵ��ͼ��Ŵ�� 
///</summary>  
///<param name="event">�������¼�</param>  
void MainWindow::MagnifyActionSlot()

{
	//�ж��Ƿ��Ѿ���ͼ������
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"Error Message","Please select a file");
		return;
	}

	getActionName();
	ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	cursor.setShape(Qt::ArrowCursor);	
			
}

//<summary>  
///�������� ʵ��ͼ��ѡ��ROI��
///</summary>  

void MainWindow::NewROIActionSlot()

{
	//�ж��Ƿ��Ѿ���ͼ������
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"��ʾ","��ѡ����Ҫ�򿪵��ļ�");
		return;
	}
	ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	cursor.setShape(Qt::ArrowCursor);	


	getActionName();

}

//<summary>  
///�������� ʵ��ͼ��ɾ��ROI��
///</summary>  

void MainWindow::DeleteROIActionSlot()

{
	//�ж��Ƿ��Ѿ���ͼ������
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"��ʾ","��ѡ����Ҫ�򿪵��ļ�");
		return;
	}

	getActionName();

}
//���Ӱ�������¼�������
void MainWindow::mousePressEvent(QMouseEvent *event)
{
	//strList=new QStringList();
	//�ҵ�scrollArea����Ļ���ϵľ��ε�λ�ã������˾��ε����Ͻǵ������
	QRect *rect=new QRect(ui.scrollArea->pos()+ui.centralWidget->pos(),ui.scrollArea->size());
	
	currentPos = event->pos();
	qDebug()<<"mousePressEvent"<<endl;
	if ( rect->contains(currentPos))//������ĵ���scrollArea�ľ��η�Χ�ڣ��򷢳��ź�
	{
		emit clicked();
	}
	
	else
	{
		return;
	}
}

//<summary>  
///��������Graphicsview�ϰ�����������Ӧ�¼�
///</summary>  
///<param name="event">�������¼�</param> 
void MainWindow::mousePressEventSlot()
{
	mouseGrabber();
	//strList�ĳ�ʼ��������mousePressEventSlot()
	if (strList->size()==0)
	{
		QMessageBox::information(this,"Error Message","��������Ĳ���");
	}
	ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	cursor.setShape(Qt::ArrowCursor);	
	operationName=""; //�����洢�������Ĳ˵�������
	if (strList->count()==0)
	{
		return;
	}

	if (strList->count()>0)
	{
		int nstrList=strList->count();
		operationName=strList->at(nstrList-1);
	}
	
	if (operationName=="PanAction")
	{
		cursor.setShape(Qt::ClosedHandCursor);
		ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); 
				
		mySceneDistX=MyScene::distX;
		mySceneDistY=MyScene::distY;

		
	
		
		//ReadImg(fileName,mySceneDistX,mySceneDistY);
		//ui.scrollArea->horizontalScrollBar()->setValue(ui.scrollArea->horizontalScrollBar()->value()+distX);	
	}
	
	
	if (operationName=="MagnifyAction")
	{
		
		if(cursor.shape()==Qt::ClosedHandCursor)
		{
			cursor.setShape(Qt::ArrowCursor);

		}
		float dScalefactor=2;
		iZoomIn=iZoomIn+2;
		qDebug()<<"zoom factor"<<iZoomIn;


	    scaleFactor= qPow(dScalefactor, iZoomIn); // ��ȫ�ֱ��� ���ű�������ֵ ����x��y����

		matrix.scale(dScalefactor,dScalefactor);
		//matrix.scale(scaleFactor,scaleFactor);

		qDebug()<<"scaleFactor"<<scaleFactor;
		
		currMatrix=matrix;//��¼��ʾͼ��ĵ�ǰ��matrix��Ϣ ������������ʹ��
	
		pItem1->setMatrix(matrix);

		if(myScene->ROILists->count()!=0)
		{
			pItem1->setZValue(-1.00000);
		}
		
		ui.graphicsView->show();
		
		
		/*int hh=ui.graphicsView->horizontalScrollBar()->maximum();

		qDebug()<<"horScrollBar"<<ui.graphicsView->horizontalScrollBar()->maximum();
		qDebug()<<"ver ScrollBar"<<ui.graphicsView->verticalScrollBar()->maximum();
		int vv=ui.graphicsView->verticalScrollBar()->maximum();
		// �������Ͻ����꣨�������꣩
		QPointF p1 = QPointF(myScene->sceneRect().topLeft());
		qDebug() << "p1:" << p1;

		// �������ϽǶ�Ӧ��ͼ���꣨��ͼ���꣩
		qDebug() << "view->mapFromScene(p1.x(), p1.y())" << ui.graphicsView->mapFromScene(p1.x(), p1.y());*/
		

	}

	if (operationName=="NewROIAction")//�½�ROI
	{
		
		
		qDebug()<<"NewROIActon"<<endl;
	
	}

	if (operationName=="DeleteROIAction")//ɾ��ROI
	{
		
		qDebug()<<"DeleteROIActon"<<endl;
		
		if (myScene->ROILists->isEmpty())//����һ��Ҫ��myScene->ROILists��ʾ�ĸ����ROILists
		{
			return;
		}
		else
		{
				qDebug()<<myScene->ROILists->size()<<endl;
				//Rect *rect=new Rect();
				//QGraphicsRectItem *tmpItem=new QGraphicsRectItem();
				//tmpItem=myScene->ROILists->at(0);
				//rect = qgraphicsitem_cast<Rect*>(myScene->ROILists->at(0));

		}
	}

	
}
//<summary>  
///ͼ���ϵĵ�����ת����Scene�ϵĵ�����
///</summary>  
///<param name="event">�������¼�</param> 

void MainWindow::ImgPtChangedScenePt()
{
	

};
//<summary>  
///ͼ���ϵĵ�����ת����Scene�ϵĵ�����
///</summary>  
///<param name="event">�������¼�</param> 

void MainWindow::ScenePtChangedImgPt()
{


};


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	
	qDebug()<<" MainWindow mousePressEvent"<<endl;

	
}
void MainWindow::isPressed()
{
	qDebug()<<"ItemIsclicked in MainWindow"<<endl;
}
//�ۣ���rect����ͷ�ʱִ��
//Ӧ�����ñ�־λ����UIͼƬֹͣ������϶��¼�����Ӧ
void MainWindow::isReleased()
{
	qDebug()<<"ItemIsRelease in MainWindow"<<endl;
}
void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
	releaseMouse();

			qDebug()<<"mouseReleaseEvent"<<endl;
	//strList=new QStringList();
	//�ҵ�scrollArea����Ļ���ϵľ��ε�λ�ã������˾��ε����Ͻǵ������
	QRect *rect=new QRect(ui.scrollArea->pos()+ui.centralWidget->pos(),ui.scrollArea->size());

	currentPos = event->pos();
	
	if ( rect->contains(currentPos))//������ĵ���scrollArea�ľ��η�Χ�ڣ��򷢳��ź�
	{
		emit released();
	}

	else
	{
		return;
	}
	
}

///<summary>  
/// ÿ��1���Ӷ�ʱ�������źţ���ȡMyScene�����������ת�ɵ������� 
///</summary>  
///<param name=""></param> 
void MainWindow::timeUpdate()
{
	QString sGeoX=QString::number(MyScene::dGeoPosX,'f',4);
	LabelGeoXY->setText(sGeoX);
	
	ui.statusBar->addWidget(LabelGeoXY);
	
}


/*void MainWindow::mouseReleaseEventSlot()
{
	qDebug()<<"mouseReleaseEvent"<<endl;
	
	//strList�ĳ�ʼ��������mousePressEventSlot()
	//if (strList->size()==0)
	//{
		//QMessageBox::information(this,"Error Message","��������Ĳ���");
	//}
	/*ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	cursor.setShape(Qt::ArrowCursor);	
	QString temp="";
	if (strList->count()==0)
	{
		return;
	}

	if (strList->count()>0)
	{
		int nstrList=strList->count();
		temp=strList->at(nstrList-1);
	}

	if (temp=="PanAction")
	{
		cursor.setShape(Qt::ClosedHandCursor);
		ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); 

	}
}*/

/*void MainWindow::paintEvent(QPaintEvent * event)
{
	paint=new QPainter;
	paint->begin(this);
	paint->setPen(QPen(Qt::blue,4,Qt::DashLine));//���û�����ʽ 
	paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));//���û�ˢ��ʽ 
	paint->drawRect(20,20,160,160);
	paint->end();

}*/


/*void MainWindow::mouseReleaseEvent( QMouseEvent *event )  
{  
	if ( event->button() == Qt::LeftButton)  
	{  
		ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	}  
}  

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (graphicsView->dragMode() ==QGraphicsView::ScrollHandDrag)
	{
		QPoint temp;
		int x1;
		x1=event->x();//����ƶ����λ��
		int dx=x1-x0;
		graphicsView->horizontalScrollBar()->setValue(graphicsView->horizontalScrollBar()->value()+dx);

	}


}*/

//<summary>  
///�����¼������� 
///</summary>  
///<param name="obj">�ؼ�����</param>  
///<param name="event">�ؼ��¼�</param>  
bool MainWindow::eventFilter(QObject *obj,QEvent *event)

{
	//
	//ui.scrollArea->verticalScrollBar()->hasFocus();
	//if (obj==ui.scrollArea->verticalScrollBar()&&event->type()==QEvent::MouseButtonPress)
	if (ui.scrollArea->verticalScrollBar()->hasFocus())

	{
		
		qDebug()<<"scrollArea event eventFilter"<<endl;
		QMouseEvent *mouseEvent=static_cast<QMouseEvent *>(event);
		if(mouseEvent->button()==Qt::LeftButton)
		{
			
			if(event->type() == QEvent::MouseButtonPress)
			{
				//�����¼�����

				qDebug()<<"scrollArea event mouseButton presss"<<endl;
			}
		
		}
		else 	
		{
			return false;
		
		
		}
			
	}
	return QMainWindow::eventFilter(obj,event);

}

/*void MainWindow::treeItemChanged(QTreeWidgetItem* item,int column)
{
	//QString itemText = item->text(0);
	if(Qt::Checked == item->checkState(0))
	{
		// QTreeWidgetItem* parent = item->parent();
		int count = item->childCount(); //��������ĸ���
		if(count >0)
		{
			for(int i=0; i<count; i++)
			{
				item->child(i)->setCheckState(0,Qt::Checked);
			}
		}
		else
		{
			updateParentItem(item);
		}
	}
	else if(Qt::Unchecked == item->checkState(0))
	{
		int count = item->childCount();
		if(count > 0)
		{
			for(int i=0; i<count; i++)
			{
				item->child(i)->setCheckState(0,Qt::Unchecked);
			}
		}
		else
		{
			updateParentItem(item);
		}
	}
}*/


/*void MainWindow::updateParentItem(QTreeWidgetItem* item)
{
	QTreeWidgetItem *parent = item->parent();
	if(parent == NULL)
	{
		return ;
	}

	int selectedCount = 0;
	int childCount = parent->childCount();
	for(int i=0;i<childCount;i++) //�ж��ж��ٸ����ѡ��
	{
		QTreeWidgetItem* childItem = parent->child(i);
		if(childItem->checkState(0) == Qt::Checked)
		{
			selectedCount++;
		}
	}
	if(selectedCount <= 0)  //���û�����ѡ�У���������Ϊδѡ��״̬
	{
		parent->setCheckState(0,Qt::Unchecked);
	}
	else if(selectedCount>0 && selectedCount<childCount)    //����в������ѡ�У���������Ϊ����ѡ��״̬�����û�ɫ��ʾ
	{
		parent->setCheckState(0,Qt::PartiallyChecked);
	}
	else if(selectedCount == childCount)    //�������ȫ����ѡ�У�����������Ϊѡ��״̬
	{
		parent->setCheckState(0,Qt::Checked);
	}
}*/

void  MainWindow::ShowTree(const QString filename,int nBandCount)
{
	if(filename==""||nBandCount==0)
	{
		return;
	}
	treeView=new QTreeView(this);

	QFileInfo fileInfo(filename);
	qDebug()<<filename<<endl;
    model = new QStandardItemModel(nBandCount,0); 

	QStandardItem *rootItem=new QStandardItem(filename);
	
	for(int i=0;i<nBandCount;i++)
	{
		QStandardItem *childItem = new QStandardItem (tr("Band %0").arg(i+1));
		
		rootItem->setChild(i,childItem);
		int m=rootItem->rowCount();
	}
	 model->setItem(0,rootItem);
	 ui.treeView->setModel(model);	
	 ui.treeView->show();
	
}


///<summary>  
/// ��ȡͼ���ļ�  
///</summary>  
///<param name="filename">ͼ���ļ�</param>  
/*void MainWindow::ReadImg(const QString filename)
{

	GDALAllRegister();  
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO" );  
	poDataset = ( GDALDataset* )GDALOpen(filename.toStdString().c_str(),GA_ReadOnly );  
	if ( poDataset == NULL )  
	{  
		QMessageBox::critical( this, tr("Error!" ), tr( "Can not open file %1" ).arg(filename) );  
		return;  
	}  

	
	//ShowFileList( imgPath );  
	//ShowImgInfor( imgPath );  
	// ���ͼ���ļ������������Σ���Ĭ��ֻ��ʾ��һ���λҶ�ͼ��  
	if ( poDataset->GetRasterCount() != 3 )  
	{  
		m_showColor = false;  
		ShowBand( poDataset->GetRasterBand(1 ) );  
	}  
	// ���ͼ�������������Σ���Ĭ����RGB��˳����ʾ��ɫͼ  
	else  
	{  
		m_showColor = true;  
		QList<GDALRasterBand*> bandList;  
		bandList.append(poDataset->GetRasterBand( 1 ) );  
		bandList.append(poDataset->GetRasterBand( 2 ) );  
		bandList.append(poDataset->GetRasterBand( 3 ) );  
		ShowImg( &bandList );  
	}  
	GDALClose( poDataset );  
}*/
///<summary>  
///��ʾ������ͼ��  
///</summary>  
///<param name="band">ͼ�񲨶�</param>  
/*void MainWindow::ShowBand( GDALRasterBand* band )  
{  
	if ( band == NULL )  
	{  
		return;  
	}  

	QList<GDALRasterBand*> myBand;  
	myBand.append( band );  
	myBand.append( band );  
	myBand.append( band );  

	ShowImg( &myBand );  

}*/

///<summary>  
/// ��ʾͼ��  
///</summary>  
///<param name="imgBand">ͼ�񲨶�</param>  
/*void MainWindow::ShowImg( QList<GDALRasterBand*> *imgBand )  
{  
	if ( imgBand->size() != 3 )  
	{  
		return;  
	}  
	//��ȡ�ò���ͼ��ĳ��Ϳ�
	int imgWidth = imgBand->at( 0)->GetXSize();  
	int imgHeight = imgBand->at( 0)->GetYSize();  

	m_scaleFactor = this->height() * 1.0 /imgHeight;  

	int iScaleWidth = ( int )( imgWidth *m_scaleFactor - 1 );  
	int iScaleHeight = ( int )( imgHeight *m_scaleFactor - 1 );  
	
	//��ȡӰ����������
	GDALDataType dataType = imgBand->at( 0)->GetRasterDataType();  

	// ���ȷֱ��ȡRGB��������  
	float* rBand = new float[iScaleWidth *iScaleHeight];  
	float* gBand = new float[iScaleWidth *iScaleHeight];  
	float* bBand = new float[iScaleWidth *iScaleHeight];  

	unsigned char *rBandUC, *gBandUC, *bBandUC;  

	// �����Ƿ���ʾ��ɫͼ���ж�RGB�������ε���ɷ�ʽ�����ֱ��ȡ  
	if ( m_showColor == true )  
	{  
		imgBand->at( 0 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, rBand , iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  
		imgBand->at( 1 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, gBand, iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  
		imgBand->at( 2 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, bBand, iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  

		// �ֱ�����ÿ�����β���Floatת��Ϊunsigned char  
		//rBandUC = ImgSketch( rBand,imgBand->at( 0 ), iScaleWidth * iScaleHeight, imgBand->at( 0)->GetNoDataValue() );  
		//gBandUC = ImgSketch( gBand,imgBand->at( 1 ), iScaleWidth * iScaleHeight, imgBand->at( 1)->GetNoDataValue() );  
		//bBandUC = ImgSketch( bBand,imgBand->at( 2 ), iScaleWidth * iScaleHeight, imgBand->at( 2)->GetNoDataValue() );  
	}  
	else  
	{  
		imgBand->at( 0 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, rBand , iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  

		//rBandUC = ImgSketch( rBand,imgBand->at( 0 ), iScaleWidth * iScaleHeight, imgBand->at( 0)->GetNoDataValue() );  
		//gBandUC = rBandUC;  
		//bBandUC = rBandUC;  
	}  

	// �����������������  
	/*int bytePerLine = ( iScaleWidth * 24 + 31 )/ 8;  
	unsigned char* allBandUC = new unsigned char[bytePerLine * iScaleHeight * 3];  
	for( int h = 0; h < iScaleHeight; h++ )  
	{  
		for( int w = 0; w < iScaleWidth; w++)  
		{  
			allBandUC[h * bytePerLine + w * 3 +0] = rBandUC[h * iScaleWidth + w];  
			allBandUC[h * bytePerLine + w * 3 +1] = gBandUC[h * iScaleWidth + w];  
			allBandUC[h * bytePerLine + w * 3 +2] = bBandUC[h * iScaleWidth + w];  
		}  
	}  

	// ����ͼ����ʾ  
	//QGraphicsPixmapItem *imgItem = new QGraphicsPixmapItem (QPixmap::fromImage(QImage( allBandUC, iScaleWidth, iScaleHeight, bytePerLine,QImage::Format_RGB888  ) ) );  
	//QGraphicsScene *myScene = new QGraphicsScene();  
	//myScene->addItem( imgItem );  
	//this->setScene( myScene );  


}  */



void MainWindow::InitTree()

{
	ui.treeWidget->clear();    //��ʼ�����οؼ�
	ui.treeWidget->show();

	//addTreeRoot
	//ui.treeWidget->setHeaderLabel("tree");
	//ui.treeWidget->setHeaderHidden(1); // TreeWidget �������� 1Ϊ����Header���� 0 Ϊ��ʾHeader����

	QTreeWidgetItem *items1 = new QTreeWidgetItem(ui.treeWidget,
		QStringList(QString("num_1")));
	items1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items1->setCheckState(0,Qt::Unchecked); //��ʼ״̬û�б�ѡ��

	QTreeWidgetItem *items2 = new QTreeWidgetItem(items1,
		QStringList(QString("num_2")));
	items2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items2->setCheckState(0,Qt::Unchecked); //��ʼ״̬û�б�ѡ��

	QTreeWidgetItem *items3 = new QTreeWidgetItem(items1,
		QStringList(QString("num_3")));
	items3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items3->setCheckState(0,Qt::Unchecked); //��ʼ״̬û�б�ѡ��


}