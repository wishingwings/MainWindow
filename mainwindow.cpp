#include "mainwindow.h"

#include "gdal.h"
#include "gdal_priv.h"



MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	strList=new QStringList();
	Rect *rect = new Rect(); 
	

	//int x=currentPos.x();
		/*int y=currentPos.y();
		const QRectF *rect=new QRectF (currentPos,QSizeF(100,100));
		qDebug()<<"createrect"<<endl;
		QGraphicsRectItem *item_rect=new QGraphicsRectItem();
		item_rect->setRect(QRectF (currentPos,QSizeF(0,0)));*/
		

	myScene=new MyScene(this);
	
	myScene->addItem(rect);

	//为视图设置场景
	//QGraphicsView *graphicsView=new QGraphicsView (this);
	//ui.graphicsView->setScene(pScene);
	ui.graphicsView->setScene(myScene);


	
	//ui.graphicsView->setMouseTracking(true);
	
	//ui.centralWidget->setMouseTracking(true);
   //MainWindow::setMouseTracking(true);
	
	setWindowState(Qt::WindowMaximized);//使得窗口最大化
	
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

	QObject::connect(this,SIGNAL(clicked()),this,SLOT(mousePressEventSlot()));

	QObject::connect(rect,SIGNAL(itemIsPressed()),this,SLOT(isPressed()));  //FIXME
	QObject::connect(rect,SIGNAL(itemIsReleased()),this,SLOT(isReleased()));//FIXME


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

	 int row = 0; // 用来记录数据模型的行号 

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
	 imgMetaModel->setItem( row++, 1, new QStandardItem(pixelSize ) );  


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

		ReadImg(fileName);
		//ReadImgInfo(fileName);
		ShowTree(fileName,nBandCount);

	
					

	}

}

void MainWindow::ReadImg(QString fileName)

{
	GDALAllRegister();         //利用GDAL读取图片，先要进行注册  

	//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //设置支持中文路径  

	GDALDataset *poDataset;

	GDALRasterBand  *poBand;
	

	QByteArray ba=fileName.toLatin1();
	char *mm=ba.data();
	qDebug()<<mm<<endl;

	poDataset=(GDALDataset*)GDALOpen(mm,GA_ReadOnly);

	
		
	//获取图像的大小
	int width=poDataset->GetRasterXSize();    
	int height=poDataset->GetRasterYSize();     


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
	int widthGraphicsView=ui.graphicsView->size().width();
	int heightGraphicsView=ui.graphicsView->size().height();
	 

	int bytePerLine = (width * 8 + 31 )/ 32*4;  
	unsigned char* allBandUC = new unsigned char[bytePerLine * height]; 

	
	poBand ->RasterIO(GF_Read,0,0, width, height,allBandUC ,width, height, GDT_Byte, 0, 0);

	pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage(allBandUC,width,height,QImage::Format_Indexed8)));
	

	//QGraphicsPixmapItem *pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage (allBandUC,width,height,bytePerLine,QImage::Format_RGB888)));

	//将item添加至场景中
	//pScene=new QGraphicsScene(this);
	//pScene->addItem(pItem);
	myScene->addItem(pItem);

	//为视图设置场景
	//QGraphicsView *graphicsView=new QGraphicsView (this);
	//ui.graphicsView->setScene(pScene);
	ui.graphicsView->setScene(myScene);

	
	
}

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
///<param name="event">鼠标左键事件</param
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
	
	
	if (temp=="MagnifyAction")
	{
		
		double dScalefactor=1.2;

		matrix.scale(dScalefactor,dScalefactor);  
		
		pItem->setMatrix(matrix);

		ui.graphicsView->show();

	}

	if (temp=="NewROIAction")//如果是新建ROI
	{
		
		qDebug()<<"NewROIActon"<<endl;
		//emit(RectMouseIsPressed());
		
		
		/*int x=currentPos.x();
		int y=currentPos.y();
		const QRectF *rect=new QRectF (currentPos,QSizeF(100,100));
		qDebug()<<"createrect"<<endl;
		QGraphicsRectItem *item_rect=new QGraphicsRectItem();
		item_rect->setRect(QRectF (currentPos,QSizeF(0,0)));*/
		

		
		//pScene->addItem(item_rect);
		//qDebug()<<"Scene added item"<<endl;
		//ui.graphicsView->setScene(pScene);*/
		
		//mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	
	}


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
/*int x=currentPos.x();
		int y=currentPos.y();
		const QRectF *rect=new QRectF (currentPos,QSizeF(100,100));
		qDebug()<<"createrect"<<endl;
		QGraphicsRectItem *item_rect=new QGraphicsRectItem();
		item_rect->setRect(QRectF (currentPos,QSizeF(0,0)));*/
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
/*bool MainWindow::eventFilter(QObject *obj,QEvent *event)
{
	if (obj==ui.PanAction)//如果是图像平移操作

	{
		qDebug()<<"Pan"<<endl;
		QMouseEvent *mouseEvent=static_cast<QMouseEvent *>(event);
		if(mouseEvent->button()==Qt::LeftButton)
		{
			
			QCursor cursor;
			cursor.setShape(Qt::ClosedHandCursor);
			QApplication::setOverrideCursor(cursor);
			x0=mouseEvent->x();//鼠标起始位置
		
			if (graphicsView==NULL)
			{
				return false;
			}
			ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); 

			return false; 
		}

		
	}
	else 	if (obj==ui.MagnifyAction)
	{
			{
				qDebug()<<"Mag"<<endl;
				QMouseEvent *mouseEvent=static_cast<QMouseEvent *>(event);
				//if(mouseEvent->type()==QEvent::MouseButtonPress)
				if(mouseEvent->button()==Qt::LeftButton)
				{
				//x0=mouseEvent->x();//
				//y0=mouseEvent->y();

				//为视图设置场景
				QGraphicsView *graphicsView=new QGraphicsView (this);

				QMatrix matrix;  
				double dScalefactor=1.5;

				matrix.scale(dScalefactor,dScalefactor);  
				pItem->setMatrix(matrix);

				ui.graphicsView->show();
				return false;
				}

			}
		
		
	}
		else return QMainWindow::eventFilter(obj,event);
	
	}*/
	



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
