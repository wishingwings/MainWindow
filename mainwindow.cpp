#include "mainwindow.h"
#include "MyScene.h" //为了引用全局变量QList ROILists
#include "rect.h"
#include "gdal.h"
#include "gdal_priv.h"

//接收的变量
static double dGeoPosX; //MyScene中鼠标所在点的地理坐标X 初始化
static double dGeoPosY; //MyScene中鼠标所在点的地理坐标Y 初始化

static int distX;//MyScene鼠标移动的X值
static int distY;//MyScene鼠标移动的X值

static double ROIscaleFactor;  //MyScene 绘制ROI时候图像的缩放比例

static QList<QGraphicsRectItem*> *ROILists;//初始化*ROILists
//发出的变量

QString MainWindow::fileName=""; //myScene.cpp中需要使用载入图像的名字
QString  MainWindow::operationName="";//myScene.cpp中需要使用操作栏最后一个操作的名字
QPoint  MainWindow::pitem1TL;
float MainWindow::scaleFactor;

int MainWindow::vScrollBarNow; //QGrphicsView 垂直滚动条现在的位置  myScene需要确定ROI左上角点移动的位置

int MainWindow::hScrollBarNow; //QGrphicsView 水平滚动条现在的位置  myScene需要确定ROI左上角点移动的位置
QGraphicsItemGroup MainWindow::*itemGroup;
 

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	
	ui.setupUi(this);
	setWindowState(Qt::WindowMaximized);//使得窗口最大化
	//计算显示图像的区域

	vScrollBarNow=ui.graphicsView->verticalScrollBar()->value();
	hScrollBarNow=2;
	iZoomIn=0;
	scaleFactor=1.000000;//默认图像放大倍数为1
	
	vScrollBar=ui.graphicsView->verticalScrollBar();
	hScrollBar=ui.graphicsView->horizontalScrollBar();
	vScrollBar->setTracking(true);
	
	
	timer=new QTimer(this);
	timer->start(1000); // 每次发射timeout信号时间间隔为1秒
	

	fileName="";
	strList=new QStringList();
	myScene=new MyScene(this);
	
	qDebug()<<myScene->sceneRect()<<endl;
	
	 LabelGeoXY = new QLabel(this);

	
	//为视图设置场景
	
	ui.graphicsView->setScene(myScene);

	//ui.graphicsView->setMouseTracking(true);
	ui.scrollArea->setMouseTracking(true);
	//ui.centralWidget->setMouseTracking(true);
	//ui.scrollAreaWidgetContents->setMouseTracking(true);
	MainWindow::setMouseTracking(true);
		
	//解决中文显示乱码问题
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	//解决中文显示乱码问题

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
	
	 /*int row = 0; // 用来记录数据模型的行号 

	 // 图像的格式信息  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Description" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetDescription() ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Meta Infor") ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetMetadataItem( GDAL_DMD_LONGNAME) ) ) ;  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr("Data Type") ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem(GDALGetDataTypeName( ( poDataset->GetRasterBand( 1)->GetRasterDataType() ) ) ) );  

	 // 图像的大小和波段个数  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "X Size" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterXSize() ) ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Y Size" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterYSize() ) ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Band Count" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterCount() ) ) );  

	 // 图像的投影信息  
	 imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Projection" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetProjectionRef() ) );  

	 // 图像的坐标和分辨率信息  
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
///QGraphicsView 垂直滚动条发生变化，触发的事件
///</summary>  
///<param name="value">滚动条变化的数值</param>  

void MainWindow::VerticalScrollBarValueChangedSlot(int value)
{
	qDebug()<<"verticalScrollBar value changed"<<endl;
	qDebug()<<"changeint factValue"<<endl;
	
	vScrollBarNow=value;
	//目前垂直滚动条的数值记录在变量中
	int temp=hScrollBarNow;
	if(fileName.isEmpty())
	{
		return;
	}
	else
	{
		int vBarHeight = ui.graphicsView->verticalScrollBar()->height();//垂直滚动条高度
		int vBarValueRange=height-vBarHeight;//滚动条滑动的最大距离=图像的高度-滚动条的高度
		
		if (vScrollBarNow==vBarValueRange) //如果滑动的范围==滚动条最大移动距离 说明滚动条已经到最大位置
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
			int vBarMaxValue=ui.graphicsView->verticalScrollBar()->maximum();//这个值就等于 滚动条最大移动距离-滚动条高度
		
			int bytePerLine = int((widthGraphicsView * 8 + 31 )/ 32*4);  
			unsigned char* allBandUC = new unsigned char[bytePerLine * heightGraphicsView]; 
			poBand1=poDataset->GetRasterBand(1);
			
			int widthFact=int(widthGraphicsView/scaleFactor);
			int heightFact=int(heightGraphicsView/scaleFactor);

			int x=int(hScrollBarNow/scaleFactor);
			int y=int(value/scaleFactor);

			poBand1->RasterIO(GF_Read,hScrollBarNow,value,widthGraphicsView,heightGraphicsView,allBandUC,widthGraphicsView,heightGraphicsView, GDT_Byte,0,0);
			pItem1=new QGraphicsPixmapItem( QPixmap::fromImage(QImage(allBandUC,widthGraphicsView,heightGraphicsView,QImage::Format_Indexed8)));

			pItem1->setPos(hScrollBarNow,value);//设置新建item1的左上角点
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
			//currMatrix记录最近的pItem1放大的倍数
			//pItem1->setMatrix(currMatrix);

			int vBarValue=ui.graphicsView->verticalScrollBar()->height();
			qDebug()<<"vbar max "<<vBarValue;
			qDebug()<<"pitem1 rect TL"<<pBackImg->sceneBoundingRect().topLeft();
			qDebug()<<"pitem1 rect TR"<<pBackImg->sceneBoundingRect().topRight();
			qDebug()<<"pitem1 rect BL"<<pBackImg->sceneBoundingRect().bottomLeft();
			qDebug()<<"pitem1 rect BR"<<pBackImg->sceneBoundingRect().bottomRight();*/
			//增加重绘在MyScene的矩形
			//QGraphicsRectItem *rectItemRedraw=new QGraphicsRectItem();
			qDebug()<<"ROILists count"<<myScene->ROILists->count();
			
			//把pitem1加入itemGroup
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
	hScrollBarNow=value;//目前垂直滚动条的数值记录在变量中

	if(fileName.isEmpty())
	{
		return;
	}
	else
	{
		int hBarWidth = ui.graphicsView->horizontalScrollBar()->width();//水平滚动条宽度
		int hBarValueRange=width-hBarWidth;

		if (hScrollBarNow==hBarValueRange) //如果滑动的范围==滚动条最大移动距离
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
			pItem1->setPos(value,vScrollBarNow);//设置新建item的左上角点
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
	fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath()); // 在mainwindow.h已定义
	qDebug()<<"fileName is"<<fileName;

	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"提示","请选择需要打开的文件");
		return;
	}


	else
	{
		/*QImage *img=new QImage;
		
		if(! ( img->load(fileName) ) ) //加载图像
		{
			QMessageBox::information(this,
				tr("打开图像失败"),
				tr("打开图像失败!"));
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

	
	GDALAllRegister();         //利用GDAL读取图片，先要进行注册  

	//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //设置支持中文路径  
	

	GDALRasterBand  *poBand;
	
	QByteArray ba=fileName.toLatin1();
	char *mm=ba.data();
	qDebug()<<mm<<endl;

	poDataset=(GDALDataset*)GDALOpen(mm,GA_ReadOnly);
	double GT[6];
	//得到仿射变换模型  
	poDataset->GetGeoTransform(GT);  
	
	//获取图像的大小
	width=poDataset->GetRasterXSize();    
	height=poDataset->GetRasterYSize();     
	
	//获取图像的波段数
	nBandCount=poDataset->GetRasterCount();
	qDebug()<<nBandCount<<endl;	

	//获取影像数据类型
	poBand=poDataset->GetRasterBand(1);
	poBand -> GetRasterDataType();

	// 图像的坐标和分辨率信息  
	double adfGeoTransform[6];  
	QString origin = "";  
	QString pixelSize = "";
	poDataset->GetGeoTransform(adfGeoTransform);

	if( poDataset->GetGeoTransform(adfGeoTransform ) == CE_None )  
	{  
		poDataset->GetGeoTransform(adfGeoTransform);
	}

	//获得显示图像的GraphicsView实际尺寸
	widthGraphicsView=ui.graphicsView->size().width();
	heightGraphicsView=ui.graphicsView->size().height();
	 
	//int bytePerLine = (width * 8 + 31 )/ 32*4;  
	//unsigned char* allBandUC = new unsigned char[bytePerLine * height]; 
	//每次仅仅载入窗口尺寸大小的图像 2018/04/20
	int bytePerLine = (widthGraphicsView * 8 + 31 )/ 32*4;  
	unsigned char* allBandUC = new unsigned char[bytePerLine * heightGraphicsView]; 
	
	
	poBand->RasterIO(GF_Read,0,0, widthGraphicsView, heightGraphicsView,allBandUC ,widthGraphicsView, heightGraphicsView, GDT_Byte, 0, 0);

//	GDALClose(poDataset);
	pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage(allBandUC,widthGraphicsView,heightGraphicsView,QImage::Format_Indexed8)));
	
	qDebug()<<"pItem height"<<pItem->boundingRect().height();
	qDebug()<<"pItem width"<<pItem->boundingRect().width();
	
	pItem1=pItem;
	myScene->setSceneRect(0,0,width,height);//为了使得滚动条显示图像实际的长宽
		
	//将item添加至场景
	myScene->addItem(pItem);
	//为视图设置场景
	ui.graphicsView->setScene(myScene);
	

}

//计算图像显示和图像经纬度的比例尺
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
///获取动作名称 (为了方便区分，后续的鼠标在GraphicsView中连续左键操作，来自哪个对象发出的信号)
///</summary>  
///
void MainWindow::getActionName()

{
	QAction *act=(QAction*) sender();//获取发出动作的对象
	QString actName=act->objectName();//获取发出动作对象的名字：这里为MagnifyAction
	
	strList->append(actName);
	
};

//<summary>  
///工具栏上 实现图像平移槽
///</summary>  
///<param name="event">鼠标左键事件</param>
void MainWindow::panPicSlot()

{
	//判断是否已经有图像载入
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"Error Message","Please select a file");
		return;
	}
	
	getActionName();

}

//<summary>  
///工具栏上 实现图像放大槽 
///</summary>  
///<param name="event">鼠标左键事件</param>  
void MainWindow::MagnifyActionSlot()

{
	//判断是否已经有图像载入
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
///工具栏上 实现图像选择ROI槽
///</summary>  

void MainWindow::NewROIActionSlot()

{
	//判断是否已经有图像载入
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"提示","请选择需要打开的文件");
		return;
	}
	ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	cursor.setShape(Qt::ArrowCursor);	


	getActionName();

}

//<summary>  
///工具栏上 实现图像删除ROI槽
///</summary>  

void MainWindow::DeleteROIActionSlot()

{
	//判断是否已经有图像载入
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"提示","请选择需要打开的文件");
		return;
	}

	getActionName();

}
//增加按下鼠标事件处理函数
void MainWindow::mousePressEvent(QMouseEvent *event)
{
	//strList=new QStringList();
	//找到scrollArea在屏幕的上的矩形的位置，给出了矩形的左上角点的坐标
	QRect *rect=new QRect(ui.scrollArea->pos()+ui.centralWidget->pos(),ui.scrollArea->size());
	
	currentPos = event->pos();
	qDebug()<<"mousePressEvent"<<endl;
	if ( rect->contains(currentPos))//如果鼠标的点在scrollArea的矩形范围内，则发出信号
	{
		emit clicked();
	}
	
	else
	{
		return;
	}
}

//<summary>  
///工具栏在Graphicsview上按下鼠标左键响应事件
///</summary>  
///<param name="event">鼠标左键事件</param> 
void MainWindow::mousePressEventSlot()
{
	mouseGrabber();
	//strList的初始化操作在mousePressEventSlot()
	if (strList->size()==0)
	{
		QMessageBox::information(this,"Error Message","请继续您的操作");
	}
	ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	cursor.setShape(Qt::ArrowCursor);	
	operationName=""; //用来存储最后操作的菜单栏对象
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


	    scaleFactor= qPow(dScalefactor, iZoomIn); // 给全局变量 缩放比例数赋值 计算x的y次幂

		matrix.scale(dScalefactor,dScalefactor);
		//matrix.scale(scaleFactor,scaleFactor);

		qDebug()<<"scaleFactor"<<scaleFactor;
		
		currMatrix=matrix;//记录显示图像的当前的matrix信息 ，供其他动作使用
	
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
		// 场景左上角坐标（场景坐标）
		QPointF p1 = QPointF(myScene->sceneRect().topLeft());
		qDebug() << "p1:" << p1;

		// 场景左上角对应视图坐标（视图坐标）
		qDebug() << "view->mapFromScene(p1.x(), p1.y())" << ui.graphicsView->mapFromScene(p1.x(), p1.y());*/
		

	}

	if (operationName=="NewROIAction")//新建ROI
	{
		
		
		qDebug()<<"NewROIActon"<<endl;
	
	}

	if (operationName=="DeleteROIAction")//删除ROI
	{
		
		qDebug()<<"DeleteROIActon"<<endl;
		
		if (myScene->ROILists->isEmpty())//这里一定要用myScene->ROILists表示哪个类的ROILists
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
///图像上的点坐标转化成Scene上的点坐标
///</summary>  
///<param name="event">鼠标左键事件</param> 

void MainWindow::ImgPtChangedScenePt()
{
	

};
//<summary>  
///图像上的点坐标转化成Scene上的点坐标
///</summary>  
///<param name="event">鼠标左键事件</param> 

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
//槽，当rect鼠标释放时执行
//应当设置标志位，让UI图片停止对鼠标拖动事件的响应
void MainWindow::isReleased()
{
	qDebug()<<"ItemIsRelease in MainWindow"<<endl;
}
void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
	releaseMouse();

			qDebug()<<"mouseReleaseEvent"<<endl;
	//strList=new QStringList();
	//找到scrollArea在屏幕的上的矩形的位置，给出了矩形的左上角点的坐标
	QRect *rect=new QRect(ui.scrollArea->pos()+ui.centralWidget->pos(),ui.scrollArea->size());

	currentPos = event->pos();
	
	if ( rect->contains(currentPos))//如果鼠标的点在scrollArea的矩形范围内，则发出信号
	{
		emit released();
	}

	else
	{
		return;
	}
	
}

///<summary>  
/// 每隔1秒钟定时器发送信号，获取MyScene类中鼠标坐标转成地理坐标 
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
	
	//strList的初始化操作在mousePressEventSlot()
	//if (strList->size()==0)
	//{
		//QMessageBox::information(this,"Error Message","请继续您的操作");
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
	paint->setPen(QPen(Qt::blue,4,Qt::DashLine));//设置画笔形式 
	paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式 
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
		x1=event->x();//鼠标移动后的位置
		int dx=x1-x0;
		graphicsView->horizontalScrollBar()->setValue(graphicsView->horizontalScrollBar()->value()+dx);

	}


}*/

//<summary>  
///窗口事件过滤器 
///</summary>  
///<param name="obj">控件对象</param>  
///<param name="event">控件事件</param>  
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
				//进行事件处理

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
		int count = item->childCount(); //返回子项的个数
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
	for(int i=0;i<childCount;i++) //判断有多少个子项被选中
	{
		QTreeWidgetItem* childItem = parent->child(i);
		if(childItem->checkState(0) == Qt::Checked)
		{
			selectedCount++;
		}
	}
	if(selectedCount <= 0)  //如果没有子项被选中，父项设置为未选中状态
	{
		parent->setCheckState(0,Qt::Unchecked);
	}
	else if(selectedCount>0 && selectedCount<childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
	{
		parent->setCheckState(0,Qt::PartiallyChecked);
	}
	else if(selectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
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
/// 读取图像文件  
///</summary>  
///<param name="filename">图像文件</param>  
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
	// 如果图像文件并非三个波段，则默认只显示第一波段灰度图像  
	if ( poDataset->GetRasterCount() != 3 )  
	{  
		m_showColor = false;  
		ShowBand( poDataset->GetRasterBand(1 ) );  
	}  
	// 如果图像正好三个波段，则默认以RGB的顺序显示彩色图  
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
///显示单波段图像  
///</summary>  
///<param name="band">图像波段</param>  
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
/// 显示图像  
///</summary>  
///<param name="imgBand">图像波段</param>  
/*void MainWindow::ShowImg( QList<GDALRasterBand*> *imgBand )  
{  
	if ( imgBand->size() != 3 )  
	{  
		return;  
	}  
	//获取该波段图像的长和宽
	int imgWidth = imgBand->at( 0)->GetXSize();  
	int imgHeight = imgBand->at( 0)->GetYSize();  

	m_scaleFactor = this->height() * 1.0 /imgHeight;  

	int iScaleWidth = ( int )( imgWidth *m_scaleFactor - 1 );  
	int iScaleHeight = ( int )( imgHeight *m_scaleFactor - 1 );  
	
	//获取影像数据类型
	GDALDataType dataType = imgBand->at( 0)->GetRasterDataType();  

	// 首先分别读取RGB三个波段  
	float* rBand = new float[iScaleWidth *iScaleHeight];  
	float* gBand = new float[iScaleWidth *iScaleHeight];  
	float* bBand = new float[iScaleWidth *iScaleHeight];  

	unsigned char *rBandUC, *gBandUC, *bBandUC;  

	// 根据是否显示彩色图像，判断RGB三个波段的组成方式，并分别读取  
	if ( m_showColor == true )  
	{  
		imgBand->at( 0 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, rBand , iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  
		imgBand->at( 1 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, gBand, iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  
		imgBand->at( 2 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, bBand, iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  

		// 分别拉伸每个波段并将Float转换为unsigned char  
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

	// 将三个波段组合起来  
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

	// 构造图像并显示  
	//QGraphicsPixmapItem *imgItem = new QGraphicsPixmapItem (QPixmap::fromImage(QImage( allBandUC, iScaleWidth, iScaleHeight, bytePerLine,QImage::Format_RGB888  ) ) );  
	//QGraphicsScene *myScene = new QGraphicsScene();  
	//myScene->addItem( imgItem );  
	//this->setScene( myScene );  


}  */



void MainWindow::InitTree()

{
	ui.treeWidget->clear();    //初始化树形控件
	ui.treeWidget->show();

	//addTreeRoot
	//ui.treeWidget->setHeaderLabel("tree");
	//ui.treeWidget->setHeaderHidden(1); // TreeWidget 标题设置 1为隐藏Header标题 0 为显示Header标题

	QTreeWidgetItem *items1 = new QTreeWidgetItem(ui.treeWidget,
		QStringList(QString("num_1")));
	items1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items1->setCheckState(0,Qt::Unchecked); //初始状态没有被选中

	QTreeWidgetItem *items2 = new QTreeWidgetItem(items1,
		QStringList(QString("num_2")));
	items2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items2->setCheckState(0,Qt::Unchecked); //初始状态没有被选中

	QTreeWidgetItem *items3 = new QTreeWidgetItem(items1,
		QStringList(QString("num_3")));
	items3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items3->setCheckState(0,Qt::Unchecked); //初始状态没有被选中


}